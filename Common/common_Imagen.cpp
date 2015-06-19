/*
 * common_Imagen.cpp
 *
 *  Created on: Jun 12, 2015
 *      Author: leandro
 */

#include "common_Imagen.h"

namespace common {

Imagen::Imagen(const std::string& rutaArchivo): matrizImagen(cv::imread(rutaArchivo,1)) {
/*	if (matrizImagen.empty())
		throw "ERROR: No es posible cargar la imagen";*/
}

//constructor para imagenes enviadas por red (BETA)
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

const uchar* const Imagen::obtenerBytesDinamicos() const{
	cv::Mat matrizTransformada=matrizImagen.reshape(0,1);
	uchar* bytesARetornar= new uchar[getTamanio()];
	memcpy(bytesARetornar,matrizTransformada.data,(unsigned int) (getTamanio()));
	return bytesARetornar;
}

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
const unsigned long int Imagen::contarAparicionesTemplateMatching(const Imagen& imagenObjeto)const {
	unsigned long int apariciones=0;
	//Creo la matriz que aloja los resultados que arrojo cada punto.
	cv::Mat resultanteDeComparaciones;
	resultanteDeComparaciones.create(this->matrizImagen.rows-imagenObjeto.matrizImagen.rows+1, this->matrizImagen.cols-imagenObjeto.matrizImagen.cols+1, CV_32FC1);
	//Aplico el metodo normalizado dado que conozco el maximo valor uqe alojan los coeficientes de la matriz resutlante y da buenos resultados
	cv::matchTemplate(this->matrizImagen, imagenObjeto.matrizImagen, resultanteDeComparaciones, CV_TM_CCOEFF_NORMED);
	//cv::normalize( resultanteDeComparaciones, resultanteDeComparaciones, 0, 1, cv::NORM_MINMAX, -1, cv::Mat() );
	//Anulo todos los coeficientes de la matriz que no alcancen el minimo de similitud necesario.
	//cv::threshold(resultanteDeComparaciones,resultanteDeComparaciones,kValorMinimoDeSimilitud,1.0, CV_THRESH_TOZERO);
	//cv::imshow("apariciones",resultanteDeComparaciones);
	//cv::waitKey();
	double valorMinimo;
	double valorMaximo=kValorMinimoDeSimilitud;
	cv::Point puntoMinimo(0,0), puntoMaximo(0,0);
	bool similitudesProcesadas=false;
	//itero obteniendo todos los puntos de maxima hasta que el punto obtenido sea el maximo y no alcance el minimo de similitud.
	while (!similitudesProcesadas){
		cv::minMaxLoc(resultanteDeComparaciones, &valorMinimo, &valorMaximo, &puntoMinimo, &puntoMaximo);
		//elimino el residuo de similitud en las cercanias de esta similitud
		cv::floodFill(resultanteDeComparaciones, puntoMaximo, cv::Scalar(0), 0, cv::Scalar(kValorMinimoDeSimilitudDeZonaCercanaAUnaSimilitd), cv::Scalar(0.0));
		if (valorMaximo>=kValorMinimoDeSimilitud)
			++apariciones;
		else
			similitudesProcesadas=true;
	}
	return apariciones; //retorno las aparicion restando la primera iteracion que no se verifica.
}

const unsigned long int Imagen::contarAparicionesFeatureMatching(const Imagen& imagenObjeto)const{
	//Busco los puntos de interes de ambas imagenes.
	cv::Ptr<cv::xfeatures2d::SURF> detectorDePuntosDeInteres = cv::xfeatures2d::SURF::create(500,4,2,true,true);
	std::vector<cv::KeyPoint> puntosDeInteresEscena, puntosDeInteresObjeto;
	detectorDePuntosDeInteres->detect(matrizImagen, puntosDeInteresEscena);
	detectorDePuntosDeInteres->detect(imagenObjeto.matrizImagen, puntosDeInteresObjeto);

	//Obtengo las descripciones de todos los puntos e interes.
	cv::Ptr<cv::xfeatures2d::SurfDescriptorExtractor> descriptorDePuntosDeInteres= cv::xfeatures2d::SurfDescriptorExtractor::create();
	cv::Mat descripcionPuntosDeInteresEscena, descripcionPuntosDeInteresObjeto;
	descriptorDePuntosDeInteres->compute(matrizImagen, puntosDeInteresEscena, descripcionPuntosDeInteresEscena);
	descriptorDePuntosDeInteres->compute(imagenObjeto.matrizImagen, puntosDeInteresObjeto, descripcionPuntosDeInteresObjeto);

	//Comparo las descripciones y almaceno los resultados
	cv::BFMatcher comparadorDeDescripciones(cv::NORM_L2);
	std::vector< std::vector<cv::DMatch> > coincidenciasPuntosDeInteres;
	comparadorDeDescripciones.radiusMatch( descripcionPuntosDeInteresObjeto,descripcionPuntosDeInteresEscena, coincidenciasPuntosDeInteres,0.8);

	std::vector<cv::KeyPoint> puntosDeInteresCoincidentes;

	unsigned long int cantidadDeCoincidencias=0;

	cv::Mat1f samples( coincidenciasPuntosDeInteres.size(), 2 );
	cv::Mat1f centers( coincidenciasPuntosDeInteres.size(), 2 );
	centers.setTo(0);

	unsigned int i=0;
	for (std::vector< std::vector<cv::DMatch> >::const_iterator iteradorPuntosEscena = coincidenciasPuntosDeInteres.begin();iteradorPuntosEscena!=coincidenciasPuntosDeInteres.end();++iteradorPuntosEscena){
		//if (cantidadDeCoincidencias<(*iteradorPuntosEscena).size())
			cantidadDeCoincidencias+=(*iteradorPuntosEscena).size();

		for (std::vector<cv::DMatch>::const_iterator iteradorCoincidenciasPunto= (*iteradorPuntosEscena).begin(); iteradorCoincidenciasPunto!=(*iteradorPuntosEscena).end();++iteradorCoincidenciasPunto){
			puntosDeInteresCoincidentes.push_back(puntosDeInteresEscena.at((*iteradorCoincidenciasPunto).trainIdx));
			samples(i,0) = puntosDeInteresEscena.at((*iteradorCoincidenciasPunto).trainIdx).pt.x;
			samples(i,1) = puntosDeInteresEscena.at((*iteradorCoincidenciasPunto).trainIdx).pt.y;
			++i;
		}
	}

	unsigned long int cantidadPromedioDeApariciones=std::ceil((float)cantidadDeCoincidencias/(float)coincidenciasPuntosDeInteres.size());

	cv::Mat iamgenConKPPIntados;

	cv::flann::KMeansIndexParams kmean_params;
	unsigned long int numeroDeClustersReales = 0;//cv::flann::hierarchicalClustering< cv::L2<float> >(samples,centers,kmean_params);

	std::stringstream parseador;
		parseador << "Objetos detectados: "<<cantidadPromedioDeApariciones<<" , por clustering jerarquico: "<<numeroDeClustersReales;



	cv::drawKeypoints(matrizImagen,puntosDeInteresCoincidentes,iamgenConKPPIntados);
	cv::imshow(parseador.str(),iamgenConKPPIntados);
	cv::waitKey();

	return 0;
}

void Imagen::mostrarImagen() const{
	cv::namedWindow("Display Image", CV_WINDOW_AUTOSIZE);
	cv::imshow("Display Image", this->matrizImagen);
	cv::waitKey(5000);
}

} /* namespace common */
