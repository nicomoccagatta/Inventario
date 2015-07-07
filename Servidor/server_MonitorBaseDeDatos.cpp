/*
 * server_MonitorBaseDeDatos.cpp
 *
 *  Created on: Jun 24, 2015
 *      Author: leandro
 */

#include "server_MonitorBaseDeDatos.h"

namespace server {

MonitorBaseDeDatos::MonitorBaseDeDatos(BaseDeDatos& baseDeDatosAMonitorear):datos(baseDeDatosAMonitorear) {}

MonitorBaseDeDatos::~MonitorBaseDeDatos() {}

//Retorna un listado de los productos por su id, nombre, descripcion e id de icono.
const std::string MonitorBaseDeDatos::obtenerListadoProductos(){
	mutexProductos.bloquear();
	const std::list<Producto*>* listaProductos = datos.getProductos();
	if (listaProductos->size()>0){
		std::stringstream acumulador;
		for(std::list<Producto*>::const_iterator it=listaProductos->begin(); it!=listaProductos->end();++it)
			acumulador<< (*it)->getId() << kMensajeDelimitadorCampos <<(*it)->getNombre() << kMensajeDelimitadorCampos <<(*it)->getDescripcion() << kMensajeDelimitadorCampos<< (*it)->getIdIcono() << kMensajeDelimitadorCampos;
		mutexProductos.desbloquear();
		return acumulador.str();
	}
	mutexProductos.desbloquear();
	return kMensajeError;
}

//Retorna un listado de las areas de vision por su id, ubicacion y tipo de capturador.
const std::string MonitorBaseDeDatos::obtenerListadoAreasDeVision(){
	mutexAreasDeVision.bloquear();
	const std::list<AreaDeVision*>* listaAreasDeVision = datos.getAreasDeVision();
	if (listaAreasDeVision->size()>0){
		std::stringstream acumulador;
		for(std::list<AreaDeVision*>::const_iterator it=listaAreasDeVision->begin(); it!=listaAreasDeVision->end();++it)
			acumulador<< (*it)->getId() << kMensajeDelimitadorCampos <<(*it)->getUbicacion() << kMensajeDelimitadorCampos <<(*it)->getTipoDeCapturador() << kMensajeDelimitadorCampos;
		mutexAreasDeVision.desbloquear();
		return acumulador.str();
	}
	mutexAreasDeVision.desbloquear();
	return kMensajeError;
}

const std::string MonitorBaseDeDatos::obtenerDetalleProducto(const unsigned long int idProducto){
	mutexProductos.bloquear();
	Producto* productoADetallar = datos.getProductoConId(idProducto);
	if (productoADetallar!=NULL){
		std::stringstream acumulador;
		acumulador << productoADetallar->getNombre() << kMensajeDelimitadorCampos << productoADetallar->getDescripcion() << kMensajeDelimitadorCampos<< productoADetallar->getIdIcono() << kMensajeDelimitadorCampos;//faltan imagenes
		for (std::list<unsigned long int>::const_iterator idImagen = productoADetallar->getIdsImagenes()->begin(); idImagen!= productoADetallar->getIdsImagenes()->end(); ++idImagen)
				acumulador << (*idImagen)<<kMensajeDelimitadorCampos;
		mutexProductos.desbloquear();
		return acumulador.str();
	}
	mutexProductos.desbloquear();
	return kMensajeError;
}


const bool MonitorBaseDeDatos::existeAreaDeVision(const unsigned long int idAreaDeVision){
	mutexAreasDeVision.bloquear();
	const bool respuestaARetornar=(datos.getAreaDeVisionConId(idAreaDeVision)!=NULL);
	mutexAreasDeVision.desbloquear();
	return respuestaARetornar;
}
//Realiza el alta de una area de vision retornando el id con el que se registro la misma.
const unsigned long int MonitorBaseDeDatos::altaAreaDeVision(const std::string ubicacionAreaDeVision ,const std::string tipoDeCapturadorAreaDeVision){
	AreaDeVision* areaDeVisionAAgregar = new AreaDeVision(ubicacionAreaDeVision,tipoDeCapturadorAreaDeVision);
	mutexAreasDeVision.bloquear();
	datos.agregarAreaDeVision(areaDeVisionAAgregar);
	mutexAreasDeVision.desbloquear();
	return areaDeVisionAAgregar->getId();
}

void MonitorBaseDeDatos::modificarAreaDeVision(const unsigned long int idAreaDeVision,const std::string ubicacionAreaDeVision ,const std::string tipoDeCapturadorAreaDeVision){
	mutexAreasDeVision.bloquear();
	AreaDeVision* areaDeVisionAModificar = datos.getAreaDeVisionConId(idAreaDeVision);
	if(areaDeVisionAModificar!=NULL){
		areaDeVisionAModificar->setUbicacion(ubicacionAreaDeVision);
		areaDeVisionAModificar->setTipoDeCapturador(tipoDeCapturadorAreaDeVision);
	}
	mutexAreasDeVision.desbloquear();
}

//Da de baja ela rea de vision y reduce el stock de todos los productos que el area de vision que corresponda con el id ubiese detectado.
void MonitorBaseDeDatos::bajaAreaDeVision(const unsigned long int idAreaDeVision){
	//Obtengo la fecha y hora actual para indicar las mismas en la reduccion de stock de los productos que ubiera detectado el area de vision a eliminar.
	time_t hora;
	time (&hora);
	std::string fecha(asctime(localtime(&hora)));
	fecha.erase (std::remove(fecha.begin(), fecha.end(), '\n'), fecha.end());
	mutexAreasDeVision.bloquear();
	AreaDeVision* areaDeVisionAEliminar=datos.getAreaDeVisionConId(idAreaDeVision);
	if(areaDeVisionAEliminar!=NULL){
		const std::list<Producto*>* listaProductosDetectados=areaDeVisionAEliminar->getProductosDetectados();
		mutexProductos.bloquear();
		for(std::list<Producto*>::const_iterator it=listaProductosDetectados->begin();it != listaProductosDetectados->end();++it){
			Producto* productoAActualizar=datos.getProductoConId((*it)->getId());
			productoAActualizar->actualizarStock(-productoAActualizar->getStock(),fecha);
		}
		mutexProductos.desbloquear();
		datos.eliminarAreaDeVision(idAreaDeVision);
	}
	mutexAreasDeVision.desbloquear();
}

const bool MonitorBaseDeDatos::existeProducto(const unsigned long int idProducto){
	mutexProductos.bloquear();
	const bool respuestaARetornar=(datos.getProductoConId(idProducto)!=NULL);
	mutexProductos.desbloquear();
	return respuestaARetornar;
}

//Realiza el alta de un producto retornando el id con el que se registro el mismo.
const unsigned long int MonitorBaseDeDatos::altaProducto(const std::string nombreProducto,const std::string descripcionProducto,const unsigned long int idIcono){
	Producto* productoAAgregar = new Producto(nombreProducto,descripcionProducto,idIcono);
	mutexProductos.bloquear();
	datos.agregarProducto(productoAAgregar);
	mutexProductos.desbloquear();
	return productoAAgregar->getId();
}

//Modifica los atributos de un producto, si las nuevas iamgenes ya no forman parte del producto final son eliminadas.
void MonitorBaseDeDatos::modificarProducto(const unsigned long int idProducto,const std::string nombreProducto,const std::string descripcionProducto,const unsigned long int idIcono,std::list<unsigned long int>& idImagenes){
	mutexProductos.bloquear();
	Producto* productoAModificar = datos.getProductoConId(idProducto);
	if (productoAModificar!=NULL){
		productoAModificar->setNombre(nombreProducto);
		productoAModificar->setDescripcion(descripcionProducto);
		productoAModificar->setIdIcono(idIcono);
		actualizarImagenesProducto(productoAModificar,idImagenes);
	}
	mutexProductos.desbloquear();
}

void MonitorBaseDeDatos::bajaProducto(const unsigned long int idProducto){
	mutexProductos.bloquear();
	Producto* productoAModificar = datos.getProductoConId(idProducto);
	if (productoAModificar!=NULL)
		datos.eliminarProducto(idProducto);
	mutexProductos.desbloquear();
}

//Retorna un listado de todos los productos con su id nombre y cantidad.
const std::string MonitorBaseDeDatos::obtenerStockGeneralProductos(){
	mutexProductos.bloquear();
	const std::list<Producto*>* listaProductos = datos.getProductos();
	if (listaProductos->size()>0){
		std::stringstream acumulador;
		for(std::list<Producto*>::const_iterator it=listaProductos->begin(); it!=listaProductos->end();++it)
			acumulador<< (*it)->getId() << kMensajeDelimitadorCampos <<(*it)->getStock()<< kMensajeDelimitadorCampos;
		mutexProductos.desbloquear();
		return acumulador.str();
	}
	mutexProductos.desbloquear();
	return kMensajeError;
}

//Retorna un listado de los productos, su nombre y su cantidad para el area de vision indicada por id.
const std::string MonitorBaseDeDatos::obtenerStockAreaDeVision(const unsigned long int idAreaDeVision){
	mutexAreasDeVision.bloquear();
	AreaDeVision* areaDeVisionAInventariar = datos.getAreaDeVisionConId(idAreaDeVision);
	if (areaDeVisionAInventariar!=NULL){
		//valido que los productos anteriormente detectado en el area de vision existan realmente y no allan sido eliminados en el periodo entre actualizaciones
		validarProductosDetectados(areaDeVisionAInventariar);
		const std::list<Producto*>* productosDetectados= areaDeVisionAInventariar->getProductosDetectados();
		if (productosDetectados->size()>0){
			std::stringstream acumulador;
			mutexProductos.bloquear();
			for(std::list<Producto*>::const_iterator it=productosDetectados->begin(); it!=productosDetectados->end();++it)
				acumulador<< (*it)->getId() << kMensajeDelimitadorCampos<< datos.getProductoConId((*it)->getId())->getNombre() << kMensajeDelimitadorCampos << datos.getProductoConId((*it)->getId())->getIdIcono() << kMensajeDelimitadorCampos <<(*it)->getStock()<< kMensajeDelimitadorCampos;
			mutexProductos.desbloquear();
			mutexAreasDeVision.desbloquear();
			return acumulador.str();
		}
	}
	mutexAreasDeVision.desbloquear();
	return kMensajeError;
}

//Retorna un listado de todas las fechas en als que el stock del producto cambio y su stock apra esa fecha.
const std::string MonitorBaseDeDatos::obtenerStockHistoricoProducto(const unsigned long int idProducto){
	mutexProductos.bloquear();
	Producto* productoAInventariar = datos.getProductoConId(idProducto);
	if (productoAInventariar!=NULL){
		const std::list<Stock*>* stockHistoricos = productoAInventariar->getStockHistorico();
		std::stringstream acumulador;
		for(std::list<Stock*>::const_iterator it=stockHistoricos->begin(); it!=stockHistoricos->end();++it)
			acumulador<< (*it)->getFecha() << kMensajeDelimitadorCampos <<(*it)->getCantidad()<< kMensajeDelimitadorCampos;
		mutexProductos.desbloquear();
		return acumulador.str();
	}
	mutexProductos.desbloquear();
	return kMensajeError;
}

const bool MonitorBaseDeDatos::existeImagen(const unsigned long int idImagen){
	mutexImagenes.bloquear();
	const bool respuestaARetornar=datos.existeImagenConId(idImagen);
	mutexImagenes.desbloquear();
	return respuestaARetornar;
}
//Realiza el alta de una imagen retornando el id con el que se registro la misma.
const unsigned long int MonitorBaseDeDatos::altaImagen(const Imagen& imagenAAgregar){
	mutexImagenes.bloquear();
	const unsigned long int idImagen = datos.agregarImagen(imagenAAgregar);
	mutexImagenes.desbloquear();
	return idImagen;
}

const Imagen MonitorBaseDeDatos::obtenerImagen(const unsigned long int idImagen){
	mutexImagenes.bloquear();
	const Imagen imagenARetornar = datos.getImagenConId(idImagen);
	mutexImagenes.desbloquear();
	return imagenARetornar;
}

//Realiza el reconocimiento de objetos comparando una por una contra todas al imagenes template de todos los productos, actualiza la deteccion del area de vision y actualiza el stock de los productos cuyo stock halla variado.
void MonitorBaseDeDatos::actualizarDeteccionAreaDeVision(const unsigned long int idAreaDeVision, const Imagen& imagenCapturada,const std::string& fechaDeCaptura,const std::string& tipoDeDeteccion){
	mutexAreasDeVision.bloquear();
	AreaDeVision* areaDeVisionAActualizar=datos.getAreaDeVisionConId(idAreaDeVision);
	//valido que los productos anteriormente detectado en el area de vision existan realmente y no allan sido eliminados en el periodo entre actualizaciones
	mutexProductos.bloquear();
	validarProductosDetectados(areaDeVisionAActualizar);
	std::list<Producto*>* productosDetectados= new std::list<Producto*>();
	//obtengo todos los producto e itero sobre las iamgenes de cada uno reconociendo la totalidad de sus apariciones.
	const std::list<Producto*>* catalogoProductos = datos.getProductos();
	for(std::list<Producto*>::const_iterator it=catalogoProductos->begin(); it!=catalogoProductos->end();++it){
		unsigned long int aparicionesDelProducto=0;
		for (std::list<unsigned long int>::const_iterator id=(*it)->getIdsImagenes()->begin(); id!=(*it)->getIdsImagenes()->end();++id){
			if (datos.existeImagenConId(*id))
				aparicionesDelProducto+=imagenCapturada.contarApariciones(datos.getImagenConId(*id),tipoDeDeteccion);
		}
		std::cerr << "Se encontraron " << aparicionesDelProducto << " " << (*it)->getNombre() << std::endl;
		if (aparicionesDelProducto>0){
			std::list<Stock*>* stockProductoDetectado = new std::list<Stock*>();
			stockProductoDetectado->push_back(new Stock(aparicionesDelProducto,fechaDeCaptura));
			productosDetectados->push_back(new Producto((*it)->getId(),(*it)->getNombre(),(*it)->getDescripcion(),stockProductoDetectado,0,new std::list<unsigned long int>()));
		}
		long int variacionDeStock=aparicionesDelProducto;//si el producto no habia sido antes detectado entonces la cantidad de apariciones es cuanto aumento su stock.
		for (std::list<Producto*>::const_iterator producto=areaDeVisionAActualizar->getProductosDetectados()->begin(); producto!=areaDeVisionAActualizar->getProductosDetectados()->end();++producto){
			//el producto ya habia sido detectado.
			if ((*producto)->getId()==(*it)->getId())
				variacionDeStock = aparicionesDelProducto-(*producto)->getStock();
		}
		if (variacionDeStock!=0){
			(*it)->actualizarStock(variacionDeStock,fechaDeCaptura);
		}
	}
	areaDeVisionAActualizar->actualizarDeteccion(productosDetectados);
	mutexProductos.desbloquear();
	mutexAreasDeVision.desbloquear();
}

//Recorre la lista de productos en un area de vision y si encuentra un producto que fue dado de baja, lo elimina.
void MonitorBaseDeDatos::validarProductosDetectados(AreaDeVision* const areaDeVisionAValidar){
	for (std::list<Producto*>::const_iterator producto=areaDeVisionAValidar->getProductosDetectados()->begin(); producto!=areaDeVisionAValidar->getProductosDetectados()->end();++producto)
		if (datos.getProductoConId((*producto)->getId())==NULL)
			producto = areaDeVisionAValidar->eliminarProductoDetectado((*producto)->getId());
}

//Recorre la lista de ids de imagenes de un producto y compara contra una nueva lista de ids de imagen, si la nueva lista no contiene los ids de imagen de la lista vieja, entonces esas imagenes seran eliminadas. Los ids de imagen del producto son actulizados para que coincidan con la nueva lista.
void MonitorBaseDeDatos::actualizarImagenesProducto(Producto* const productoAModificar, std::list<unsigned long int> nuevaListaDeIdsImagenes){
	std::list<unsigned long int>*const listaDeIdsDeImagenesActualDelProducto=productoAModificar->getIdsImagenes();
	for(std::list<unsigned long int>::const_iterator id = nuevaListaDeIdsImagenes.begin();id!=nuevaListaDeIdsImagenes.end();++id)
		//si el nuevo id no se encuentra en la lista de ids actual, lo agrego.
		if (std::find(listaDeIdsDeImagenesActualDelProducto->begin(),listaDeIdsDeImagenesActualDelProducto->end(),(*id)) == listaDeIdsDeImagenesActualDelProducto->end())
			listaDeIdsDeImagenesActualDelProducto->push_back(*id);
		//Por cada uno de los ids que quedaron, si no estaban en la lista de nuevos ids, es porque esas imagens fueron dadas de baja, deben eliminarse.
		for(std::list<unsigned long int>::iterator id = listaDeIdsDeImagenesActualDelProducto->begin();id!=listaDeIdsDeImagenesActualDelProducto->end();++id){
		if (std::find(nuevaListaDeIdsImagenes.begin(),nuevaListaDeIdsImagenes.end(),(*id)) == nuevaListaDeIdsImagenes.end()){
			datos.eliminarImagen((*id));//comentar esta linea si se desea admitir que muchos productos tengan la misma imagen.
			id = listaDeIdsDeImagenesActualDelProducto->erase(id);
		}
	}
}

} /* namespace server */
