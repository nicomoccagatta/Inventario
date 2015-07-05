#ifndef ADMINISTRADOR_MODELOADMIN_ADMINISTRADOR_H_
#define ADMINISTRADOR_MODELOADMIN_ADMINISTRADOR_H_

#include "common_SocketCliente.h"
#include "common_Protocolo.h"
#include <gtkmm-2.4/gtkmm.h>
#include "admin_Datos.h"
#include "common_Stock.h"
#include <map>

#define RUTA_CARPETA_TEMP "temp_admin/"
#define IMAGEN_DEFAULT "temp_admin/imagen_vacia.png"

using client::SocketCliente;
using common::Protocolo;
using common::AreaDeVision;

class Administrador {
	SocketCliente admin;
	Protocolo protocolo;
	Datos data;
	long unsigned int altaImagen(std::string &rutaImagen);
	std::list<unsigned long int> idsDescargados;
	std::map<unsigned long int,unsigned long int> stockGeneral;
public:
	Administrador();
	virtual ~Administrador();

	bool actualizarProductos();
	void altaProducto(std::string &nombre,std::string &descripcion,std::string &rutaImagenPPAL,std::list<std::string*> &rutaImagenes);
	void eliminarProducto(unsigned long int id);
	void modificarProducto(unsigned long int id,std::string &nombre,std::string &descripcion,std::string &rutaImagenPPAL,
												std::list<unsigned long int> idsAnteriores,std::list<std::string*> &rutaImagenesAgregar);
	bool actualizarAreasDeVision();
	void altaAreaVision(const std::string &ubicacion,const std::string &capturador);
	void eliminarAreaVision(unsigned long int idAV);
	void modificarAreaVision(unsigned long int idAV,std::string& ubicacion,std::string& capturador);
	std::list<unsigned long int> getIdsImagenes(unsigned long int idProducto);
	std::string getImagenConID(unsigned long int id);
	void actualizarStockGeneral();
	unsigned long int consultarStock(unsigned long int idProd);
	std::list<common::Stock> getStockHisto(unsigned long int idProducto);

	const std::list<AreaDeVision*>* getAreasDeVision() const;
	const std::list<Producto*>* getProductos() const;

	void cerrarConeccion();
};

#endif /* ADMINISTRADOR_MODELOADMIN_ADMINISTRADOR_H_ */
