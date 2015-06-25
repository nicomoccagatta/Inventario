#include "common_Video.h"

namespace common {

Video::Video(const std::string& rutaArchivo):capturasVideo(rutaArchivo)  {}

bool Video::esValido()const{
	return capturasVideo.isOpened();
}

//Completa la lista de imagenes y strings con las imagenes separadas por un periodo en segundos dado por periodoEnSegundos, completando en el mismo orden la lista de string con las fechas de esas imagenes teniendo en cuenta la fechaInicial como la de la primera imagen del video.
void Video::capturasPeriodicasVideo(std::list<Imagen>& listaImagenes,std::list<std::string>& listaDeFechas,const std::string& fechaInicial, float periodoEnSegundos){
	struct tm fechaProcesada;
	if(esValido()&& strptime(fechaInicial.c_str(),kFormatoFecha,&fechaProcesada)){
		double fps = capturasVideo.get(CV_CAP_PROP_FPS);
		unsigned long int cantidadDeFrames =  capturasVideo.get(CV_CAP_PROP_FRAME_COUNT);
		unsigned long int cantidadImagenesARetornar= std::floor(cantidadDeFrames/(fps*60))+1;
		float periodoEntreFrames = 1/fps;
		bool cambioDeFrame=true;
		cv::Mat frame;
		capturasVideo.set(CV_CAP_PROP_POS_AVI_RATIO,0);
		capturasVideo >>frame;
		float segundosParcialesProcesados=periodoEntreFrames;
		for (unsigned long int i=0;i<cantidadImagenesARetornar;++i){
			if (cambioDeFrame){
				listaImagenes.push_back(Imagen(frame.clone()));
				mktime(&fechaProcesada);
				std::string fechaImagen(asctime(&fechaProcesada));
				fechaImagen.erase(fechaImagen.find('\n'));
				listaDeFechas.push_back(fechaImagen);
				++fechaProcesada.tm_min;
				cambioDeFrame=false;
			}
			while (segundosParcialesProcesados<periodoEnSegundos){
				capturasVideo >> frame;
				cambioDeFrame=true;
				segundosParcialesProcesados+=periodoEntreFrames;
			}
			segundosParcialesProcesados-=periodoEnSegundos;
		}
	}
}

bool Video::setearSecuenciaDeImagenes(std::string templateImagenes, double fps){
	capturasVideo.open(templateImagenes);
	capturasVideo.set(CV_CAP_PROP_FPS,fps);
	return this->esValido();
}

void Video::mostrarVideo(){
	using namespace cv;
	Mat image;
	namedWindow("Image sequence | press ESC to close", WINDOW_KEEPRATIO);

	double fps = capturasVideo.get(CV_CAP_PROP_FPS);

	while (true){
		// Read in image from sequence
		capturasVideo >> image;

		// If no image was retrieved -> end of sequence
		if(image.empty())
		{
			std::cout << "End of Sequence" << std::endl;
			capturasVideo.set(CAP_PROP_POS_MSEC,0);
			continue;
		}

		imshow("Image sequence | press ESC to close", image);

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
				switch((char)waitKey(0)){
				case ' ':
					break;
				case 27:
					destroyAllWindows();
					return;
				}
			}
		}

	}
}


} /* namespace common */
