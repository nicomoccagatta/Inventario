#ifndef COMMON_VIDEO_H_
#define COMMON_VIDEO_H_

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include "opencv2/videoio.hpp"
#include <list>
#include "common_Imagen.h"

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
	void capturasPeriodicasVideo(std::list<const Imagen>& listaImagenes, double periodoEnMinutos=30)const;

	void mostrarVideo(double fps);

private:
	cv::VideoCapture capturasVideo;
};

} /* namespace common */

#endif /* COMMON_VIDEO_H_ */
