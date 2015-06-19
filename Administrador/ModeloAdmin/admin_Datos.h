/*
 * admin_Datos.h
 *
 *  Created on: 16/6/2015
 *      Author: nicomoccagatta
 */

#ifndef ADMINISTRADOR_MODELOADMIN_ADMIN_DATOS_H_
#define ADMINISTRADOR_MODELOADMIN_ADMIN_DATOS_H_

#include <list>

#include "common_Producto.h"
#include "common_AreaDeVision.h"

using common::Producto;
using common::AreaDeVision;

class Datos {

	std::list<Producto*> productos;

	std::list<AreaDeVision*> areasDeVision;

public:
	Datos();
	virtual ~Datos();
	const std::list<AreaDeVision*>* getAreasDeVision() const {
		return &areasDeVision;
	}
	const std::list<Producto*>* getProductos() const {
		return &productos;
	}
	/*PRODUCTO*/
	void agregarProducto(std::string nombre, std::string descripcion,unsigned long int id, unsigned long int idIcono);
	void eliminarProductos();

	/*AREA DE VISION*/
	void agregarAreaDeVision(std::string ubicacion, std::string tipoDeCapturador,unsigned long int id,std::list<Producto*>* listaProductos);
	void eliminarAreasDeVision();
};
#endif /* ADMINISTRADOR_MODELOADMIN_ADMIN_DATOS_H_ */
