/*
 * Administrador.h
 *
 *  Created on: 16/6/2015
 *      Author: nicomoccagatta
 */

#ifndef ADMINISTRADOR_MODELOADMIN_ADMINISTRADOR_H_
#define ADMINISTRADOR_MODELOADMIN_ADMINISTRADOR_H_

#include "common_SocketCliente.h"
#include "common_Protocolo.h"
#include "admin_Datos.h"
#include "common_Stock.h"

using client::SocketCliente;
using common::Protocolo;
using common::AreaDeVision;

class Administrador {
	SocketCliente admin;
	Protocolo protocolo;
	Datos data;
public:
	Administrador();
	virtual ~Administrador();

	bool actualizarProductos();
	void eliminarProducto(unsigned long int id);
	bool actualizarAreasDeVision();
	void eliminarAreaVision(unsigned long int idAV);

	const std::list<AreaDeVision*>* getAreasDeVision() const;
	const std::list<Producto*>* getProductos() const;

	void cerrarConeccion();
};

#endif /* ADMINISTRADOR_MODELOADMIN_ADMINISTRADOR_H_ */
