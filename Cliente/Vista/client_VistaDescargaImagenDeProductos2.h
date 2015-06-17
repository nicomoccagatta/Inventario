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

class VistaDescargaImagenDeProductos2: public Gtk::Window {

	ModeloObservable* modelo;
	//ControladorVistaDescargaImagenDeProductos* controlador;

public:
	VistaDescargaImagenDeProductos2(ModeloObservable* modelo);
	virtual ~VistaDescargaImagenDeProductos2();

	void asignarModelo(ModeloObservable* modelo);
	//void asignarControlador(ControladorVistaDescargaImagenDeProductos* controlador);

private:
	void update();

	bool on_imagen_button_press(GdkEventButton*);

	void on_producto_seleccionado();

	void ponerImagenesSeleccion();

protected:
	//signal handlers:
	void on_button_atras();
	void on_button_descargar();

	Gtk::HPaned m_hPaned;

	ProductosList m_ProductosList;

	Gtk::VBox m_VBox;
	Gtk::HBox m_HBoxImagenes;
	Gtk::HButtonBox m_ButtonBox;

	Gtk::Button m_AtrasButton;
	Gtk::Button m_DescargarButton;

	//const GdkColor color;
	Gtk::RadioButtonGroup radioGroup;


};

#endif /* CLIENTE_VISTA_CLIENT_VISTADESCARGAIMAGENDEPRODUCTOS_H_ */
