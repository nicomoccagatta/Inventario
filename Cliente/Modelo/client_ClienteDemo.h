/*
 * client_ClienteDemo.h
 *
 *  Created on: Jun 10, 2015
 *      Author: ale
 */

#ifndef CLIENTE_MODELO_CLIENT_CLIENTEDEMO_H_
#define CLIENTE_MODELO_CLIENT_CLIENTEDEMO_H_

#include "common_SocketCliente.h"
#include "common_Protocolo.h"
#include "client_Data.h"

using client::SocketCliente;
using common::Protocolo;

class ClienteDemo {

	SocketCliente client;
	Protocolo protocolo;
	Data data;

public:
	ClienteDemo();
	virtual ~ClienteDemo();

	bool actualizarProductos();
	bool actualizarAreasDeVision();

	void cerrarConeccion();
};

#endif /* CLIENTE_MODELO_CLIENT_CLIENTEDEMO_H_ */
