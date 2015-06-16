/*
 * Administrador.cpp
 *
 *  Created on: 11/6/2015
 *      Author: nicomoccagatta
 */

#include <gtkmm-2.4/gtkmm.h>
#include <glibmm-2.4/glibmm.h>
#include <iostream>
#include "ModeloAdmin/admin_ModeloObservable.h"
#include "VistaAdmin/VistaVentanaPPAL.h"

#define VISTAPPAL "/home/nicomoccagatta/git/Inventario/build/Administrador.glade"

//static void on_button_clicked()
//{
//    std::cout << "Hello World" << std::endl;
//}

int crearAPartirDeGlade(Glib::RefPtr<Gtk::Builder>* refBuilder);

int main(int argc, char *argv[]) {

	Modelo_Observable modelo;
	modelo.actualizarProductos();
	modelo.actualizarAreasDeVision();

	Gtk::Main kit(argc, argv);
	Glib::RefPtr<Gtk::Builder> refBuilder = Gtk::Builder::create();
	if (crearAPartirDeGlade(&refBuilder)==1)
		  return 1;
	VistaVentanaPPAL *ventanaPPAL;
	refBuilder->get_widget("Administrador", ventanaPPAL);
	if(ventanaPPAL)
	{
		//Gtk::Button* pButton = 0;
		//refBuilder->get_widget("Agregar Producto", pButton);
		//if(pButton)
		//{
		//	pButton->signal_clicked().connect( sigc::ptr_fun(&on_button_clicked) );
		//}
		ventanaPPAL->show_all();
		Gtk::Main::run(*ventanaPPAL);
	}
	delete ventanaPPAL;
	return 0;
}

int crearAPartirDeGlade(Glib::RefPtr<Gtk::Builder>* refBuilder){

	try
	{
		(*refBuilder)->add_from_file(VISTAPPAL);
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
