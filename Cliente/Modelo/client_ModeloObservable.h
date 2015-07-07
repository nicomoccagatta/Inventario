/*
 * client_ModeloObservable.h
 *
 *  Created on: Jun 10, 2015
 *      Author: ale
 */

#ifndef CLIENTE_MODELO_CLIENT_MODELOOBSERVABLE_H_
#define CLIENTE_MODELO_CLIENT_MODELOOBSERVABLE_H_

#include "client_ClienteDemo.h"
#include "ThEnviadorArchivos.h"
#include "ThActualizador.h"
#include "common_AreaDeVision.h"
#include "common_Imagen.h"
#include "common_Subject.h"

#define FEATURE_MATCHING 1
#define TEMPLATE_MATCHING 2

using common::AreaDeVision;
using common::Imagen;

/*
 * El ModeloObservable es utilizado para implementar el patron MVC y asi
 * separar la parte recoleccion de los datos que se necesitan con la
 * interfaz grafica y contiene un metodo por cada dato que la interfaz
 * pudiera llegar a necesitar.
 */
class ModeloObservable  : public Subject{

	ClienteDemo cliente;
	ThEnviadorArchivos enviador;

	//ThActualizador actualizador;
	Mutex mutexData;

public:
	ModeloObservable(const char* ip, const char* puerto);
	virtual ~ModeloObservable();

	/*
	 * Actualiza Productos y Areas de Vision
	 */
	bool actualizarDatos();

	/*
	 *Actualiza los Productos :)
	 */
	bool actualizarProductos();

	/*
	 *Actualiza las Areas de vision :)
	 */
	bool actualizarAreasDeVision();

	const std::list<AreaDeVision*>* getAreasDeVision();
	const std::list<Producto*>* getProductos();

	std::string getImagenConId(unsigned long int id);

	/*
	 * Envia la imagen mediante el ClienteDemo.
	 */
	void enviarFotoTemplateMatching(unsigned long int idArea, std::string& fecha,std::string& rutaDeImagen);
	void enviarFotoFeatureMatching(unsigned long int idArea, std::string& fecha, std::string& rutaDeImagen);

	void enviarVideoTemplateMatching(unsigned long int idArea, std::string& fechaInicio,std::string& rutaDeVideo, int intervaloSegs);
	void enviarVideoFeatureMatching(unsigned long int idArea, std::string& fechaInicio,std::string& rutaDeVideo, int intervaloSegs);


};

#endif /* CLIENTE_MODELO_CLIENT_MODELOOBSERVABLE_H_ */
