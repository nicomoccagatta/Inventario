/*
 * client_ModeloObservable.h
 *
 *  Created on: Jun 10, 2015
 *      Author: ale
 */

#ifndef CLIENTE_MODELO_CLIENT_MODELOOBSERVABLE_H_
#define CLIENTE_MODELO_CLIENT_MODELOOBSERVABLE_H_

#include "client_ClienteDemo.h"
#include "common_AreaDeVision.h"
#include "common_Imagen.h"

using common::AreaDeVision;
using common::Imagen;

class ModeloObservable {

	ClienteDemo cliente;

public:
	ModeloObservable();
	virtual ~ModeloObservable();


	bool actualizarProductos();
	bool actualizarAreasDeVision();

	const std::list<AreaDeVision*>* getAreasDeVision() const;
	const std::list<Producto*>* getProductos() const;

	std::string getImagenConId(unsigned long int id);

	void enviarFotoTemplateMatching(unsigned long int id, std::string& fecha,std::string& rutaDeImagen);
	void enviarFotoFeatureMatching(unsigned long int id, std::string& fecha, std::string& rutaDeImagen);

	void enviarVideoTemplateMatching(unsigned long int idArea, std::string& fechaInicio,std::string& rutaDeVideo);
	void enviarVideoFeatureMatching(unsigned long int idArea, std::string& fechaInicio,std::string& rutaDeVideo);


};

#endif /* CLIENTE_MODELO_CLIENT_MODELOOBSERVABLE_H_ */
