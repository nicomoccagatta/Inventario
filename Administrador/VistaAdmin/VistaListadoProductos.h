/*
 * VistaListadoProductos.h
 *
 *  Created on: 17/6/2015
 *      Author: nicomoccagatta
 */

#ifndef ADMINISTRADOR_VISTAADMIN_VISTALISTADOPRODUCTOS_H_
#define ADMINISTRADOR_VISTAADMIN_VISTALISTADOPRODUCTOS_H_

#include <gtkmm-2.4/gtkmm.h>
#include "ModeloAdmin/admin_ModeloObservable.h"
#include <list>
#include "common_Producto.h"

class VistaListadoProductos : public Observer {
	Modelo_Observable *model;
	Gtk::Viewport *vista;
	const std::list<Producto*>* productos;
public:
	void update();
	void setearAtributos(Gtk::Viewport *panelDinamico,Modelo_Observable *modelo);
	void run();
	virtual ~VistaListadoProductos();
};

#endif /* ADMINISTRADOR_VISTAADMIN_VISTALISTADOPRODUCTOS_H_ */
