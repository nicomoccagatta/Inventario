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

class ControladorVistaEnviar {

	ModeloObservable* modelo;

public:
	ControladorVistaEnviar(ModeloObservable* modelo) {
		this->modelo = modelo;
	}
	virtual ~ControladorVistaEnviar(){}

	//void buttonENVIARClicked(...);
	void buttonVistaPreviaClicked(Glib::ustring rutaArchivo);
};

#endif /* CLIENTE_CONTROL_CLIENT_CONTROLADORVISTAENVIAR_H_ */
