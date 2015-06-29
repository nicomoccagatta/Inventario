/*
 * admin_ModeloObservable.h
 *
 *  Created on: 16/6/2015
 *      Author: nicomoccagatta
 */

#ifndef ADMINISTRADOR_MODELOADMIN_ADMIN_MODELOOBSERVABLE_H_
#define ADMINISTRADOR_MODELOADMIN_ADMIN_MODELOOBSERVABLE_H_

#include <list>
#include <gtkmm-2.4/gtkmm.h>
#include "common_AreaDeVision.h"
#include "Administrador.h"
#include "admin_Subject.h"

#define RUTA_CARPETA_TEMP "temp_admin/"

using common::AreaDeVision;

class Modelo_Observable: public Subject {
	Administrador admin;
public:
	Modelo_Observable();

	bool actualizarProductos();
	void eliminarProducto(unsigned long int id);
	bool actualizarAreasDeVision();
	void eliminarAreaVision(unsigned long int idAV);
	void altaProducto(std::string &nombre,std::string &descripcion,
			std::string &rutaImagenPPAL,std::list<std::string*> &rutaImagenes);
	void modificarProducto(unsigned long int id,std::string &nombre,std::string &descripcion,std::string &rutaImagenPPAL,
												std::list<unsigned long int> idsAnteriores,std::list<std::string*> &rutaImagenesAgregar);
	std::list<unsigned long int> getIdsImagenes(unsigned long int idProducto);
	std::string getImagenConID(unsigned long int id);
	void altaAreaVision(const std::string &ubicacion,const std::string &capturador);
	void modificarAreaVision(unsigned long int idAV,std::string& ubicacion,std::string& capturador);
	void actualizarStockGeneral();
	unsigned long int consultarStock(unsigned long int idProducto);

	const std::list<AreaDeVision*>* getAreasDeVision() const;
	const std::list<Producto*>* getProductos() const;

	virtual ~Modelo_Observable();
};

#endif /* ADMINISTRADOR_MODELOADMIN_ADMIN_MODELOOBSERVABLE_H_ */
