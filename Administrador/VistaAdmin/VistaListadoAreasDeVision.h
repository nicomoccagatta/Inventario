/*
 * VistaListadoAreasDeVision.h
 *
 *  Created on: 17/6/2015
 *      Author: nicomoccagatta
 */

#ifndef ADMINISTRADOR_VISTAADMIN_VISTALISTADOAREASDEVISION_H_
#define ADMINISTRADOR_VISTAADMIN_VISTALISTADOAREASDEVISION_H_

#include <gtkmm-2.4/gtkmm.h>
#include "ModeloAdmin/admin_ModeloObservable.h"
#include "ListaAV.h"
#include "ListaProductos.h"
#include <list>
#include "common_AreaDeVision.h"

class VistaListadoAreasDeVision : public Observer {
	Modelo_Observable *modelo;
	Gtk::Viewport *panelDinam;
	void update_lista_av();
	bool on_imagen_button_press(GdkEventButton*);
	void on_av_seleccionado();
	void on_button_editar();
	void on_button_eliminar();
public:
	VistaListadoAreasDeVision();
	void update();
	void run(Gtk::Viewport *panelDinamico,Modelo_Observable *modelo);
	virtual ~VistaListadoAreasDeVision();
protected:
	Glib::RefPtr<Gtk::ListStore> m_refProductosListStore;
	Gtk::TreeView m_ProductosTreeView;

	Glib::RefPtr<Gtk::ListStore> m_refAVListStore;
	Gtk::TreeView m_AVTreeView;
	Glib::RefPtr<Gtk::TreeSelection> refTreeSelection;

	Gtk::VBox verticalBox;
	Gtk::HBox hBoxListados;
	ListaAV m_AVList;
	ListaProductos m_ProductosList;
	Gtk::VButtonBox m_ButtonBox;
	Gtk::Button m_EditarButton;
	Gtk::Button m_EliminarButton;
};

#endif /* ADMINISTRADOR_VISTAADMIN_VISTALISTADOAREASDEVISION_H_ */
