/*
 * client_VistaPrincipal.cpp
 *
 *  Created on: Jun 20, 2015
 *      Author: ale
 */

#include "client_VistaPrincipal.h"

VistaPrincipal::VistaPrincipal(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade)
: Gtk::Window(cobject),
  m_refGlade(refGlade){

	std::cerr << "CREANDO VISTA PRINCIPAL\n";
	m_refGlade->get_widget_derived("viewportEnviar", vistaEnviarPtr);
	m_refGlade->get_widget_derived("viewportDescargar", vistaDescargar);
	m_refGlade->get_widget_derived("viewportCrearVideo", vistaCrearVideo);

	this->signal_delete_event().connect(sigc::mem_fun(*this, &VistaPrincipal::on_exit_clicked) );
}

VistaPrincipal::~VistaPrincipal() {
	std::cerr << "DESTRUYENDO VISTA PRINCIPAL\n";
	if(vistaEnviarPtr)
		delete vistaEnviarPtr;
	if(vistaDescargar)
		delete vistaDescargar;
	if(vistaCrearVideo)
		delete vistaCrearVideo;
	std::cerr << "SE TERMINO DE DESTRUIR\n";
}

void VistaPrincipal::setModelo(ModeloObservable* modelo){
	vistaEnviarPtr->asignarModelo(modelo);
	modelo->suscribe(vistaEnviarPtr);
	vistaDescargar->asignarModelo(modelo);
	modelo->suscribe(vistaDescargar);

}

bool VistaPrincipal::on_exit_clicked(GdkEventAny* event){
	Gtk::Main::quit();
	return true;
}
