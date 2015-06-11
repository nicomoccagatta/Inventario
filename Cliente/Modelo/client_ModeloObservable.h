/*
 * client_ModeloObservable.h
 *
 *  Created on: Jun 10, 2015
 *      Author: ale
 */

#ifndef CLIENTE_MODELO_CLIENT_MODELOOBSERVABLE_H_
#define CLIENTE_MODELO_CLIENT_MODELOOBSERVABLE_H_

#include "client_ClienteDemo.h"

class ModeloObservable {

	ClienteDemo cliente;

public:
	ModeloObservable();
	virtual ~ModeloObservable();


	bool actualizarProductos();
	bool actualizarAreasDeVision();
};

#endif /* CLIENTE_MODELO_CLIENT_MODELOOBSERVABLE_H_ */
