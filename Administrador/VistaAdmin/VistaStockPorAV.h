/*
 * VistaStockPorAV.h
 *
 *  Created on: 28/6/2015
 *      Author: nicomoccagatta
 */

#ifndef ADMINISTRADOR_VISTAADMIN_VISTASTOCKPORAV_H_
#define ADMINISTRADOR_VISTAADMIN_VISTASTOCKPORAV_H_

#include <gtkmm-2.4/gtkmm.h>
#include "ModeloAdmin/admin_ModeloObservable.h"
#include "ModelComboBoxAreasDeVision.h"
#include "ListaProductos.h"
#include <list>
#include "common_Producto.h"

class VistaStockPorAV : public Observer {
	Modelo_Observable *modelo;
	Gtk::Viewport *panelDinam;
	void update_lista_av();
	void update_lista_productos();

	Gtk::VButtonBox m_botoneraComboBox;
	Gtk::ComboBox m_AreasDeVision;
	AreasDeVisionComboBoxModel columnas;
	Glib::RefPtr<Gtk::ListStore> modeloComboBox;

	Glib::RefPtr<Gtk::ListStore> m_refProductosListStore;
	Gtk::TreeView m_ProductosTreeView;
	ListaProductos m_ProductosList;

	Gtk::VBox m_vBoxPrincipal;
	Gtk::HBox m_HBoxGrillaEImagen;
	Gtk::DrawingArea m_ImagenItem;
public:
	VistaStockPorAV();
	void update();
	void run(Gtk::Viewport *panelDinamico,Modelo_Observable *modelo);
	virtual ~VistaStockPorAV();
};

#endif /* ADMINISTRADOR_VISTAADMIN_VISTASTOCKPORAV_H_ */
