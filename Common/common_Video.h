#ifndef COMMON_VIDEO_H_
#define COMMON_VIDEO_H_

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include "opencv2/videoio.hpp"
#include <list>
#include <ctime>
#include <vector>
#include "common_Imagen.h"
#define kFormatoFecha "%a %b %d %H:%M:%S %Y"

using common::Imagen;

namespace common {

class Video {
public:
	/*Para crear con secuencia de imagenes*/
	Video(std::string templateImagenes, double fps);

	/*Para crear con archivo de video*/
	Video(const std::string& rutaArchivo);
	bool esValido()const;
	void capturasPeriodicasVideo(std::list<Imagen>& listaImagenes,std::list<std::string>& listaDeFechas,const std::string& fechaInicial , float periodoEnSegundos=60);
	void mostrarVideo();
	void guardar(std::string& rutaDestino);
	static void guardarAPartirDeImagenes(const std::string& rutaDestino, const std::vector<std::string>& rutas, const double fps);
private:
	cv::VideoCapture capturasVideo;
	double fps;
};

} /* namespace common */

#endif /* COMMON_VIDEO_H_ */
