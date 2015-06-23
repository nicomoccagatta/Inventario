/*
 * admin_ControlAP.h
 *
 *  Created on: 22/6/2015
 *      Author: nicomoccagatta
 */

#ifndef ADMINISTRADOR_CONTROLADMIN_ADMIN_CONTROLAP_H_
#define ADMINISTRADOR_CONTROLADMIN_ADMIN_CONTROLAP_H_

#include <gtkmm-2.4/gtkmm.h>

class ControlAP {
	Gtk::Button *boton;
	void *vista;
public:
	ControlAP(Gtk::Button *button,void *view);
	void on_button_eliminarIcono();
	virtual ~ControlAP();
};

#endif /* ADMINISTRADOR_CONTROLADMIN_ADMIN_CONTROLAP_H_ */
