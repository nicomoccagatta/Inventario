/*
 * VistaEnviar.h
 *
 *  Created on: Jun 11, 2015
 *      Author: ale
 */

#ifndef CLIENTE_VISTA_CLIENT_VISTAENVIAR_H_
#define CLIENTE_VISTA_CLIENT_VISTAENVIAR_H_

#include <gtkmm-2.4/gtkmm.h>
#include <glibmm-2.4/glibmm.h>
#include <iostream>

#include "../Control/client_ControladorVistaEnviar.h"
#include "../Modelo/client_ModeloObservable.h"
#include "client_ModelComboBoxAreasDeVision.h"

class ControladorVistaEnviar;

/*
 * Es la vista que permite seleccionar los datos necesarios para enviar una
 * foto o video al servidor para realizar una demonstracion de un
 * control de inventario.
 */
class VistaEnviar : public Gtk::Viewport{

	ModeloObservable* modelo;
	ControladorVistaEnviar* controlador;

public:
	VistaEnviar(BaseObjectType* cobject,
			const Glib::RefPtr<Gtk::Builder>& refGlade);

	virtual ~VistaEnviar();

	void asignarModelo(ModeloObservable* modelo);
	void ventanaError(const char* mensaje, const char* titulo);

protected:
	//signal handlers:
	void on_button_quit();
	void on_button_ENVIAR();
	void on_button_VistaPrevia();
	void on_button_AutocompletarHoy();
	void on_button_AutocompletarFechaUltimaModif();

	Glib::RefPtr<Gtk::Builder> m_refGlade;
	Gtk::Button* m_ENVIARButton;
	Gtk::Button* m_vistaPrevia;
	Gtk::Button* m_fechaHoy;
	Gtk::Button* m_fechaUltimaMod;
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
	void setearFechaYHora(std::tm* timer);

};

#endif /* CLIENTE_VISTA_CLIENT_VISTAENVIAR_H_ */
