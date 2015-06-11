/*
 * client_main.cpp
 *
 *  Created on: Jun 11, 2015
 *      Author: ale
 */
#include <string>
#include <iostream>

#include "Modelo/client_ModeloObservable.h"
#include "Vista/client_VistaEnviar.h"

#define VISTA_ENVIAR "Enviar_Imagen.glade"

int main(int argc, char* argv[]) {
  ModeloObservable modelo;

  modelo.actualizarProductos();
  modelo.actualizarAreasDeVision();

  Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "org.gtkmm.example");

  //Load the Glade file and instiate its widgets:
  Glib::RefPtr<Gtk::Builder> refBuilder = Gtk::Builder::create();
  try
  {
	  refBuilder->add_from_file(VISTA_ENVIAR);
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

  //Get the GtkBuilder-instantiated dialog::
  VistaEnviar* pDialog = 0;
  refBuilder->get_widget_derived("DialogoEnviar", pDialog);
  if(pDialog){
	  //Start:
	  app->run(*pDialog);
  }

  delete pDialog;
  return 0;
}



