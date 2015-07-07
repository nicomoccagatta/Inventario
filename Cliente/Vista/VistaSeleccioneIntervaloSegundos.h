/*
 * VistaSeleccioneFPS.h
 *
 *  Created on: Jun 30, 2015
 *      Author: ale
 */

#ifndef CLIENTE_VISTA_VISTASELECCIONEINTERVALOSEGUNDOS_H_
#define CLIENTE_VISTA_VISTASELECCIONEINTERVALOSEGUNDOS_H_

#include <gtkmm-2.4/gtkmm.h>
#include <gtkmm/dialog.h>

class VistaSeleccioneIntervaloSegundos: public Gtk::Dialog {
public:
	VistaSeleccioneIntervaloSegundos();
	virtual ~VistaSeleccioneIntervaloSegundos(){}

	int correr();

private:
	Gtk::Entry segs;
	Gtk::VBox* vbox;
	Gtk::Button ok;

	void on_button_OK();
};

#endif /* CLIENTE_VISTA_VISTASELECCIONEINTERVALOSEGUNDOS_H_ */
