/*
 * VistaAgregarProducto.h
 *
 *  Created on: 21/6/2015
 *      Author: nicomoccagatta
 */

#ifndef ADMINISTRADOR_VISTAADMIN_VISTAAGREGARPRODUCTO_H_
#define ADMINISTRADOR_VISTAADMIN_VISTAAGREGARPRODUCTO_H_

#include <gtkmm-2.4/gtkmm.h>
#include "ModeloAdmin/admin_ModeloObservable.h"

class VistaAgregarProducto : public Observer{
	void on_button_editar();
	void on_button_eliminar();
public:
	VistaAgregarProducto();
	void update();
	void run(Gtk::Viewport *panelDinamico,Modelo_Observable *modelo);
	virtual ~VistaAgregarProducto();
protected:
	Glib::RefPtr<Gtk::ListStore> m_refProductosListStore; //The Tree Model.
	Gtk::TreeView m_ProductosTreeView; //The Tree View.
	Glib::RefPtr<Gtk::TreeSelection> refTreeSelection; //The selected

	Glib::RefPtr<Gtk::ListStore> m_refAVListStore;
	Gtk::TreeView m_AVTreeView;
	Glib::RefPtr<Gtk::TreeSelection> refTreeSelection;

	//Esto es lo miooo
	Gtk::VBox vBoxPrincipal;

	Gtk::HBox hBoxNombre;
	Gtk::HBox hBoxDescripcion;
	Gtk::HBox hBoxStock;
	Gtk::HBox hBoxAreaVision;
	Gtk::HBox hBoxIconos;

	Gtk::VBox vBoxCantidad;

	ListaAV m_AVList;
	Gtk::Label m_labelNombre;
	Gtk::Entry m_ingresarNombre;
	Gtk::Label m_labelDescripcion;
	Gtk::Entry m_ingresarDescripcion;
	Gtk::Calendar m_calendario;
	Gtk::Label m_labelCantidad;
	Gtk::Entry m_ingresarCantidad;
	Gtk::Label m_labelAreaVision;
	Gtk::ComboBox m_ComboAreaVision;
	Gtk::Button m_ImagenIconoPPAL;
	std::list<Gtk::Button*> m_ImagenIconosSecundarios;

	Gtk::Button m_AgregarIconosSecundarios;
	Gtk::Button m_AgregarProducto;
};

#endif /* ADMINISTRADOR_VISTAADMIN_VISTAAGREGARPRODUCTO_H_ */
