/*
 * VistaAgregarAreaVision.h
 *
 *  Created on: 23/6/2015
 *      Author: nicomoccagatta
 */

#ifndef ADMINISTRADOR_VISTAADMIN_VISTAAGREGARAREAVISION_H_
#define ADMINISTRADOR_VISTAADMIN_VISTAAGREGARAREAVISION_H_

#include <gtkmm-2.4/gtkmm.h>
#include "ModeloAdmin/admin_ModeloObservable.h"
#include "TiposCapturadorComboBoxModel.h"

class VistaAgregarAreaVision : public Observer {
	void on_button_OK();

	Modelo_Observable *modelo;
	Gtk::Viewport *panelDinam;

	Gtk::HButtonBox m_HBoxPrincipal;
	Gtk::VButtonBox m_VBoxOpciones;

	Gtk::HBox m_hBoxUbicacion;
	Gtk::Label m_labelUbicacion;
	Gtk::Entry m_obtenerUbicacion;

	Gtk::HBox m_hBoxCapturador;
	Gtk::Label m_labelCapturador;
	Gtk::ComboBox m_TiposCapturador;
	TiposCapturadorComboBoxModel columnas;
	Glib::RefPtr<Gtk::ListStore> modeloComboBox;

	Gtk::Button m_ButtonCrearAV;
public:
	VistaAgregarAreaVision();
	virtual ~VistaAgregarAreaVision();
	void update();
	void run(Gtk::Viewport *panelDinamico,Modelo_Observable *modelo);
};

#endif /* ADMINISTRADOR_VISTAADMIN_VISTAAGREGARAREAVISION_H_ */
