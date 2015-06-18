/*
 * client_main.cpp
 *
 *  Created on: Jun 11, 2015
 *      Author: ale
 */
#include <string>
#include <iostream>

#include "Control/client_ControladorVistaEnviar.h"
#include "Control/client_ControladorVistaDescargaImagenDeProductos.h"
#include "Modelo/client_ModeloObservable.h"
#include "Vista/client_VistaEnviar.h"
#include "Vista/client_VistaDescargaImagenDeProductos2.h"

#define VISTA_ENVIAR "Enviar_Imagen_2.4.glade"

int crearAPartirDeGlade(Glib::RefPtr<Gtk::Builder>* refBuilder);

int main(int argc, char* argv[]) {
  ModeloObservable modelo;

  modelo.actualizarProductos();
  modelo.actualizarAreasDeVision();

  Gtk::Main kit(argc, argv);

  VistaDescargaImagenDeProductos2 vista(&modelo);

  vista.show();

  //Load the Glade file and instiate its widgets:
  Glib::RefPtr<Gtk::Builder> refBuilder = Gtk::Builder::create();

  if (crearAPartirDeGlade(&refBuilder)==1)
	  return 1;

  //Get the GtkBuilder-instantiated dialog::
  VistaEnviar* pDialogoEnviar = 0;
  refBuilder->get_widget_derived("DialogoEnviar", pDialogoEnviar);
  if(pDialogoEnviar){
	  //Asignar Modelo y Controlador
	  ControladorVistaEnviar controlador(&modelo);
	  pDialogoEnviar->asignarControlador(&controlador);
	  pDialogoEnviar->asignarModelo(&modelo);

	  //Start:
	  pDialogoEnviar->show();
	  //pDialogoEnviar->run();
	  Gtk::Main::run();
  }

  delete pDialogoEnviar;
  return 0;
}


int crearAPartirDeGlade(Glib::RefPtr<Gtk::Builder>* refBuilder){

	try
	{
		(*refBuilder)->add_from_file(VISTA_ENVIAR);
		return 0;
	}
	catch(const Glib::FileError& ex)
	{
		std::cerr << "FileError: " << ex.what() << std::endl;
		return 1;
	}
	catch(const Glib::MarkupError& ex)
	{
		std::cerr << "MarkupError: " << ex.what() << std::endl;
		return 1;
	}
	catch(const Gtk::BuilderError& ex)
	{
		std::cerr << "BuilderError: " << ex.what() << std::endl;
		return 1;
	}

}

