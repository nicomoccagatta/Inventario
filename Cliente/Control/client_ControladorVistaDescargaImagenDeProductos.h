/*
 * client_ControladorVistaDescargaImagenDeProductos.h
 *
 *  Created on: Jun 17, 2015
 *      Author: ale
 */

#ifndef CLIENTE_CONTROL_CLIENT_CONTROLADORVISTADESCARGAIMAGENDEPRODUCTOS_H_
#define CLIENTE_CONTROL_CLIENT_CONTROLADORVISTADESCARGAIMAGENDEPRODUCTOS_H_

#include <gtkmm-2.4/gtkmm/scrolledwindow.h>

#include "../Modelo/client_ModeloObservable.h"
#include "common_Producto.h"

class VistaDescargaImagenDeProductos;

/*
 * Se de manejar las acciones de la vista DescargaImagenDeProductos
 */
class ControladorVistaDescargaImagenDeProductos {

	ModeloObservable* modelo;
	VistaDescargaImagenDeProductos* vista;

public:
	ControladorVistaDescargaImagenDeProductos(ModeloObservable* modelo,VistaDescargaImagenDeProductos* vista) {
		this->modelo = modelo;
		this->vista = vista;
	}
	virtual ~ControladorVistaDescargaImagenDeProductos(){}

	/*
	 * Llama a la funcion de la vista que actualiza las imagenes de los productos.
	 */
	void on_producto_seleccionado(Producto* prod, Gtk::ScrolledWindow* imagenes_container);

	/*
	 * Copia el archivo que esta en rutaOrigen a rutaDestino.
	 */
	//no pongo referencia para que me copie de glib::ustring a std::string
	void on_button_descargar(std::string rutaOrigen, std::string rutaDestino);

private:
	void copiarArchivo(std::string& rutaOrigen, std::string& rutaDestino);
};

#endif /* CLIENTE_CONTROL_CLIENT_CONTROLADORVISTADESCARGAIMAGENDEPRODUCTOS_H_ */
