/*
 * client_VistaPrincipal.h
 *
 *  Created on: Jun 20, 2015
 *      Author: ale
 */

#ifndef CLIENTE_VISTA_CLIENT_VISTAPRINCIPAL_H_
#define CLIENTE_VISTA_CLIENT_VISTAPRINCIPAL_H_

#include <gtkmm-2.4/gtkmm.h>
#include <glibmm-2.4/glibmm.h>

/*
 * A CAMBIAR POR PANELES CON PESTANIAS.
 * Es la ventana principal que contiene a las otras tres vistas.
 */
class VistaPrincipal: public Gtk::Window {
public:
	VistaPrincipal(BaseObjectType* cobject,
			const Glib::RefPtr<Gtk::Builder>& refGlade);
	virtual ~VistaPrincipal();

private:
	//signal handlers:
	void on_button_Enviar();
	void on_button_Descargar();
	void on_button_CrearVideo();
	bool on_exit_clicked(GdkEventAny* event);

	Glib::RefPtr<Gtk::Builder> m_refGlade;
	Gtk::Button* m_EnviarButton;
	Gtk::Button* m_DescargarButton;
	Gtk::Button* m_CrearVideoButton;

	Gtk::VBox* m_bottonesBox;
};

#endif /* CLIENTE_VISTA_CLIENT_VISTAPRINCIPAL_H_ */
