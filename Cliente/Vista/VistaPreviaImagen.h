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

/*
 * Dialogo para mostrar una imagen.
 */
class VistaPreviaImagen: public Gtk::Dialog {
public:
	VistaPreviaImagen(Glib::ustring ruta);
	virtual ~VistaPreviaImagen();

	/*
	 * Se inicia el dialogo, si se apreta la cruz retorna la senal
	 * Gtk::RESPONSE_DELETE_EVENT, sino 0.
	 */
	int correr();

private:
	Gtk::VBox* vbox;
	Gtk::HButtonBox buttonBox;
	Gtk::Button ok;
	Gtk::Image imagen;

	/*
	 * Sale
	 */
	void on_button_OK();
};

#endif /* CLIENTE_VISTA_VISTAPREVIAIMAGEN_H_ */
