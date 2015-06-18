/*
 * VistaListadoProductos.h
 *
 *  Created on: 17/6/2015
 *      Author: nicomoccagatta
 */

#ifndef ADMINISTRADOR_VISTAADMIN_VISTALISTADOPRODUCTOS_H_
#define ADMINISTRADOR_VISTAADMIN_VISTALISTADOPRODUCTOS_H_

#include <gtkmm-2.4/gtkmm.h>
#include "ModeloAdmin/admin_ModeloObservable.h"
#include "ListaProductos.h"
#include <list>
#include "common_Producto.h"

class VistaListadoProductos : public Observer {
	Modelo_Observable *modelo;
	Gtk::Viewport *panelDinam;
	void update_lista_productos();
	bool on_imagen_button_press(GdkEventButton*);
	void on_producto_seleccionado();
	void on_button_editar();
	void on_button_eliminar();
public:
	void update();
	void setearAtributos(Gtk::Viewport *panelDinamico,Modelo_Observable *modelo);
	void run();
	virtual ~VistaListadoProductos();
protected:
	Glib::RefPtr<Gtk::ListStore> m_refProductosListStore; //The Tree Model.
	Gtk::TreeView m_ProductosTreeView; //The Tree View.
	Glib::RefPtr<Gtk::TreeSelection> refTreeSelection; //The selected

	Gtk::HBox horizontalBox;
	Gtk::VBox m_imagenPlusBotones;
	Gtk::Image* m_imagenItem;
	ListaProductos m_ProductosList;
	Gtk::VButtonBox m_ButtonBox;
	Gtk::Button m_EditarButton;
	Gtk::Button m_EliminarButton;
};

#endif /* ADMINISTRADOR_VISTAADMIN_VISTALISTADOPRODUCTOS_H_ */
