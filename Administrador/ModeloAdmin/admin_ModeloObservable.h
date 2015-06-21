/*
 * admin_ModeloObservable.h
 *
 *  Created on: 16/6/2015
 *      Author: nicomoccagatta
 */

#ifndef ADMINISTRADOR_MODELOADMIN_ADMIN_MODELOOBSERVABLE_H_
#define ADMINISTRADOR_MODELOADMIN_ADMIN_MODELOOBSERVABLE_H_

#include <list>
#include "common_AreaDeVision.h"
#include "Administrador.h"
#include "admin_Subject.h"

using common::AreaDeVision;

class Modelo_Observable: public Subject {
	Administrador admin;
public:
	Modelo_Observable();

	bool actualizarProductos();
	void eliminarProducto(unsigned long int id);
	bool actualizarAreasDeVision();
	void eliminarAreaVision(unsigned long int idAV);

	const std::list<AreaDeVision*>* getAreasDeVision() const;
	const std::list<Producto*>* getProductos() const;

	virtual ~Modelo_Observable();
};

#endif /* ADMINISTRADOR_MODELOADMIN_ADMIN_MODELOOBSERVABLE_H_ */
