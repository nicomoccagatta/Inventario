#ifndef COMMON_IMAGEN_H_
#define COMMON_IMAGEN_H_

#include "opencv.hpp"
#include <cv.h>
#include <highgui.h>
#include <vector>
#include <string>

namespace common {

class Imagen {
public:
	Imagen(const std::string& rutaArchivo);
	Imagen(const unsigned int ancho,const unsigned int alto, const uchar* informacionDeImagen);
	void guardarEnArchivo(const std::string& rutaArchivo) const;
	const uchar* convertirABytesDinamicos();
	const unsigned int getTamanio()const;

private:
	cv::Mat matrizImagen;
};

} /* namespace common */

#endif /* COMMON_IMAGEN_H_ */
