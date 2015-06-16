/*
 * client_VistaDescargaImagenDeProductos.h
 *
 *  Created on: Jun 15, 2015
 *      Author: ale
 */

#ifndef CLIENTE_VISTA_CLIENT_VISTADESCARGAIMAGENDEPRODUCTOS_H_
#define CLIENTE_VISTA_CLIENT_VISTADESCARGAIMAGENDEPRODUCTOS_H_

#include <gtkmm-2.4/gtkmm.h>
#include <glibmm-2.4/glibmm.h>
#include <iostream>

#include "client_ProductosList.h"

//#include "../Control/client_ControladorVistaDescargaImagenDeProductos.h"
#include "../Modelo/client_ModeloObservable.h"

class VistaDescargaImagenDeProductos: public Gtk::Window {

	ModeloObservable* modelo;
	//ControladorVistaDescargaImagenDeProductos* controlador;

public:
	VistaDescargaImagenDeProductos(BaseObjectType* cobject,
			const Glib::RefPtr<Gtk::Builder>& refGlade);
	virtual ~VistaDescargaImagenDeProductos();

	void asignarModelo(ModeloObservable* modelo);
	//void asignarControlador(ControladorVistaDescargaImagenDeProductos* controlador);

private:
	void update();

protected:
	//signal handlers:
	void on_button_atras();
	void on_button_descargar();


	Glib::RefPtr<Gtk::Builder> m_refGlade;
	Gtk::Button* m_atrasButton;
	Gtk::Button* m_descargarButton;

	Gtk::Viewport* m_viewport;
	//Gtk::VBox* m_productosVBox;
	Gtk::HPaned* m_hPaned;

	ProductosList m_ProductosList;

	Gtk::VBox m_productosVbox;

};

#endif /* CLIENTE_VISTA_CLIENT_VISTADESCARGAIMAGENDEPRODUCTOS_H_ */
