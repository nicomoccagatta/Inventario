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
  m_quitButton(0)
{
	//this->modelo = modelo;

	//CONECTAR BOTONES CON SUS FUNCIONES CONTROLADORAS
	//Get the Glade-instantiated Button, and connect a signal handler:
	m_refGlade->get_widget("quit_button", m_quitButton);

	if(m_quitButton)
		m_quitButton->signal_clicked().connect( sigc::mem_fun(*this, &VistaEnviar::on_button_quit) );
}

VistaEnviar::~VistaEnviar() {
	// TODO Auto-generated destructor stub
}

void VistaEnviar::on_button_quit()
{
  hide(); //hide() will cause main::run() to end.
}
