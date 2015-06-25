#ifndef COMMON_IMAGEN_H_
#define COMMON_IMAGEN_H_

#include "opencv2/opencv.hpp"
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv2/xfeatures2d.hpp>
#include <vector>
#include <string>
#include <cmath>
#define kValorMinimoDeSimilitud 0.8
#define kValorMinimoDeSimilitudDeZonaCercanaAUnaSimilitud 0.2
#define kMetodoTemplateMatching CV_TM_CCOEFF_NORMED
#define kDistanciaFeatureMatching cv::NORM_L2
#define kValorMinimoHessianoSURFFeatureMatching 300
#define kDistanciaMaximaDeSimilitudFeatureMatching 0.18
#define kTituloPorDefaultVentanaMostrarImagen "Display Image"


namespace common {

class Imagen {
public:
	Imagen(const std::string& rutaArchivo);
	Imagen(const cv::Mat matrizImagen);
	Imagen(const unsigned int ancho,const unsigned int alto, const uchar* informacionDeImagen);
	void guardarEnArchivo(const std::string& rutaArchivo) const;
	const uchar* const obtenerBytesDinamicos()const;
	const unsigned long int getTamanio()const;
	const unsigned int getAlto()const;
	const unsigned int getAncho()const;
	const bool esValida()const;
	const unsigned long int contarApariciones(const Imagen& imagenObjeto,const std::string& tipoDeteccion)const;
	void mostrarImagen(const std::string& tituloVentana=kTituloPorDefaultVentanaMostrarImagen) const;
	static const bool existeImagen(const std::string& rutaArchivoImagen);
	static void setearPatametros(float valorMinimoDeSimilitudTemplateMatching=kValorMinimoDeSimilitud,float valorMinimoDeSimilitudDeZonaCercanaAUnaSimilitud=kValorMinimoDeSimilitudDeZonaCercanaAUnaSimilitud,unsigned long int valorMinimoHessianoSURFFeatureMatching=kValorMinimoHessianoSURFFeatureMatching,float distanciaMaximaDeSimilitudFeatureMatching=kDistanciaMaximaDeSimilitudFeatureMatching);

private:
	cv::Mat matrizImagen;
	const unsigned long int contarAparicionesTemplateMatching(const Imagen& imagenObjeto)const;
	const unsigned long int contarAparicionesFeatureMatching(const Imagen& imagenObjeto)const;
	static float valorMinimoDeSimilitudTemplateMatching;
	static float valorMinimoDeSimilitudDeZonaCercanaAUnaSimilitud;
	static unsigned long int valorMinimoHessianoSURFFeatureMatching;
	static float distanciaMaximaDeSimilitudFeatureMatching;

};

} /* namespace common */

#endif /* COMMON_IMAGEN_H_ */
