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
using common::AreaDeVision;

class ClienteDemo {

	SocketCliente client;
	Protocolo protocolo;
	Data data;

public:
	ClienteDemo();
	virtual ~ClienteDemo();

	bool actualizarProductos();
	bool actualizarAreasDeVision();

	const std::list<AreaDeVision*>* getAreasDeVision() const;
	const std::list<Producto*>* getProductos() const;

	std::string getImagenConId(unsigned long int id);

	void enviarFotoTemplateMatching(unsigned long int idArea, std::string& fecha,std::string& rutaDeImagen);
	void enviarFotoFeatureMatching(unsigned long int idArea, std::string& fecha,std::string& rutaDeImagen);

	bool identificarse();
	void cerrarConeccion();

private:
	void actualizarIdImagenesDeProducto(Producto* prod);
	void agregarImagenACocaLata(std::string ruta);
};

#endif /* CLIENTE_MODELO_CLIENT_CLIENTEDEMO_H_ */
