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
	m_refGlade->get_widget_derived("viewportEnviar", vistaEnviarPtr);//panelDinamicoEnviar);
	m_refGlade->get_widget_derived("viewportDescargar", vistaDescargar);
	m_refGlade->get_widget("viewportCrearVideo", panelDinamicoCrearVideo);

	this->signal_delete_event().connect(sigc::mem_fun(*this, &VistaPrincipal::on_exit_clicked) );
}

VistaPrincipal::~VistaPrincipal() {
	std::cerr << "DESTRUYENDO VISTA PRINCIPAL\n";
	if(vistaEnviarPtr)
		delete vistaEnviarPtr;
	if(vistaDescargar)
		delete vistaDescargar;
	std::cerr << "SE TERMINO DE DESTRUIR\n";
}

void VistaPrincipal::setModelo(ModeloObservable* modelo){
	vistaEnviarPtr->asignarModelo(modelo);
	vistaDescargar->asignarModelo(modelo);

}

bool VistaPrincipal::on_exit_clicked(GdkEventAny* event){
	Gtk::Main::quit();
	return true;
}

bool VistaPrincipal::crearVistaEnviarAPartirDeGlade(){

	Glib::RefPtr<Gtk::Builder> refBuilder = Gtk::Builder::create();

	try
	{
		refBuilder->add_from_file("Enviar_Imagen_2.4.glade");
		refBuilder->get_widget_derived("DialogoEnviar", vistaEnviarPtr);
		if(vistaEnviarPtr){
			std::cerr << "TODO BIEN CON LA VISTA ENVIAR\n";
			//vistaEnviarPtr->show();
			return true;
		}else{
			return false;
		}
	}
	catch(const Glib::FileError& ex)
	{
		std::cerr << "FileError: " << ex.what() << std::endl;
		return false;
	}
	catch(const Glib::MarkupError& ex)
	{
		std::cerr << "MarkupError: " << ex.what() << std::endl;
		return false;
	}
	catch(const Gtk::BuilderError& ex)
	{
		std::cerr << "BuilderError: " << ex.what() << std::endl;
		return false;
	}
}
