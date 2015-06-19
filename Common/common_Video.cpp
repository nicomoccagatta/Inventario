#include "common_Video.h"

namespace common {

Video::Video(const std::string& rutaArchivo):capturasVideo(rutaArchivo)  {}

bool Video::esValido()const{
	return capturasVideo.isOpened();
}

void Video::capturasPeriodicasVideo(std::list<const Imagen>& listaImagenes, double periodoEnMinutos)const{
	double fps = capturasVideo.get(CV_CAP_PROP_FPS);
	unsigned long int cantidadDeFrames =  capturasVideo.get(CV_CAP_PROP_FRAME_COUNT);
	double duracionTotalEnMinutos = (cantidadDeFrames/(fps*60));

}

} /* namespace common */
