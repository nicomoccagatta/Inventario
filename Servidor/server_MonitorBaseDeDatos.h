#ifndef SERVER_MONITORBASEDEDATOS_H_
#define SERVER_MONITORBASEDEDATOS_H_

#include <string>
#include <list>
#include <ctime>
#include "common_Producto.h"
#include "common_AreaDeVision.h"
#include "common_Stock.h"
#include "common_Imagen.h"
#include "common_Mutex.h"
#include "common_Protocolo.h"
#include "server_BaseDeDatos.h"

using common::Imagen;
using common::Mutex;

namespace server {

class MonitorBaseDeDatos {
public:
	MonitorBaseDeDatos(BaseDeDatos& baseDeDatosAMonitorear);
	virtual ~MonitorBaseDeDatos();
	const std::string obtenerListadoProductos();
	const std::string obtenerListadoAreasDeVision();
	const std::string obtenerDetalleProducto(const unsigned long int idProducto);
	const bool existeAreaDeVision(const unsigned long int idAreaDeVision);
	const unsigned long int altaAreaDeVision(const std::string ubicacionAreaDeVision ,const std::string tipoDeCapturadorAreaDeVision);
	void modificarAreaDeVision(const unsigned long int idAreaDeVision,const std::string ubicacionAreaDeVision ,const std::string tipoDeCapturadorAreaDeVision);
	void bajaAreaDeVision(const unsigned long int idAreaDeVision);
	void actualizarDeteccionAreaDeVision(const unsigned long int idAreaDeVision, const Imagen& imagenCapturada,const std::string& fechaDeCaptura,const std::string& tipoDeDeteccion);
	const bool existeProducto(const unsigned long int idProducto);
	const unsigned long int altaProducto(const std::string nombreProducto,const std::string descripcionProducto,const unsigned long int idIcono);
	void modificarProducto(const unsigned long int idProducto,const std::string nombreProducto,const std::string descripcionProducto,const unsigned long int idIcono,std::list<unsigned long int>& idImagenes);
	void bajaProducto(const unsigned long int idProducto);
	const bool existeImagen(const unsigned long int idImagen);
	const unsigned long int altaImagen(const Imagen& imagenAAgregar);
	const Imagen obtenerImagen(const unsigned long int idImagen);
	const std::string obtenerStockGeneralProductos();
	const std::string obtenerStockAreaDeVision(const unsigned long int idAreaDeVision);
	const std::string obtenerStockHistoricoProducto(const unsigned long int idProducto);


private:
	BaseDeDatos& datos;
	Mutex mutexAreasDeVision;
	Mutex mutexProductos;
	Mutex mutexImagenes;
	void validarProductosDetectados(AreaDeVision* const areaDeVisionAValidar);
	void actualizarImagenesProducto(Producto* const productoAModificar, std::list<unsigned long int> nuevaListaDeIdsImagenes);
};

} /* namespace server */

#endif /* SERVER_MONITORBASEDEDATOS_H_ */
