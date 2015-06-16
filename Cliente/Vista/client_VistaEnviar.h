/*
 * VistaEnviar.h
 *
 *  Created on: Jun 11, 2015
 *      Author: ale
 */

#ifndef CLIENTE_VISTA_CLIENT_VISTAENVIAR_H_
#define CLIENTE_VISTA_CLIENT_VISTAENVIAR_H_

//#include <gtkmm-3.0/gtkmm.h>
#include <gtkmm-2.4/gtkmm.h>
#include <glibmm-2.4/glibmm.h>
#include <iostream>

#include "../Control/client_ControladorVistaEnviar.h"
#include "../Modelo/client_ModeloObservable.h"
#include "client_AreasDeVisionComboBoxModel.h"

class VistaEnviar : public Gtk::Dialog{

	ModeloObservable* modelo;
	ControladorVistaEnviar* controlador;

public:
	VistaEnviar(BaseObjectType* cobject,
			const Glib::RefPtr<Gtk::Builder>& refGlade);
			//,ModeloObservable* modelo);//,ControladorVistaEnviar* ctrol);
	virtual ~VistaEnviar();

	void asignarModelo(ModeloObservable* modelo);
	void asignarControlador(ControladorVistaEnviar* controlador);

protected:
	//signal handlers:
	void on_button_quit();
	void on_button_ENVIAR();
	void on_button_VistaPrevia();
	void on_file_set();

	Glib::RefPtr<Gtk::Builder> m_refGlade;
	Gtk::Button* m_quitButton;
	Gtk::Button* m_ENVIARButton;
	Gtk::Button* m_vistaPrevia;
	Gtk::FileChooserButton* m_fileChooser;
	Gtk::Calendar* m_calendar;
	Gtk::Entry* m_entryHora;
	Gtk::Entry* m_entryMinutos;
	Gtk::Entry* m_entrySegundos;
	Gtk::RadioButton* m_templateMatching;
	Gtk::RadioButton* m_featureMatching;
	Gtk::ComboBox* m_AreasDeVision;
	AreasDeVisionComboBoxModel columnas;
	Glib::RefPtr<Gtk::ListStore> modeloComboBox;

private:
	void update();
	void agregarAreasAlCombo();

};

#endif /* CLIENTE_VISTA_CLIENT_VISTAENVIAR_H_ */
