/*
 * Administrador.cpp
 *
 *  Created on: 11/6/2015
 *      Author: nicomoccagatta
 */

#include <gtkmm-3.0/gtkmm.h>
#include <glibmm-2.4/glibmm.h>
#include <iostream>

#define VISTAPPAL "Administrador.glade"

typedef struct
{
	Gtk::Window       *ventanaPPAL = NULL;
	GtkWidget       *grillaPPAL;
	GtkWidget       *barraMENU;
	GtkWidget       *grillaSECUNDARIA;
	GtkWidget       *panelIzquierdo; //Muchas cosas
	GtkWidget       *panelCambiante;
	GtkWidget       *barraESTADO;
} Administrador;
Administrador aplicacion;

static void on_button_clicked()
{
  if(aplicacion.ventanaPPAL)
	  aplicacion.ventanaPPAL->hide(); //hide() will cause main::run() to end.
}

int main(int argc, char *argv[]) {

	Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "Aplicacion.Administrador");

	//Load the GtkBuilder file and instantiate its widgets:
	Glib::RefPtr<Gtk::Builder> refBuilder = Gtk::Builder::create();
	try
	{
		refBuilder->add_from_file(VISTAPPAL);
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

	//Get the GtkBuilder-instantiated Dialog:
	refBuilder->get_widget("Administrador", aplicacion.ventanaPPAL);
	if(aplicacion.ventanaPPAL)
	{
		//Agarrar el panel cambiante y los botones
		//Asignarle controlador a los botones

		Gtk::Button* pButton = 0;
		refBuilder->get_widget("Agregar Producto", pButton);
		if(pButton)
		{
			pButton->signal_clicked().connect( sigc::ptr_fun(on_button_clicked) );
		}

		app->run(*aplicacion.ventanaPPAL);
	}

	delete aplicacion.ventanaPPAL;

	return 0;
}
