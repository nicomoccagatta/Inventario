/*
 * client_Data.h
 *
 *  Created on: Jun 10, 2015
 *      Author: ale
 */

#ifndef CLIENTE_MODELO_CLIENT_DATA_H_
#define CLIENTE_MODELO_CLIENT_DATA_H_

#include <list>

#include "common_Producto.h"
#include "common_AreaDeVision.h"

using common::Producto;
using common::AreaDeVision;

/*
 * La clase Data almacena una lista de Productos y Areas de Vision y los metodos
 * necesarios que se necesitan para que la interfaz grafica muestre sus atributos.
 */
class Data {

	std::list<Producto*> productos;

	std::list<AreaDeVision*> areasDeVision;

public:
	Data();
	virtual ~Data();

	const std::list<AreaDeVision*>* getAreasDeVision() const {
		return &areasDeVision;
	}

	const std::list<Producto*>* getProductos() const {
		return &productos;
	}

	/*PRODUCTO*/
	Producto* agregarProducto(std::string nombre, std::string descripcion,unsigned long int id, unsigned long int idIcono);

	/*
	 * Libera y elimina todos los productos de la lista.
	 */
	void eliminarProductos();

	/*AREA DE VISION*/
	void agregarAreaDeVision(std::string ubicacion, std::string tipoDeCapturador,unsigned long int id);
	/*
	 * Libera y elimina todas las Areas de Vision de la lista.
	 */
	void eliminarAreasDeVision();
};

#endif /* CLIENTE_MODELO_CLIENT_DATA_H_ */
