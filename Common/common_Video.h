#ifndef COMMON_VIDEO_H_
#define COMMON_VIDEO_H_

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include "opencv2/videoio.hpp"
#include <list>
#include <ctime>
#include "common_Imagen.h"
#define kFormatoFecha "%a %b %d %H:%M:%S %Y"

using common::Imagen;

namespace common {

class Video {
public:
	Video(const std::string& rutaArchivo);
	Video();

	/*image sequence (eg. img_%02d.jpg, which will read samples like
	 * img_00.jpg, img_01.jpg, img_02.jpg, ...)*/
	bool setearSecuenciaDeImagenes(std::string templateImagenes);
	bool esValido()const;
	void capturasPeriodicasVideo(std::list<Imagen>& listaImagenes,std::list<std::string>& listaDeFechas,const std::string& fechaInicial , float periodoEnSegundos=60);

	void mostrarVideo(double fps);

private:
	cv::VideoCapture capturasVideo;
};

} /* namespace common */

#endif /* COMMON_VIDEO_H_ */
