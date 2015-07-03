/*
 * CotroladorVistaEnviar.h
 *
 *  Created on: Jun 14, 2015
 *      Author: ale
 */

#ifndef CLIENTE_CONTROL_CLIENT_CONTROLADORVISTAENVIAR_H_
#define CLIENTE_CONTROL_CLIENT_CONTROLADORVISTAENVIAR_H_

#include <glibmm-2.4/glibmm.h>

#include "../Modelo/client_ModeloObservable.h"
#include "common_AreaDeVision.h"

class VistaEnviar;

class ControladorVistaEnviar {

	ModeloObservable* modelo;
	VistaEnviar* vista;

public:
	ControladorVistaEnviar(ModeloObservable* modelo,VistaEnviar* vista) {
		this->modelo = modelo;
		this->vista = vista;
	}
	virtual ~ControladorVistaEnviar(){}

	void buttonVistaPreviaClicked(Glib::ustring rutaArchivo);
	void buttonENVIARClicked(Glib::ustring rutaArchivo,Glib::Date* fecha,
			Glib::ustring horas,Glib::ustring minutos, Glib::ustring segundos,
			int matching,AreaDeVision* area);

private:
	void aStructTime(Glib::Date* fecha,
		Glib::ustring horas,Glib::ustring minutos,Glib::ustring segundos,
		struct tm& time);
};

#endif /* CLIENTE_CONTROL_CLIENT_CONTROLADORVISTAENVIAR_H_ */
