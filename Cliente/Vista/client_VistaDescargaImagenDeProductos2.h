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

//#include "../Control/client_ControladorVistaDescargaImagenDeProductos.h"

#include "../Control/client_ControladorVistaDescargaImagenDeProductos.h"
#include "../Modelo/client_ModeloObservable.h"
#include "common_ListaProductos.h"

class ControladorVistaDescargaImagenDeProductos;

/*
 * Es la Vista que permite ver las imagenes de cada producto y
 * descargar la que uno quiera.
 */
class VistaDescargaImagenDeProductos2: public Gtk::Viewport {

	ModeloObservable* modelo;
	ControladorVistaDescargaImagenDeProductos* controlador;

public:
	VistaDescargaImagenDeProductos2(BaseObjectType* cobject,
			const Glib::RefPtr<Gtk::Builder>& refGlade);
	virtual ~VistaDescargaImagenDeProductos2();

	void asignarModelo(ModeloObservable* modelo);
	//void asignarControlador(ControladorVistaDescargaImagenDeProductos* controlador);

	void update_lista_imagenes(std::list<unsigned long int>* ids,
			Gtk::ScrolledWindow* imagenes_container);

private:
	void update();
	void update_lista_productos();

	bool on_imagen_button_press(GdkEventButton*);

	void on_producto_seleccionado();

	void on_radioButton_toggled(Gtk::RadioButton* radio);


protected:
	//signal handlers:
	void on_button_atras();
	void on_button_descargar();

	Glib::RefPtr<Gtk::ListStore> m_refProductosListStore; //The Tree Model.
	Gtk::TreeView m_ProductosTreeView; //The Tree View.
	Glib::RefPtr<Gtk::TreeSelection> refTreeSelection; //The selected

	Gtk::HPaned m_hPaned; //El panel con la barra que divide

	//ProductosList m_ProductosList; //La Scrolled Window de los productos
	ListaProductos m_ProductosList;

	Gtk::VBox m_VBox; //Arriba imanes, abajo botones
	Gtk::ScrolledWindow* m_ActiveImagenes; //ScrolledWindow de imagenes activa
	Gtk::HButtonBox m_ButtonBox; //Para los botones atras y descargar


	Gtk::Button m_AtrasButton;
	Gtk::Button m_DescargarButton;

	//const GdkColor color;
	Gtk::RadioButtonGroup radioGroup; //de las imagenes
	Gtk::RadioButton* m_ActiveRadio; //La imagen clickeada activa

};

#endif /* CLIENTE_VISTA_CLIENT_VISTADESCARGAIMAGENDEPRODUCTOS_H_ */
