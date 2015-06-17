/*
 * VistaVentanaPPAL.h
 *
 *  Created on: 16/6/2015
 *      Author: nicomoccagatta
 */

#ifndef ADMINISTRADOR_VISTAADMIN_VISTAVENTANAPPAL_H_
#define ADMINISTRADOR_VISTAADMIN_VISTAVENTANAPPAL_H_

#include <gtkmm-2.4/gtkmm/window.h>
#include "ModeloAdmin/admin_ModeloObservable.h"
#include "ModeloAdmin/admin_Observer.h"

class VistaVentanaPPAL: public Gtk::Window, public Observer {
public:
	VistaVentanaPPAL(Modelo_Observable *modelo);
	virtual ~VistaVentanaPPAL();
private:
	Modelo_Observable *model;
};

#endif /* ADMINISTRADOR_VISTAADMIN_VISTAVENTANAPPAL_H_ */
