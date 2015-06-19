#ifndef COMMON_IMAGEN_H_
#define COMMON_IMAGEN_H_

#include "opencv.hpp"
#include <cv.h>
#include <highgui.h>
#include <vector>
#include <string>
#define kValorMinimoDeSimilitud 0.8
#define kValorMinimoDeSimilitudDeZonaCercanaAUnaSimilitd 0.2
#define kMetodoTemplateMatching CV_TM_CCOEFF_NORMED


namespace common {

class Imagen {
public:
	Imagen(const std::string& rutaArchivo);
	Imagen(const unsigned int ancho,const unsigned int alto, const uchar* informacionDeImagen);
	void guardarEnArchivo(const std::string& rutaArchivo) const;
	const uchar* const obtenerBytesDinamicos()const;
	const unsigned long int getTamanio()const;
	const unsigned int getAlto()const;
	const unsigned int getAncho()const;
	const bool esValida()const;
	static const bool existeImagen(const std::string& rutaArchivoImagen);
	const unsigned long int contarApariciones(const Imagen& imagenObjeto,const std::string& tipoDeteccion)const;
	void mostrarImagen();


private:
	cv::Mat matrizImagen;
	const unsigned long int contarAparicionesTemplateMatching(const Imagen& imagenObjeto)const;
	const unsigned long int contarAparicionesFeatureMatching(const Imagen& imagenObjeto)const;

};

} /* namespace common */

#endif /* COMMON_IMAGEN_H_ */
