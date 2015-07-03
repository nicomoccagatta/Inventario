#include "common_Video.h"

namespace common {

Video::Video(std::string templateImagenes, double fps) :
	capturasVideo(templateImagenes), fps(fps){
	capturasVideo.set(CV_CAP_PROP_FPS,fps);
}

Video::Video(const std::string& rutaArchivo):capturasVideo(rutaArchivo)  {
	fps = capturasVideo.get(CV_CAP_PROP_FPS);
}

bool Video::esValido()const{
	return capturasVideo.isOpened();
}

//Completa la lista de imagenes y strings con las imagenes separadas por un periodo en segundos dado por periodoEnSegundos,
//completando en el mismo orden la lista de string con las fechas de esas imagenes teniendo en cuenta la fechaInicial como la de la primera imagen del video.
void Video::capturasPeriodicasVideo(std::list<Imagen>& listaImagenes,std::list<std::string>& listaDeFechas,
		const std::string& fechaInicial, float periodoFinalEnSegundos){//periodoFinalEnSegundos=60 por defecto
	struct tm fechaProcesada;
	if(esValido()&& strptime(fechaInicial.c_str(),kFormatoFecha,&fechaProcesada)){

		double fps = capturasVideo.get(CV_CAP_PROP_FPS);
		double fpsFinal = 1/periodoFinalEnSegundos;
		unsigned long int cantidadDeFrames =  capturasVideo.get(CV_CAP_PROP_FRAME_COUNT);
		double cantidadImagenesARetornar= std::floor(fpsFinal*cantidadDeFrames/fps);
		float periodoEntreFrames = 1/fps;
		bool cambioDeFrame=true;

		std::cerr << "FPS: " << fps << "\nCANTIDAD TOTAL DE FRAMES: " << cantidadDeFrames
				<< "\nCANTIDAD ESPERADA DE FRAMES A RETORNAR: " << cantidadImagenesARetornar
				<< "\nPERIODO ENTRE FRAMES REAL: " << periodoEntreFrames << "\n";


		cv::Mat frame;
		capturasVideo.set(CV_CAP_PROP_POS_AVI_RATIO,0);
		capturasVideo >>frame;

		/*
		 * Si el video es menor a el periodoFinalEnSegundos paso la primer imagen.
		 */
		if (cantidadImagenesARetornar==0)
			cantidadImagenesARetornar=1;

		float segundosParcialesProcesados=periodoEntreFrames;
		for (unsigned long int i=1;i<=cantidadImagenesARetornar;++i){
			if (cambioDeFrame){
				listaImagenes.push_back(Imagen(frame.clone()));
				mktime(&fechaProcesada);
				std::string fechaImagen(asctime(&fechaProcesada));
				fechaImagen.erase(fechaImagen.find('\n'));
				listaDeFechas.push_back(fechaImagen);

				//Le agrego a la fecha la cantidad de segundos que pasaron,
				//El mktime luego se encarga de arreglar los minutos en caso de que
				//queden segundos mayores a 60
				fechaProcesada.tm_sec += periodoFinalEnSegundos;


				cambioDeFrame=false;
			}
			while (segundosParcialesProcesados<periodoFinalEnSegundos){
				capturasVideo >> frame;
				cambioDeFrame=true;
				segundosParcialesProcesados+=periodoEntreFrames;
			}
			segundosParcialesProcesados-=periodoFinalEnSegundos;
		}
	}
}

void Video::mostrarVideo(){
	using namespace cv;
	Mat image;
	namedWindow("Vista previa video | precione Q para salir", WINDOW_KEEPRATIO | CV_GUI_NORMAL);

	std::cerr << "FPS: " << fps << std::endl;

	if (fps == 0)
		fps=1;

	while (true){
		// Read in image from sequence
		capturasVideo >> image;

		// If no image was retrieved -> end of sequence
		if(image.empty())
		{
			std::cerr << "End of Sequence" << std::endl;
			capturasVideo.set(CAP_PROP_POS_MSEC,0);
			continue; //para loop
			//break; //para reproducir una vez y salir
		}

		imshow("Vista previa video | precione Q para salir", image);

		char key = (char)waitKey(1000/fps); //delay N millis, usually long enough to display and capture input

		switch (key) {
		case 'q':
			destroyAllWindows();
			return;
		case 27: //escape key
			destroyAllWindows();
			return;
		case ' ': //
			while (true){
				char key = (char)waitKey(0);
				if(key == ' ')
					break;
				if(key == 'q'){
					destroyAllWindows();
					return;
				}
				if(key == 27){
					destroyAllWindows();
					return;
				}
			}
		}

	}
}


} /* namespace common */
