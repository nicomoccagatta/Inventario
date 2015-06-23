/*
 * admin_ControlAP.cpp
 *
 *  Created on: 22/6/2015
 *      Author: nicomoccagatta
 */

#include "admin_ControlAP.h"
#include "VistaAdmin/VistaAgregarProducto.h"

ControlAP::ControlAP(Gtk::Button *button,void *view): boton(button), vista(view) {
}

void ControlAP::on_button_eliminarIcono(){
	((VistaAgregarProducto*)(vista))->eliminarIconoPertenecienteABoton(boton);
}

ControlAP::~ControlAP() {

}

