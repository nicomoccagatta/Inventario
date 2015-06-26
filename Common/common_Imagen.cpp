#include "common_Imagen.h"

namespace common {

float Imagen::valorMinimoDeSimilitudTemplateMatching;
float Imagen::valorMinimoDeSimilitudDeZonaCercanaAUnaSimilitud;
unsigned long int Imagen::valorMinimoHessianoSURFFeatureMatching;
float Imagen::distanciaMaximaDeSimilitudFeatureMatching;

Imagen::Imagen(const std::string& rutaArchivo): matrizImagen(cv::imread(rutaArchivo,1)) {}

Imagen::Imagen(const cv::Mat matrizImagen): matrizImagen(matrizImagen) {}

//Construye la imagen a partir de sus datos binarios y la informacion de su organizacion en la imagen.
Imagen::Imagen(const unsigned int alto,const unsigned int ancho, const uchar* informacionDeImagen){
	matrizImagen=cv::Mat::ones(alto,ancho, CV_8UC3);
	unsigned long int ptr=0;
	 for (unsigned int i = 0;  i < alto; i++) {
	  for (unsigned int j = 0; j < ancho; j++) {
		  matrizImagen.at<cv::Vec3b>(i,j) = cv::Vec3b(informacionDeImagen[ptr+ 0],informacionDeImagen[ptr+1],informacionDeImagen[ptr+2]);
		  ptr+=3;
	  }
	 }
}

void Imagen::guardarEnArchivo(const std::string& rutaArchivo) const{
	std::vector<int> parametros;
	parametros.push_back(100);
	try	{
		cv::imwrite(rutaArchivo,matrizImagen,parametros);
	} catch(...) {
		throw "ERROR: No es posible guardar la imagen";
	}
}

//Obtiene los datos binarios de la matriz de la imagen y los almacena en un buffer cuya direccion es retornada.
const uchar* const Imagen::obtenerBytesDinamicos() const{
	cv::Mat matrizTransformada=matrizImagen.reshape(0,1);
	uchar* bytesARetornar= new uchar[getTamanio()];
	memcpy(bytesARetornar,matrizTransformada.data,(unsigned int) (getTamanio()));
	return bytesARetornar;
}

//Devuelve la cantidad de valores de coordenadas de color que contiene la imagen.
const unsigned long int Imagen::getTamanio()const{
	return matrizImagen.total()*matrizImagen.elemSize();
}

const unsigned int Imagen::getAlto()const{
	return matrizImagen.rows;
}

const unsigned int Imagen::getAncho()const{
	return matrizImagen.cols;
}

const bool Imagen::existeImagen(const std::string& rutaArchivoImagen){
	return !((cv::imread(rutaArchivoImagen,1)).empty());
}

//Inicializa los parametros que emplearan los metodos de Template Matching y Feature Matching en la deteccion de objetos.
//Este metodo debe ser invocado antes de cualquiera de los metodos que cuentan apariciones de una imagen dentro de otra.
void Imagen::setearPatametros(float valorMinimoDeSimilitudTemplateMatching,float valorMinimoDeSimilitudDeZonaCercanaAUnaSimilitud,unsigned long int valorMinimoHessianoSURFFeatureMatching,float distanciaMaximaDeSimilitudFeatureMatching){
	Imagen::valorMinimoDeSimilitudTemplateMatching=valorMinimoDeSimilitudTemplateMatching;
	Imagen::valorMinimoDeSimilitudDeZonaCercanaAUnaSimilitud=valorMinimoDeSimilitudDeZonaCercanaAUnaSimilitud;
	Imagen::distanciaMaximaDeSimilitudFeatureMatching=distanciaMaximaDeSimilitudFeatureMatching;
	Imagen::valorMinimoHessianoSURFFeatureMatching=valorMinimoHessianoSURFFeatureMatching;
}

const bool Imagen::esValida()const{
	return !matrizImagen.empty();
}

const unsigned long int Imagen::contarApariciones(const Imagen& imagenObjeto,const std::string& tipoDeteccion)const{
	if (tipoDeteccion=="M"){
		return contarAparicionesTemplateMatching(imagenObjeto);
	} else {
		return contarAparicionesFeatureMatching(imagenObjeto);
	}
}

//Aplica el metodo Template Matching para contar las apariciones de la imagenObjeto dentro de la imagenEscena.
//Este metodo solo soporta imagenes template pasada por el parametro imagenObjeto de dimensiones menores a la imagen receptora del mensaje.
const unsigned long int Imagen::contarAparicionesTemplateMatching(const Imagen& imagenObjeto)const {
	//Si imagenObjero es de mayores dimensiones indico que no puede aparecer en la imagen por las caracteristicas del metodo.
	if (imagenObjeto.matrizImagen.rows>matrizImagen.rows || imagenObjeto.matrizImagen.cols>matrizImagen.cols)
		return 0;

	unsigned long int apariciones=0;
	//Creo la matriz que aloja los resultados que arrojo cada punto.
	cv::Mat resultanteDeComparaciones;
	resultanteDeComparaciones.create(this->matrizImagen.rows-imagenObjeto.matrizImagen.rows+1, this->matrizImagen.cols-imagenObjeto.matrizImagen.cols+1, CV_32FC1);
	//Aplico el metodo normalizado dado que conozco el maximo valor uqe alojan los coeficientes de la matriz resutlante y da buenos resultados
	cv::matchTemplate(this->matrizImagen, imagenObjeto.matrizImagen, resultanteDeComparaciones, kMetodoTemplateMatching);
	//cv::normalize( resultanteDeComparaciones, resultanteDeComparaciones, 0, 1, cv::NORM_MINMAX, -1, cv::Mat() );
	//Anulo todos los coeficientes de la matriz que no alcancen el minimo de similitud necesario.
	//cv::threshold(resultanteDeComparaciones,resultanteDeComparaciones,kValorMinimoDeSimilitud,1.0, CV_THRESH_TOZERO);
	//cv::imshow("apariciones",resultanteDeComparaciones);
	//cv::waitKey();
	double valorMinimo;
	double valorMaximo=valorMinimoDeSimilitudTemplateMatching;
	cv::Point puntoMinimo(0,0), puntoMaximo(0,0);
	bool similitudesProcesadas=false;
	//itero obteniendo todos los puntos de maxima hasta que el punto obtenido sea el maximo y no alcance el minimo de similitud.
	while (!similitudesProcesadas){
		cv::minMaxLoc(resultanteDeComparaciones, &valorMinimo, &valorMaximo, &puntoMinimo, &puntoMaximo);
		//elimino el residuo de similitud en las cercanias de esta similitud
		cv::floodFill(resultanteDeComparaciones, puntoMaximo, cv::Scalar(0), 0, cv::Scalar(valorMinimoDeSimilitudDeZonaCercanaAUnaSimilitud), cv::Scalar(0.0));
		if (valorMaximo>=valorMinimoDeSimilitudTemplateMatching)
			++apariciones;
		else
			similitudesProcesadas=true;
	}
	return apariciones; //retorno las aparicion restando la primera iteracion que no se verifica.
}

//Aplica el metodo Feature Matching para contar las apariciones de la imagenObjeto dentro de la imagenEscena.
//Cuenta la cantidad de apariciones a partir de calcular la media de la distribucion del numero de apariciones de cada punto de interes de la imagen objeto en la imagenEscena.
const unsigned long int Imagen::contarAparicionesFeatureMatching(const Imagen& imagenObjeto)const{
	//Busco los puntos de interes de ambas imagenes.
	cv::Ptr<cv::xfeatures2d::SURF> detectorDePuntosDeInteres = cv::xfeatures2d::SURF::create(valorMinimoHessianoSURFFeatureMatching);
	std::vector<cv::KeyPoint> puntosDeInteresEscena, puntosDeInteresObjeto;
	detectorDePuntosDeInteres->detect(matrizImagen, puntosDeInteresEscena);
	detectorDePuntosDeInteres->detect(imagenObjeto.matrizImagen, puntosDeInteresObjeto);

	//Obtengo las descripciones de todos los puntos e interes.
	cv::Ptr<cv::xfeatures2d::SurfDescriptorExtractor> descriptorDePuntosDeInteres= cv::xfeatures2d::SurfDescriptorExtractor::create();
	cv::Mat descripcionPuntosDeInteresEscena, descripcionPuntosDeInteresObjeto;
	descriptorDePuntosDeInteres->compute(matrizImagen, puntosDeInteresEscena, descripcionPuntosDeInteresEscena);
	descriptorDePuntosDeInteres->compute(imagenObjeto.matrizImagen, puntosDeInteresObjeto, descripcionPuntosDeInteresObjeto);

	//Comparo las descripciones y solo almaceno los resultados con una diferencia minima.
	cv::BFMatcher comparadorDeDescripciones(kDistanciaFeatureMatching);
	std::vector< std::vector<cv::DMatch> > coincidenciasPuntosDeInteres;
	comparadorDeDescripciones.radiusMatch( descripcionPuntosDeInteresObjeto,descripcionPuntosDeInteresEscena, coincidenciasPuntosDeInteres,distanciaMaximaDeSimilitudFeatureMatching);

	//Itero por las coincidencias calculando las apariciones mediante la esperanza (promedio de apariciones ponderado por la probabilidad de aparicion)
	//std::vector<cv::KeyPoint> puntosDeInteresCoincidentes; sirve para pintar la ventana que te muestre los resultados

	//unsigned long int cantidadDeCoincidencias=0;


/*
	cv::Mat1f samples( coincidenciasPuntosDeInteres.size(), 2 );
	cv::Mat1f centers( coincidenciasPuntosDeInteres.size(), 2 );
	centers.setTo(0);*/

	//std::map<unsigned long int, unsigned long int> cantPuntosPorAparicion;

	float esperanza=0;


	//std::vector<unsigned long int> prediccionesHechas; //sirve para saber la cantidad de predicciones distintas sobre la cantidad de objetos que hay
	//std::vector<float> prediccionesHechas;
	//unsigned int i=0;

	for (std::vector< std::vector<cv::DMatch> >::const_iterator iteradorPuntosEscena = coincidenciasPuntosDeInteres.begin();iteradorPuntosEscena!=coincidenciasPuntosDeInteres.end();++iteradorPuntosEscena)
		/*if (maximoDeCoincidencias<(*iteradorPuntosEscena).size())
			maximoDeCoincidencias=(*iteradorPuntosEscena).size();*/
		//unsigned long int coincidenciasPunto=(*iteradorPuntosEscena).size();
		//cantidadDeCoincidencias+=(*iteradorPuntosEscena).size();
		//float productoriaDeProbs=1;
		//float sumaPrediccionesPorProbabilidad=0;
		for (std::vector<cv::DMatch>::const_iterator iteradorCoincidenciasPunto= (*iteradorPuntosEscena).begin(); iteradorCoincidenciasPunto!=(*iteradorPuntosEscena).end();++iteradorCoincidenciasPunto)
			esperanza+=(1-(*iteradorCoincidenciasPunto).distance);
			//puntosDeInteresCoincidentes.push_back(puntosDeInteresEscena.at((*iteradorCoincidenciasPunto).trainIdx));
			//samples(i,0) = puntosDeInteresEscena.at((*iteradorCoincidenciasPunto).trainIdx).pt.x;
			//samples(i,1) = puntosDeInteresEscena.at((*iteradorCoincidenciasPunto).trainIdx).pt.y;
			//++i;
			//certezaDePrediccion*=(*iteradorCoincidenciasPunto).distance;

			//productoriaDeProbs*=(1-(*iteradorCoincidenciasPunto).distance);

/*		sirve para saber la cantidad de predicciones distintas sobre la cantidad de objetos que hay
		if (std::find(prediccionesHechas.begin(),prediccionesHechas.end(),coincidenciasPunto)==prediccionesHechas.end())
			prediccionesHechas.push_back(coincidenciasPunto);*/
/*		sirve para saber la moda y calcular la distribucion
		std::map<unsigned long int, unsigned long int>::iterator aparicionAlmacenada= cantPuntosPorAparicion.find(coincidenciasPunto);
		if (aparicionAlmacenada==cantPuntosPorAparicion.end())
			cantPuntosPorAparicion.insert(std::pair<unsigned long int, unsigned long int>(coincidenciasPunto,1));
		else
			cantPuntosPorAparicion[coincidenciasPunto]+=1;
*/


	esperanza= esperanza / coincidenciasPuntosDeInteres.size();

	//sirve para conocer la media pero sin tener en cuenta la probabilidad de que la aparicion efectivamente sea una aparicion.
	//unsigned long int cantidadPromedioDeApariciones=std::ceil((float)cantidadDeCoincidencias/(float)coincidenciasPuntosDeInteres.size());
	/*airve para saber los promedios entre las estimaciones sin importar cuantos casos faborables tiene cada una
	unsigned long int promedioDeCoincidencias=0;
	for (std::vector<unsigned long int>::const_iterator nCoincidencia= prediccionesHechas.begin(); nCoincidencia!=prediccionesHechas.end();++nCoincidencia)
		promedioDeCoincidencias+=(*nCoincidencia);
	promedioDeCoincidencias=promedioDeCoincidencias/prediccionesHechas.size();
	 */

	/* sirve para saber la moda
	unsigned long int moda=0;
	unsigned long int aparicionesModa=0;
	for (std::map<unsigned long int,unsigned long int>::iterator apariciones=cantPuntosPorAparicion.begin(); apariciones!=cantPuntosPorAparicion.end();++apariciones)
		if (apariciones->second>aparicionesModa){
			moda=apariciones->first;
			aparicionesModa=apariciones->second;
		}
	 */
	//cv::flann::KMeansIndexParams kmean_params; sirve para clustering, NO PROBADO
	//unsigned long int numeroDeClustersReales = 0;//cv::flann::hierarchicalClustering< cv::L2<float> >(samples,centers,kmean_params);

/* sirve para saber los resultados de cada metodo, por ahora nos quedamos con el piso de la esperanza
	std::stringstream parseador;
		parseador << "Objetos detectados: "<<cantidadPromedioDeApariciones<<" , por max: "<<maximoDeCoincidencias<<" , por esp: "<<std::floor(esperanza)<<" , por promedio: "<<promedioDeCoincidencias<<" , por moda: "<<moda;//" , por clustering jerarquico: "<<numeroDeClustersReales;
	cv::Mat iamgenConKPPIntados;
	cv::drawKeypoints(matrizImagen,puntosDeInteresCoincidentes,iamgenConKPPIntados);
	cv::namedWindow(parseador.str(), CV_WINDOW_NORMAL);
	cv::imshow(parseador.str(),iamgenConKPPIntados);
	cv::waitKey();
*/
	return std::floor(esperanza);
}

//Muestra la imagen en una ventana de tamaño ajustable.
//Causa advertencias de posibles errores al correr el ejecutable si se considera (no se comentan) alguna de sus lineas.
void Imagen::mostrarImagen(const std::string& tituloVentana) const{
	cv::namedWindow(tituloVentana, CV_WINDOW_NORMAL);
	cv::imshow(tituloVentana, this->matrizImagen);
	cv::waitKey();
}

} /* namespace common */
