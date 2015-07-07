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
#include "Vista/client_VistaPrincipal.h"

#include "common_Video.h"
#include "Vista/client_VistaDescargaImagenDeProductos.h"

#define VISTA_ENVIAR "Enviar_Imagen_2.4.glade"
#define VISTA_PPAL "Principal.glade"
#define MSJ_USAGE " ip puerto"

int crearAPartirDeGlade(Glib::RefPtr<Gtk::Builder>* refBuilder,
		const char* gladeFile);

int main(int argc, char* argv[]) {
	if (argc != 3){
		std::cout << "Uso: "<<argv[0]<< MSJ_USAGE << std::endl;
		return 1;
	}

	ModeloObservable modelo(argv[1],argv[2]);

	modelo.actualizarProductos();
	modelo.actualizarAreasDeVision();

	Gtk::Main kit(argc, argv);

	Glib::RefPtr<Gtk::Builder> refBuilder2 = Gtk::Builder::create();

	if (crearAPartirDeGlade(&refBuilder2, VISTA_PPAL)==1)
		return 1;

	VistaPrincipal* pPrincipal = 0;
	refBuilder2->get_widget_derived("VentanaPrincipal",pPrincipal);
	if( pPrincipal){
		//Start:
		pPrincipal->setModelo(&modelo);
		pPrincipal->show();
		Gtk::Main::run();
	}
	delete pPrincipal;
	return 0;
}


int crearAPartirDeGlade(Glib::RefPtr<Gtk::Builder>* refBuilder1,
		const char* gladeFile){

	try
	{
		(*refBuilder1)->add_from_file(gladeFile);
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

