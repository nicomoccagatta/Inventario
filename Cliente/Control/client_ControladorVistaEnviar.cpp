/*
 * CotroladorVistaEnviar.cpp
 *
 *  Created on: Jun 14, 2015
 *      Author: ale
 */

#include <glibmm-2.4/glibmm.h>

#include "client_ControladorVistaEnviar.h"
#include "common_Imagen.h"


void ControladorVistaEnviar::buttonVistaPreviaClicked(Glib::ustring rutaArchivo){

	//if es una extencion de imagen

	common::Imagen imagen(rutaArchivo);

	imagen.mostrarImagen();


	//if es una extencion de video

	//...
}
