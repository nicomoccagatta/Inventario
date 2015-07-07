/*
 * CotroladorVistaEnviar.h
 *
 *  Created on: Jun 14, 2015
 *      Author: ale
 */

#ifndef CLIENTE_CONTROL_CLIENT_CONTROLADORVISTAENVIAR_H_
#define CLIENTE_CONTROL_CLIENT_CONTROLADORVISTAENVIAR_H_

#include <glibmm-2.4/glibmm.h>
#include <gtkmm-2.4/gtkmm/liststore.h>

#include "../Modelo/client_ModeloObservable.h"
#include "../Vista/client_ModelComboBoxAreasDeVision.h"
#include "common_AreaDeVision.h"

class VistaEnviar;

class ControladorVistaEnviar {

	ModeloObservable* modelo;
	VistaEnviar* vista;

public:
	ControladorVistaEnviar(ModeloObservable* modelo,VistaEnviar* vista) {
		this->modelo = modelo;
		this->vista = vista;
	}
	virtual ~ControladorVistaEnviar(){}

	void buttonVistaPreviaClicked(Glib::ustring rutaArchivo);

	/*
	 * Si se trata de una imagen, llama a enviarFoto al modelo segun el matching
	 * que corresponda.
	 * Si se trata de un video primero pregunta cada cuantos segundos sacar
	 * los frames y manda.
	 */
	void buttonENVIARClicked(Glib::ustring rutaArchivo,Glib::Date* fecha,
			Glib::ustring horas,Glib::ustring minutos, Glib::ustring segundos,
			int matching,int  idArea);

	void agregarAreasAlCombo(Glib::RefPtr<Gtk::ListStore> modeloComboBox,
			AreasDeVisionComboBoxModel* columnas);

private:
	/*
	 * Llena la estructura tm @arg time con los datos proporcionados.
	 */
	void aStructTime(Glib::Date* fecha,
		Glib::ustring horas,Glib::ustring minutos,Glib::ustring segundos,
		struct tm& time);
};

#endif /* CLIENTE_CONTROL_CLIENT_CONTROLADORVISTAENVIAR_H_ */
