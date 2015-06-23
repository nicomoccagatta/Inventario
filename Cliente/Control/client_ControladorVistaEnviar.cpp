/*
 * CotroladorVistaEnviar.cpp
 *
 *  Created on: Jun 14, 2015
 *      Author: ale
 */

#include <glibmm-2.4/glibmm.h>
#include <sstream>
#include <ctime>

#include "client_ControladorVistaEnviar.h"
#include "common_Imagen.h"

#define FEATURE_MATCHING 1
#define TEMPLATE_MATCHING 2

void ControladorVistaEnviar::buttonVistaPreviaClicked(Glib::ustring rutaArchivo){

	//if es una extencion de imagen

	common::Imagen imagen(rutaArchivo);

	imagen.mostrarImagen();


	//if es una extencion de video

	//...
}
//Tue Jun 9 16:40:47 2015
void ControladorVistaEnviar::buttonENVIARClicked(Glib::ustring rutaArchivo,Glib::Date* fecha,
		Glib::ustring horas,Glib::ustring minutos,Glib::ustring segundos,
		int matching,AreaDeVision* area){

	struct tm time;

	this->aStructTime(fecha, horas, minutos, segundos, time);

	std::cerr << horas << minutos << segundos << std::endl;

	std::cerr << asctime(&time);

	std::string formatoFecha(asctime(&time));

	formatoFecha.erase(formatoFecha.find('\n'));

	std::string rutaImagen(rutaArchivo.c_str());

	std::stringstream iss(rutaImagen);
	std::string item;
	std::string extencion;

	std::getline(iss, item, '.');
	std::getline(iss, extencion, '.');

	std::cerr << "La extencion es: " << extencion << "\n";

	if (extencion == "jpg" || extencion == "png"){
		switch(matching){
		case TEMPLATE_MATCHING:
			modelo->enviarFotoTemplateMatching(area->getId(), formatoFecha, rutaImagen);
			break;
		case FEATURE_MATCHING:
			modelo->enviarFotoFeatureMatching(area->getId(), formatoFecha, rutaImagen);
			break;
		}
	}

	if (extencion == "mpg" || extencion == "mpeg" || extencion == "mp4"){
		std::cerr << "Se ingreso un video!!\n";
		switch(matching){
		case TEMPLATE_MATCHING:
			//modelo->enviarVideoTemplateMatching(area->getId(), formatoFecha, rutaImagen);
			break;
		case FEATURE_MATCHING:
			//modelo->enviarVideoFeatureMatching(area->getId(), formatoFecha, rutaImagen);
			break;
		}

	}

}


void ControladorVistaEnviar::aStructTime(Glib::Date* fecha,
		Glib::ustring horas,Glib::ustring minutos,Glib::ustring segundos,
		struct tm& time){

	fecha->to_struct_tm(time);

	std::stringstream ss;
	ss << horas;
	ss >> time.tm_hour;
	ss.clear();
	ss.flush();
	ss.str("");
	ss << minutos;
	ss >> time.tm_min;
	ss.clear();
	ss.flush();
	ss.str("");
	ss << segundos;
	ss >> time.tm_sec;
}
