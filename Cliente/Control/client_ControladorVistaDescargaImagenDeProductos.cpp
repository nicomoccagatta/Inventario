/*
 * client_ControladorVistaDescargaImagenDeProductos.cpp
 *
 *  Created on: Jun 17, 2015
 *      Author: ale
 */

#include <sstream>
#include <fstream>

#include "client_ControladorVistaDescargaImagenDeProductos.h"
#include "../Vista/client_VistaDescargaImagenDeProductos2.h"

void ControladorVistaDescargaImagenDeProductos::on_producto_seleccionado(
		Producto* prod, Gtk::ScrolledWindow* imagenes_container){
	vista->update_lista_imagenes(prod->getIdsImagenes(), imagenes_container);
}

void ControladorVistaDescargaImagenDeProductos::on_button_descargar(
		std::string rutaOrigen, std::string rutaDestino){
	std::cerr << "Copiando de " << rutaOrigen << " a " << rutaDestino << "\n";

	std::stringstream iss(rutaOrigen);
	std::string item;
	std::string extencion;

	std::getline(iss, item, '.');
	std::getline(iss, extencion, '.');

	std::cerr << "La extencion es: " << extencion;

	rutaDestino+="."+extencion;

	this->copiarArchivo(rutaOrigen, rutaDestino);
}


void ControladorVistaDescargaImagenDeProductos::copiarArchivo(
		std::string& rutaOrigen, std::string& rutaDestino){

	std::ifstream  source(rutaOrigen.c_str(), std::ios::binary);
	std::ofstream  dest(rutaDestino.c_str(),   std::ios::binary);

	dest << source.rdbuf();

	source.close();
	dest.close();

}
