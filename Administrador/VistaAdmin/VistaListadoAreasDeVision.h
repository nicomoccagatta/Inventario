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
	void update();
	void setearAtributos(Gtk::Viewport *panelDinamico,Modelo_Observable *modelo);
	void run();
	virtual ~VistaListadoAreasDeVision();
protected:
	Glib::RefPtr<Gtk::ListStore> m_refAVListStore; //The Tree Model.
	Gtk::TreeView m_AVTreeView; //The Tree View.
	Glib::RefPtr<Gtk::TreeSelection> refTreeSelection; //The selected

	Gtk::VBox verticalBox;
	Gtk::HBox m_Botones;
	ListaAV m_AVList;
	Gtk::VButtonBox m_ButtonBox;
	Gtk::Button m_EditarButton;
	Gtk::Button m_EliminarButton;
};

#endif /* ADMINISTRADOR_VISTAADMIN_VISTALISTADOAREASDEVISION_H_ */
