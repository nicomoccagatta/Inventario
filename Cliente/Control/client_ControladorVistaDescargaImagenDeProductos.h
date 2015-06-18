/*
 * client_ControladorVistaDescargaImagenDeProductos.h
 *
 *  Created on: Jun 17, 2015
 *      Author: ale
 */

#ifndef CLIENTE_CONTROL_CLIENT_CONTROLADORVISTADESCARGAIMAGENDEPRODUCTOS_H_
#define CLIENTE_CONTROL_CLIENT_CONTROLADORVISTADESCARGAIMAGENDEPRODUCTOS_H_

#include "../Modelo/client_ModeloObservable.h"
//#include "../Vista/client_VistaDescargaImagenDeProductos2.h"
#include "common_Producto.h"

class VistaDescargaImagenDeProductos2;

class ControladorVistaDescargaImagenDeProductos {

	ModeloObservable* modelo;
	VistaDescargaImagenDeProductos2* vista;

public:
	ControladorVistaDescargaImagenDeProductos(ModeloObservable* modelo,VistaDescargaImagenDeProductos2* vista) {
		this->modelo = modelo;
		this->vista = vista;
	}
	virtual ~ControladorVistaDescargaImagenDeProductos(){}

	void on_producto_seleccionado(Producto* prod);
};

#endif /* CLIENTE_CONTROL_CLIENT_CONTROLADORVISTADESCARGAIMAGENDEPRODUCTOS_H_ */
