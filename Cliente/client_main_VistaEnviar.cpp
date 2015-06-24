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
#include "Vista/client_VistaPrincipal.h"

#include "common_Video.h"

#define VISTA_ENVIAR "Enviar_Imagen_2.4.glade"
#define VISTA_PPAL "Principal.glade"

int crearAPartirDeGlade(Glib::RefPtr<Gtk::Builder>* refBuilder,
		const char* gladeFile);

int main(int argc, char* argv[]) {

	common::Video vid("/home/ale/git/Inventario/Imagenes/Areas/Farmacia/farmacia_%02d.jpg");
	//common::Video vid("/home/ale/git/Inventario/Imagenes/20150623_144843.mp4");
	vid.mostrarVideo();

	std::list<Imagen> frames;
	std::list<std::string> fechas;

	vid.capturasPeriodicasVideo(frames,fechas,"Sun Jun 14 01:02:03 2015",1);

	std::list<Imagen>::iterator itIm;
	std::list<std::string>::iterator itStr;

	for (itIm=frames.begin(), itStr=fechas.begin();
			itIm != frames.end(); ++itIm, ++itStr){
		(*itIm).mostrarImagen();
		cv::waitKey(1000);
		std::cerr << "Fecha: " << (*itStr) << "\n";
	}
	return 0;
	ModeloObservable modelo;

	modelo.actualizarProductos();
	modelo.actualizarAreasDeVision();

	Gtk::Main kit(argc, argv);

	VistaDescargaImagenDeProductos2 vista(&modelo);

	vista.show();

	//Load the Glade file and instiate its widgets:
	Glib::RefPtr<Gtk::Builder> refBuilder1 = Gtk::Builder::create();
	Glib::RefPtr<Gtk::Builder> refBuilder2 = Gtk::Builder::create();

	if (crearAPartirDeGlade(&refBuilder1, VISTA_ENVIAR)==1)
		return 1;

	if (crearAPartirDeGlade(&refBuilder2, VISTA_PPAL)==1)
		return 1;

	//Get the GtkBuilder-instantiated dialog::
	VistaEnviar* pDialogoEnviar = 0;
	VistaPrincipal* pPrincipal = 0;
	refBuilder1->get_widget_derived("DialogoEnviar", pDialogoEnviar);
	refBuilder2->get_widget_derived("VentanaPrincipal",pPrincipal);
	if(pDialogoEnviar && pPrincipal){
		//Asignar Modelo y Controlador
		ControladorVistaEnviar controlador(&modelo);
		pDialogoEnviar->asignarControlador(&controlador);
		pDialogoEnviar->asignarModelo(&modelo);

		//Start:
		pPrincipal->show();
		pDialogoEnviar->show();
		//pDialogoEnviar->run();
		Gtk::Main::run();
	}

	delete pDialogoEnviar;
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

