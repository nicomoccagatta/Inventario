/*
 * VistaStockGeneral.h
 *
 *  Created on: 23/6/2015
 *      Author: nicomoccagatta
 */

#ifndef ADMINISTRADOR_VISTAADMIN_VISTASTOCKGENERAL_H_
#define ADMINISTRADOR_VISTAADMIN_VISTASTOCKGENERAL_H_

#include <gtkmm-2.4/gtkmm.h>
#include "ModeloAdmin/admin_ModeloObservable.h"
#include "ListaProductos.h"
#include <list>
#include "common_Producto.h"

class VistaStockGeneral : public Observer {
	Modelo_Observable *modelo;
	Gtk::Viewport *panelDinam;
	void update_lista_productos();

	Glib::RefPtr<Gtk::ListStore> m_refProductosListStore;
	Gtk::TreeView m_ProductosTreeView;
	ListaProductos m_ProductosList;

	Gtk::HBox m_HBoxGrillaEImagen;
	Gtk::DrawingArea m_ImagenItem;
public:
	VistaStockGeneral();
	void update();
	void run(Gtk::Viewport *panelDinamico,Modelo_Observable *modelo);
	virtual ~VistaStockGeneral();
};

#endif /* ADMINISTRADOR_VISTAADMIN_VISTASTOCKGENERAL_H_ */
