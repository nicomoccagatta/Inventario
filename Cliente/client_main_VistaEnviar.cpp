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

	//common::Video vid("/home/ale/git/Inventario/Imagenes/Areas/Farmacia/farmacia_%02d.jpg", 50);
	//vid.mostrarVideo();
	//return 0;
	/*common::Video vid("test.mp4");

	cv::VideoCapture capturasVideo;

	if (!capturasVideo.open("testLeo.mp4"))
		std:: cout << "FAAAAAALSE\n";

	if (!capturasVideo.isOpened()){
		std::cerr << "EL OPENCV ES UNA MIERDA!\n";
		//return 0;
	}

	if (!vid.esValido()){
		std::cerr << "EL VIDEO NO ES VALIDO\n";
		return 0;
	}

	//vid.mostrarVideo();

	std::list<Imagen> frames;
	std::list<std::string> fechas;

	vid.capturasPeriodicasVideo(frames,fechas,"Sun Jun 14 01:02:39 2015",4);

	std::list<Imagen>::iterator itIm;
	std::list<std::string>::iterator itStr;

	std::cout << "Cantidad de frames extraidos: " << frames.size() << "\n";

	for (itIm=frames.begin(), itStr=fechas.begin();
			itIm != frames.end(); ++itIm, ++itStr){
		(*itIm).mostrarImagen();
		cv::waitKey(1000);
		std::cerr << "Fecha: " << (*itStr) << "\n";
	}
	return 0;
*/
	ModeloObservable modelo;

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

