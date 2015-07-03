/*
 * VistaPreviaImagen.h
 *
 *  Created on: Jul 3, 2015
 *      Author: ale
 */

#ifndef CLIENTE_VISTA_VISTAPREVIAIMAGEN_H_
#define CLIENTE_VISTA_VISTAPREVIAIMAGEN_H_

#include <gtkmm/dialog.h>
#include <gtkmm/box.h>
#include <gtkmm/image.h>

class VistaPreviaImagen: public Gtk::Dialog {
public:
	VistaPreviaImagen(Glib::ustring ruta);
	virtual ~VistaPreviaImagen();

	int correr();

private:
	Gtk::VBox* vbox;
	Gtk::HButtonBox buttonBox;
	Gtk::Button ok;
	Gtk::Image imagen;

	void on_button_OK();
};

#endif /* CLIENTE_VISTA_VISTAPREVIAIMAGEN_H_ */
