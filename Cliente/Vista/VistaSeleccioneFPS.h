/*
 * VistaSeleccioneFPS.h
 *
 *  Created on: Jun 30, 2015
 *      Author: ale
 */

#ifndef CLIENTE_VISTA_VISTASELECCIONEFPS_H_
#define CLIENTE_VISTA_VISTASELECCIONEFPS_H_

#include <gtkmm-2.4/gtkmm.h>
#include <gtkmm/dialog.h>

class VistaSeleccioneFPS: public Gtk::Dialog {
public:
	VistaSeleccioneFPS();
	virtual ~VistaSeleccioneFPS(){}

	int correr();

private:
	Gtk::Entry fps;
	Gtk::VBox* vbox;
	Gtk::Button ok;

	void on_button_OK();
};

#endif /* CLIENTE_VISTA_VISTASELECCIONEFPS_H_ */
