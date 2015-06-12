/*
 * VistaEnviar.cpp
 *
 *  Created on: Jun 11, 2015
 *      Author: ale
 */

#include "client_VistaEnviar.h"

VistaEnviar::VistaEnviar(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade)
						//,ModeloObservable* modelo)
: Gtk::Dialog(cobject),
  m_refGlade(refGlade),
  m_quitButton(0), m_ENVIARButton(0), m_vistaPrevia(0), m_fileChooser(0), m_calendar(0),
  m_entryHora(0), m_entryMinutos(0), m_entrySegundos(0), m_templateMatching(0),
  m_featureMatching(0), m_AreasDeVision(0)

{
	//this->modelo = modelo;

	//CONECTAR BOTONES CON SUS FUNCIONES CONTROLADORAS
	//BOTON SALIR:
	m_refGlade->get_widget("quit_button", m_quitButton);
	if(m_quitButton)
		m_quitButton->signal_clicked().connect( sigc::mem_fun(*this, &VistaEnviar::on_button_quit) );

	//BOTON ENVIAR
	m_refGlade->get_widget("buttonEnviar", m_ENVIARButton);
	if(m_ENVIARButton)
		m_ENVIARButton->signal_clicked().connect( sigc::mem_fun(*this, &VistaEnviar::on_button_ENVIAR) );

	//BOTON VISTA PREVIA
	m_refGlade->get_widget("buttonVistaPrevia", m_vistaPrevia);
	if(m_vistaPrevia)
		m_vistaPrevia->signal_clicked().connect( sigc::mem_fun(*this, &VistaEnviar::on_button_VistaPrevia) );

	//FILE CHOOSER
	/*m_refGlade->get_widget("fileChooserAEnviar", m_fileChooser);
	if(m_fileChooser)
		m_fileChooser->signal_file_set().connect( sigc::mem_fun(*this, &VistaEnviar::on_file_set) );
	*/

}

VistaEnviar::~VistaEnviar() {
	// TODO Auto-generated destructor stub
}

void VistaEnviar::on_button_quit(){
	hide(); //hide() will cause main::run() to end.
}

void VistaEnviar::on_file_set(){

}

void VistaEnviar::on_button_ENVIAR(){
	//controlador->buttonENVIARClicked(...);
	m_refGlade->get_widget("entryHora", m_entryHora);
	m_refGlade->get_widget("entryMinutos", m_entryMinutos);
	m_refGlade->get_widget("entrySegundos", m_entrySegundos);
	m_refGlade->get_widget("fileChooserAEnviar", m_fileChooser);
	m_refGlade->get_widget("radiobuttonTemplateMatching", m_templateMatching);
	m_refGlade->get_widget("radiobuttonFeatureMatching", m_featureMatching);
	m_refGlade->get_widget("comboboxAreasDeVision", m_AreasDeVision);


	Glib::ustring horas = m_entryHora->get_text();
	Glib::ustring minutos = m_entryMinutos->get_text();
	Glib::ustring segundos = m_entrySegundos->get_text();

	std::cerr << "Horas: " << horas << " ";
	std::cerr << "Minutos: " << minutos << " ";
	std::cerr << "Segundos: " << segundos << "\n";

	Glib::ustring rutaArchivo = m_fileChooser->get_filename();

	std::cerr << "Ruta archivo: " << rutaArchivo << "\n";


}

void VistaEnviar::on_button_VistaPrevia(){
	//controlador->buttonVistaPreviaClicked(...);

}
