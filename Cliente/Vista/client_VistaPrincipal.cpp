/*
 * client_VistaPrincipal.cpp
 *
 *  Created on: Jun 20, 2015
 *      Author: ale
 */

#include "client_VistaPrincipal.h"

VistaPrincipal::VistaPrincipal(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade)
: Gtk::Window(cobject),
  m_refGlade(refGlade),
  m_EnviarButton(0), m_DescargarButton(0), m_CrearVideoButton(0),
  m_bottonesBox(0){

	//CONECTAR BOTONES CON SUS FUNCIONES CONTROLADORAS
	//BOTON SALIR:
	m_refGlade->get_widget("quit_button", m_EnviarButton);
	if(m_EnviarButton)
		m_EnviarButton->signal_clicked().connect( sigc::mem_fun(*this, &VistaPrincipal::on_button_Enviar) );

	//BOTON ENVIAR
	m_refGlade->get_widget("buttonEnviar", m_DescargarButton);
	if(m_DescargarButton)
		m_DescargarButton->signal_clicked().connect( sigc::mem_fun(*this, &VistaPrincipal::on_button_Descargar) );

	//BOTON VISTA PREVIA
	m_refGlade->get_widget("buttonVistaPrevia", m_CrearVideoButton);
	if(m_CrearVideoButton)
		m_CrearVideoButton->signal_clicked().connect( sigc::mem_fun(*this, &VistaPrincipal::on_button_CrearVideo) );


	this->signal_delete_event().connect(sigc::mem_fun(*this, &VistaPrincipal::on_exit_clicked) );
}

VistaPrincipal::~VistaPrincipal() {
	// TODO Auto-generated destructor stub
}

void VistaPrincipal::on_button_Enviar(){

}
void VistaPrincipal::on_button_Descargar(){

}
void VistaPrincipal::on_button_CrearVideo(){
	Gtk::Main::quit();
}

bool VistaPrincipal::on_exit_clicked(GdkEventAny* event){
	Gtk::Main::quit();
	return true;
}




