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
#include "common_Imagen.h"
#include "common_Video.h"
#include "client_Data.h"

using client::SocketCliente;
using common::Protocolo;
using common::AreaDeVision;
using common::Imagen;
using common::Video;

/*
 * Clase que representa a un cliente para el servidor de Control de Inventario.
 * Utiliza un SocketCliente y un Protocolo para comunicarse y una instancia de
 * Data para almacenar los Productos y Areas De Vision que le pide al server.
 */
class ClienteDemo {

	SocketCliente client;
	Protocolo protocolo;
	Data data;

public:
	ClienteDemo();
	virtual ~ClienteDemo();

	/*
	 * Elimina los productos que tenia y pide todos los productos que tenga el
	 * Server nuevamente solo si este esta conectado.
	 */
	bool actualizarProductos();

	/*
	 * Elimina las AreasDeVision que tenia y pide todas las que tenga el
	 * Server nuevamente solo si este esta conectado.
	 */
	bool actualizarAreasDeVision();

	/*
	 * Devuelve un puntero a la lista de Areas de Vision.
	 */
	const std::list<AreaDeVision*>* getAreasDeVision() const;

	/*
	 * Devuelve un puntero a la lista de Productos.
	 */
	const std::list<Producto*>* getProductos() const;

	/*
	 * Le pide al servidor la imagen con el id @arg id y devuelve la ruta
	 * temporal en la que se almacena.
	 */
	std::string getImagenConId(unsigned long int id);

	/*
	 * Envia una foto al servidor para que realice el control de inventario
	 * mediante el metodo Template Matching.
	 * @arg fecha debe ser del formato definido en kFormatoFecha ("%a %b %d %H:%M:%S %Y")
	 */
	void enviarFotoTemplateMatching(unsigned long int idArea, std::string& fecha,std::string& rutaDeImagen);

	/*
	 * Envia una foto al servidor para que realice el control de inventario
	 * mediante el metodo Feature Matching.
	 */
	void enviarFotoFeatureMatching(unsigned long int idArea, std::string& fecha,std::string& rutaDeImagen);

	/*
	 * Envia los frames necesarios del video al servidor para que realice el control de
	 * inventario mediante el metodo Template Matching.
	 * @arg fecha debe ser del formato definido en kFormatoFecha ("%a %b %d %H:%M:%S %Y")
	 */
	void enviarVideoTemplateMatching(unsigned long int idArea, std::string& fechaInicio,std::string& rutaDeVideo);
	void enviarVideoFeatureMatching(unsigned long int idArea, std::string& fechaInicio,std::string& rutaDeVideo);


	/*
	 * Envia la lista de imagenes en @arg listaImagenes al servidor para que realice el control de
	 * inventario mediante el metodo Template Matching.
	 * @arg fecha debe ser del formato definido en kFormatoFecha ("%a %b %d %H:%M:%S %Y")
	 */
	void enviarVideoTemplateMatching(unsigned long int idArea, std::string& fechaInicio,std::list<Imagen>& listaImagenes);
	void enviarVideoFeatureMatching(unsigned long int idArea, std::string& fechaInicio,std::list<Imagen>& listaImagenes);


	/*
	 * Realiza la identificacion ante el Server.
	 * Devuelve False en caso de un fallo en la identificacion.
	 */
	bool identificarse();

	/*
	 * Cierra la coneccion del socket.
	 */
	void cerrarConeccion();

private:
	/*
	 * Actualiza los ids de las imagenes del Producto @arg prod.
	 */
	void actualizarIdImagenesDeProducto(Producto* prod);

	/*
	 * Envia la imagen @arg img al servidor con el tipo de matcheo especificado
	 * por el @arg comando.
	 */
	void enviarFoto(const char* comando, unsigned long int idArea, std::string& fecha,Imagen& img);

	/*
	 * Envia el video @arg vid al servidor con el tipo de matcheo especificado
	 * por el @arg comando.
	 */
	void enviarVideo(const char* comando, unsigned long int idArea, std::string& fechaInicio,Video& vid);
};

#endif /* CLIENTE_MODELO_CLIENT_CLIENTEDEMO_H_ */
