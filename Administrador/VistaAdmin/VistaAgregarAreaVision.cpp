/*
 * VistaAgregarAreaVision.cpp
 *
 *  Created on: 23/6/2015
 *      Author: nicomoccagatta
 */

#include "VistaAgregarAreaVision.h"

VistaAgregarAreaVision::VistaAgregarAreaVision():modelo(0),panelDinam(0) {
	m_labelUbicacion.set_text("Ubicacion:");
	m_hBoxUbicacion.pack_start(m_labelUbicacion);
	m_hBoxUbicacion.pack_end(m_obtenerUbicacion);

	m_VBoxOpciones.pack_start(m_hBoxUbicacion);

	m_labelCapturador.set_text("Tipo de Capturador:");
	m_hBoxCapturador.pack_start(m_labelCapturador);

	modeloComboBox = Gtk::ListStore::create(columnas);
	m_TiposCapturador.set_model(modeloComboBox);
	Gtk::TreeModel::Row fila = *modeloComboBox->append();
	fila[columnas.getColumnaCapturador()] = "Foto";
	fila = *(modeloComboBox->append());
	fila[columnas.getColumnaCapturador()] = "Video";
	m_TiposCapturador.pack_start(columnas.getColumnaCapturador());
	m_hBoxCapturador.pack_end(m_TiposCapturador);

	m_VBoxOpciones.pack_end(m_hBoxCapturador);
	m_VBoxOpciones.set_layout(Gtk::BUTTONBOX_SPREAD);

	m_HBoxPrincipal.pack_start(m_VBoxOpciones);

	m_ButtonCrearAV.set_label("OK");
	m_ButtonCrearAV.signal_clicked().connect( sigc::mem_fun(*this, &VistaAgregarAreaVision::on_button_OK));
	m_HBoxPrincipal.pack_end(m_ButtonCrearAV);
	m_HBoxPrincipal.set_layout(Gtk::BUTTONBOX_SPREAD);

}

VistaAgregarAreaVision::~VistaAgregarAreaVision() {
}

void VistaAgregarAreaVision::on_button_OK(){
	if( m_obtenerUbicacion.get_text() == "" ){
			Gtk::Window *ventanitaError = new Gtk::Window;
			Gtk::MessageDialog dialog(*ventanitaError,"Ingrese Ubicacion",false, Gtk::MESSAGE_ERROR);
			dialog.set_title("Error Ubicacion");
			dialog.set_size_request(350,100);
			dialog.run();
			return;
	}
	if( m_TiposCapturador.get_active_row_number() == (-1) ){
			Gtk::Window *ventanitaError = new Gtk::Window;
			Gtk::MessageDialog dialog(*ventanitaError,"Seleccione Tipo de Capturador",false, Gtk::MESSAGE_ERROR);
			dialog.set_title("Error Tipo Capturador");
			dialog.set_size_request(350,100);
			dialog.run();
			return;
	}
	Gtk::TreeModel::Row fila = *m_TiposCapturador.get_active();
	Glib::ustring tCapturador = fila[columnas.getColumnaCapturador()];
	std::string capturador = tCapturador;
	std::string ubicacion = m_obtenerUbicacion.get_text();
	this->modelo->altaAreaVision(ubicacion,capturador);

	Gtk::Window *ventanitaOK = new Gtk::Window;
	Gtk::MessageDialog dialog(*ventanitaOK,"Area de Vision agregada correctamente!",false, Gtk::MESSAGE_INFO);
	dialog.set_title("Operacion Exitosa");
	dialog.set_size_request(350,100);
	dialog.run();

	panelDinam->remove();
	this->run(panelDinam,modelo);
}

void VistaAgregarAreaVision::update(){

}

void VistaAgregarAreaVision::run(Gtk::Viewport *panelDinamico,Modelo_Observable *modelo){
	this->modelo = modelo;
	this->panelDinam = panelDinamico;

	m_obtenerUbicacion.set_text("");
	panelDinam->add(m_HBoxPrincipal);
}
