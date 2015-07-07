#ifndef ADMINISTRADOR_MODELOADMIN_ADMIN_MODELOOBSERVABLE_H_
#define ADMINISTRADOR_MODELOADMIN_ADMIN_MODELOOBSERVABLE_H_

#include <list>
#include <gtkmm-2.4/gtkmm.h>
#include "common_AreaDeVision.h"
#include "common_Stock.h"
#include "Administrador.h"
#include "common_Subject.h"

#define RUTA_CARPETA_TEMP "temp_admin/"

using common::AreaDeVision;

class Modelo_Observable: public Subject {
	Administrador admin;
public:
	Modelo_Observable(const char* ip, const char* puerto);
	virtual ~Modelo_Observable();

	/*
	 * ABM de productos
	 */
	bool actualizarProductos();
	void altaProducto(std::string &nombre,std::string &descripcion,
			std::string &rutaImagenPPAL,std::list<std::string*> &rutaImagenes);
	void eliminarProducto(unsigned long int id);
	void modificarProducto(unsigned long int id,std::string &nombre,std::string &descripcion,std::string &rutaImagenPPAL,
											std::list<unsigned long int> idsAnteriores,std::list<std::string*> &rutaImagenesAgregar);

	/*
	 * ABM de areas de vision
	 */
	bool actualizarAreasDeVision();
	void altaAreaVision(const std::string &ubicacion,const std::string &capturador);
	void eliminarAreaVision(unsigned long int idAV);
	void modificarAreaVision(unsigned long int idAV,std::string& ubicacion,std::string& capturador);

	/*
	 * Dado un id de producto, devuelve una lista de Ids de imagenes.
	 */
	std::list<unsigned long int> getIdsImagenes(unsigned long int idProducto);

	/*
	 * Devuelve la ruta donde esta alojada la imagen con el id ingresado.
	 * en caso de no encontrarla, la funcion devuelve "error"
	 */
	std::string getImagenConID(unsigned long int id);

	/*
	 * Se actualiza el stock general de productos.
	 */
	void actualizarStockGeneral();

	/*
	 * Se consulta el stock del id del producto ingresado por parametro.
	 * Es necesario llamar a la funcion actualizarStockGeneral previamente.
	 */
	unsigned long int consultarStock(unsigned long int idProducto);

	/*
	 * Devuelve el stock historico (cantidad-fecha) del id del producto
	 * ingresado por parametro.
	 */
	std::list<common::Stock> getStockHisto(unsigned long int idProducto);

	const std::list<AreaDeVision*>* getAreasDeVision() const;
	const std::list<Producto*>* getProductos() const;
};

#endif /* ADMINISTRADOR_MODELOADMIN_ADMIN_MODELOOBSERVABLE_H_ */
