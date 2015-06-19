#ifndef SERVER_BASEDEDATOS_H_
#define SERVER_BASEDEDATOS_H_

#include <iostream>
#include <fstream>
#include "tinyxml.h"
//#include "opencv.hpp"
#include <cv.h>
#include <highgui.h>
#include <stdio.h>
#include "common_Producto.h"
#include "common_AreaDeVision.h"
#include "common_Stock.h"
#include "common_Imagen.h"
#include "common_Mutex.h"

#define kTagXMLProducto "Producto"
#define kTagXMLId "id"
#define kTagXMLNombreProducto "Nombre"
#define kTagXMLDescripcionProducto "Descripcion"
#define kTagXMLStockHistoricoProducto "StockHistorico"
#define kTagXMLStockProducto "Stock"
#define kTagXMLIdIconoProducto "Icono"
#define kTagXMLIdImagenesProducto "Imagenes"
#define kTagXMLIdImagenesProducto "Imagenes"
#define kTagXMLIdImagenProducto "Imagen"
#define kTagXMLFechaStockProducto "Fecha"
#define kTagXMLCantidadStockProducto "Cantidad"
#define kTagXMLAreaDeVision "AreaDeVision"
#define kTagXMLUbicacionAreaDeVision "Ubicacion"
#define kTagXMLTipoDeCapturadorAreaDeVision "TipoDeCapturador"
#define kTagXMLProductosDetectadosAreaDeVision "ProductosDetectados"
#define kRutaPorDefectoProductos "productos.xml"
#define kRutaPorDefectoAreasDeVision "areasdevision.xml"
#define kRutaPorDefectoImagenes "./imagenes/"
#define kExtensionPorDefectoImagenes ".jpg"

using common::Producto;
using common::Stock;
using common::AreaDeVision;
using common::Imagen;
using common::Mutex;

namespace server {

class BaseDeDatos {
public:
	BaseDeDatos(std::string rutaProductos = kRutaPorDefectoProductos,std::string rutaAreasDeVision = kRutaPorDefectoAreasDeVision);
	~BaseDeDatos();
	Producto* const getProductoConId(const unsigned long int idProductoBuscado) const;
	const std::list<Producto*>* getProductos() const;
	void agregarProducto(Producto* productoAAgregar);
	void eliminarProducto(const unsigned long int idProductoBuscado);
	AreaDeVision* const getAreaDeVisionConId(const unsigned long int idAreaDeVisionBuscada) const;
	const std::list<AreaDeVision*>* getAreasDeVision() const;
	void agregarAreaDeVision(AreaDeVision* AreaDeVisionAAgregar);
	void eliminarAreaDeVision(const unsigned long int idAreaDeVisionBuscada);
	const bool existeImagenConId(const unsigned long int idImagen);
	const unsigned long int agregarImagen(const Imagen& imagenAAgregar);
	Imagen getImagenConId(const unsigned long int idImagen);
	void eliminarImagen(const unsigned long int idImagen);

private:
	std::list<Producto*>* productos;
	std::list<AreaDeVision*>* areasDeVision;
	unsigned long int proximoIdImagenes;
	Mutex mutexImagenes;
	void cargarProductos(std::string rutaProductos = kRutaPorDefectoProductos);
	void guardarProductos(std::string rutaProductos = kRutaPorDefectoProductos)const;
	Producto* hidratarProductoDinamico(TiXmlElement* nodoProducto)const;
	TiXmlElement* persistirProductoDinamico(Producto* productoAPersistir)const;
	void cargarAreasDeVision(std::string rutaAreasDeVision = kRutaPorDefectoAreasDeVision);
	void guardarAreasDeVision(std::string rutaAreasDeVision= kRutaPorDefectoAreasDeVision)const;
	AreaDeVision* hidratarAreaDeVisionDinamica(TiXmlElement* nodoAreaDeVision)const;
	TiXmlElement* persistirAreaDeVisionDinamica(AreaDeVision* AreaDeVisionAPersistir)const;
	void contarProximoIdImagenes(Producto* const productoConImagenes);
};

} /* namespace server */

#endif /* SERVER_BASEDEDATOS_H_ */
