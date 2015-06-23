#include "common_Video.h"

namespace common {

Video::Video(const std::string& rutaArchivo):capturasVideo(rutaArchivo)  {}

bool Video::esValido()const{
	return capturasVideo.isOpened();
}

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

} /* namespace common */
