/*
 * common_Imagen.cpp
 *
 *  Created on: Jun 12, 2015
 *      Author: leandro
 */

#include "common_Imagen.h"

namespace common {

Imagen::Imagen(const std::string& rutaArchivo): matrizImagen(cv::imread(rutaArchivo,1)) {
	if (matrizImagen.empty())
		throw "ERROR: No es posible cargar la imagen";
}

//constructor para imagenes enviadas por red (BETA)
Imagen::Imagen(const unsigned int ancho,const unsigned int alto, const uchar* informacionDeImagen): matrizImagen(cv::Mat::zeros( alto,ancho, CV_8UC3)){
	 int ptr=0;
	 for (int i = 0;  i < matrizImagen.rows; i++) {
	  for (int j = 0; j < matrizImagen.cols; j++) {
		  matrizImagen.at<cv::Vec3b>(i,j) = cv::Vec3b(informacionDeImagen[ptr+ 0],informacionDeImagen[ptr+1],informacionDeImagen[ptr+2]);
		  ptr=ptr+3;
	   }
	  }
}

void Imagen::guardarEnArchivo(const std::string& rutaArchivo) const{
	std::vector<int> parametros;
	parametros.push_back(100);
	try	{
		cv::imwrite(rutaArchivo,matrizImagen,parametros);
	} catch(...) {
		throw "ERROR: No es posible guardar la imagen";
	}
}

const uchar* Imagen::convertirABytesDinamicos(){
	return (matrizImagen=matrizImagen.reshape(0,1)).data;
}

const unsigned int Imagen::getTamanio()const{
	return matrizImagen.total()*matrizImagen.elemSize();
}

} /* namespace common */
