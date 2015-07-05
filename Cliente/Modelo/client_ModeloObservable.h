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

/*
 * El ModeloObservable es utilizado para implementar el patron MVC y asi
 * separar la parte recoleccion de los datos que se necesitan con la
 * interfaz grafica y contiene un metodo por cada dato que la interfaz
 * pudiera llegar a necesitar.
 */
class ModeloObservable {

	ClienteDemo cliente;

public:
	ModeloObservable();
	virtual ~ModeloObservable();

	/*
	 *Actualiza los Productos :)
	 */
	bool actualizarProductos();

	/*
	 *Actualiza las Areas de vision :)
	 */
	bool actualizarAreasDeVision();

	const std::list<AreaDeVision*>* getAreasDeVision() const;
	const std::list<Producto*>* getProductos() const;

	std::string getImagenConId(unsigned long int id);

	/*
	 * Envia la imagen mediante el ClienteDemo.
	 */
	void enviarFotoTemplateMatching(unsigned long int idArea, std::string& fecha,std::string& rutaDeImagen);
	void enviarFotoFeatureMatching(unsigned long int idArea, std::string& fecha, std::string& rutaDeImagen);

	void enviarVideoTemplateMatching(unsigned long int idArea, std::string& fechaInicio,std::string& rutaDeVideo);
	void enviarVideoFeatureMatching(unsigned long int idArea, std::string& fechaInicio,std::string& rutaDeVideo);


};

#endif /* CLIENTE_MODELO_CLIENT_MODELOOBSERVABLE_H_ */
