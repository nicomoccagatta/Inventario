/*
 * common_Imagen.cpp
 *
 *  Created on: Jun 12, 2015
 *      Author: leandro
 */

#include <opencv2/opencv.hpp>

#include "common_Imagen.h"

namespace common {

Imagen::Imagen(const std::string& rutaArchivo): matrizImagen(cv::imread(rutaArchivo,1)) {
	if (matrizImagen.empty())
		throw "ERROR: No es posible cargar la imagen";
}

//constructor para imagenes enviadas por red (BETA)
Imagen::Imagen(const unsigned int alto,const unsigned int ancho, const uchar* informacionDeImagen){
	matrizImagen=cv::Mat::ones(alto,ancho, CV_8UC3);
	unsigned long int ptr=0;
	 for (unsigned int i = 0;  i < alto; i++) {
	  for (unsigned int j = 0; j < ancho; j++) {
		  matrizImagen.at<cv::Vec3b>(i,j) = cv::Vec3b(informacionDeImagen[ptr+ 0],informacionDeImagen[ptr+1],informacionDeImagen[ptr+2]);
		  ptr+=3;
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

const uchar* const Imagen::obtenerBytesDinamicos() const{
	cv::Mat matrizTransformada=matrizImagen.reshape(0,1);
	uchar* bytesARetornar= new uchar[getTamanio()];
	memcpy(bytesARetornar,matrizTransformada.data,(unsigned int) (getTamanio()));
	return bytesARetornar;
}

const unsigned long int Imagen::getTamanio()const{
	return matrizImagen.total()*matrizImagen.elemSize();
}

void Imagen::mostrarImagen(){
	using namespace cv;

	//CascadeClassifier face_cascade;
	//loadClassifier(face_cascade);
	//markFaces(face_cascade, this->matrizImagen);

	namedWindow("Display Image", CV_WINDOW_AUTOSIZE);
	imshow("Display Image", this->matrizImagen);

const unsigned int Imagen::getAlto()const{
	return matrizImagen.rows;
}

const unsigned int Imagen::getAncho()const{
	return matrizImagen.cols;
}

const bool Imagen::existeImagen(const std::string& rutaArchivoImagen){
	return !((cv::imread(rutaArchivoImagen,1)).empty());
}

const bool Imagen::esValida()const{
	return !matrizImagen.empty();
}

} /* namespace common */
