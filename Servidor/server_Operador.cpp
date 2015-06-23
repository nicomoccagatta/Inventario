#include "server_Operador.h"
#include <list>
#include <string>

using server::Operador;
using common::Protocolo;
using common::Socket;

Operador::Operador(Socket& cliente, const Protocolo& protocolo, BaseDeDatos& datos)
    : cliente(cliente),
      protocolo(protocolo),
      datos(datos),
      realizarOperaciones(true),
	  identificadorUsuario(Operador::identificarUsuario(cliente,protocolo)){}

Operador::~Operador() {}


void Operador::run() { this->atenderOperaciones(); }

const common::Socket& Operador::getCliente() const { return this->cliente; }

// Escucha las consultas de entrantes por el socket, las resuelve y reenvia la
// informacion correspondiente.
void Operador::atenderOperaciones() {
  this->realizarOperaciones = true;
  while (this->cliente.estaConectado() && this->realizarOperaciones) {
    std::string mensajeRecibido = this->protocolo.recibirMensaje(this->cliente);
    if (this->cliente.estaConectado()){
    	std::string mensajeAResponder(this->realizarOperacion(mensajeRecibido));
		if (mensajeAResponder != kRespuestaNula)
				this->protocolo.enviarMensaje(this->cliente,mensajeAResponder);
    }
  }
  this->cliente.cerrarConeccion();
}


// Obliga al operador a que finalice la tarea actual.
void Operador::detenerOperaciones() {
  if (this->realizarOperaciones) {
    this->cliente.abortarConeccion();
    // espero que se terminen las operaciones
    // solo la tarea en ejecucion
    // determianra feacientemente que se
    // cerro la coneccion.
    this->realizarOperaciones = false;
  }
}

// TAREA PRINCIPAL. A partir de un comando recibido resuelve que operacion debe
// realizar, al ejecuta y retorna el resultado.
const std::string Operador::realizarOperacion(std::string& comandoDeOperacion) {
  if (comandoDeOperacion.length() > 1) {
	  switch (comandoDeOperacion[0]) {
		case kIndicadorComandoListarProductos: return listarProductos();
		case kIndicadorComandoListarAreasDeVision:return listarAreasDeVision();
		case kIndicadorComandoDetalleProducto:return detallarProducto(comandoDeOperacion);
		case kIndicadorComandoSolicitudImagen:return enviarImagen(comandoDeOperacion);
		default :return realizarOperacionEspecifica(comandoDeOperacion);
	  }
    }
  return kMensajeError;
}

const std::string Operador::realizarOperacionEspecifica(std::string& comandoDeOperacion){
	if (identificadorUsuario==(kIdentificacionAdministrador+protocolo.getFinalizadorDeMensaje()))
		switch (comandoDeOperacion[0]) {
			case kIndicadorComandoAltaProducto:return altaProducto(comandoDeOperacion);
			case kIndicadorComandoModificacionProducto:return modificacionProducto(comandoDeOperacion);
			case kIndicadorComandoBajaProducto: return bajaProducto(comandoDeOperacion);
			case kIndicadorComandoAltaAreaDeVision: return altaAreaDeVision(comandoDeOperacion);
			case kIndicadorComandoModificacionAreaDeVision:return modificacionAreaDeVision(comandoDeOperacion);
			case kIndicadorComandoBajaAreaDeVision: return bajaAreaDeVision(comandoDeOperacion);
			case kIndicadorComandoStockGeneral: return stockGeneral();
			case kIndicadorComandoStockAreaDeVision: return stockAreaDeVision(comandoDeOperacion);
			case kIndicadorComandoStockHistoricoProducto: return stockHistoricoProducto(comandoDeOperacion);
			case kIndicadorComandoAltaImagen: return altaImagen(comandoDeOperacion);
		}
	if (identificadorUsuario==(kIdentificacionCliente+protocolo.getFinalizadorDeMensaje()))
		switch (comandoDeOperacion[0]) {
			case kIndicadorComandoFotoTemplateMatching:return actualizarStockAreaDeVision(comandoDeOperacion);
			case kIndicadorComandoFotoFeatureMatching:return actualizarStockAreaDeVision(comandoDeOperacion);
		}
	return kMensajeError;
}

const std::string Operador::listarProductos()const{
	const std::list<Producto*>* listaProductos = datos.getProductos();
	if (listaProductos->size()>0){
		std::stringstream acumulador;
		for(std::list<Producto*>::const_iterator it=listaProductos->begin(); it!=listaProductos->end();++it)
			acumulador<< (*it)->getId() << kMensajeDelimitadorCampos <<(*it)->getNombre() << kMensajeDelimitadorCampos <<(*it)->getDescripcion() << kMensajeDelimitadorCampos<< (*it)->getIdIcono() << kMensajeDelimitadorCampos;
		return acumulador.str();
	} else {
		return kMensajeError;
	}
}

const std::string Operador::listarAreasDeVision()const{
	const std::list<AreaDeVision*>* listaAreasDeVision = datos.getAreasDeVision();
	if (listaAreasDeVision->size()==0){
		return kMensajeError;
	} else {
		std::stringstream acumulador;
		for(std::list<AreaDeVision*>::const_iterator it=listaAreasDeVision->begin(); it!=listaAreasDeVision->end();++it)
			acumulador<< (*it)->getId() << kMensajeDelimitadorCampos <<(*it)->getUbicacion() << kMensajeDelimitadorCampos <<(*it)->getTipoDeCapturador() << kMensajeDelimitadorCampos;
		return acumulador.str();
	}
}

const std::string Operador::detallarProducto(const std::string& comandoDeOperacion) const{
	const unsigned long int idProducto = Protocolo::extraerArgumentoNumericoDeComando(comandoDeOperacion,2);
	Producto* productoADetallar = datos.getProductoConId(idProducto);
	if (productoADetallar!=NULL){
		std::stringstream acumulador;
		acumulador << productoADetallar->getNombre() << kMensajeDelimitadorCampos << productoADetallar->getDescripcion() << kMensajeDelimitadorCampos<< productoADetallar->getIdIcono() << kMensajeDelimitadorCampos;//faltan imagenes
		for (std::list<unsigned long int>::const_iterator idImagen = productoADetallar->getIdsImagenes()->begin(); idImagen!= productoADetallar->getIdsImagenes()->end(); ++idImagen)
				acumulador << (*idImagen)<<kMensajeDelimitadorCampos;
		return acumulador.str();
	} else {
		return kMensajeError;
	}
}

const std::string Operador::enviarImagen(const std::string& comandoDeOperacion){
	const unsigned long int idImagen = Protocolo::extraerArgumentoNumericoDeComando(comandoDeOperacion,2);
	if (datos.existeImagenConId(idImagen)){
		Imagen imagenSolicitada = datos.getImagenConId(idImagen);
		protocolo.enviarImagen(cliente,imagenSolicitada);
		return kRespuestaNula;
	}
	return kMensajeError;
}

void Operador::validarProductosDetectados(AreaDeVision* const areaDeVisionAValidar){
	for (std::list<Producto*>::const_iterator producto=areaDeVisionAValidar->getProductosDetectados()->begin(); producto!=areaDeVisionAValidar->getProductosDetectados()->end();++producto)
		if (datos.getProductoConId((*producto)->getId())==NULL)
			producto = areaDeVisionAValidar->eliminarProductoDetectado((*producto)->getId());
}

const Imagen Operador::recibirImagen(const std::string& informacionDeImagen){
	const unsigned int altoImagen = Protocolo::extraerArgumentoNumericoDeComando(informacionDeImagen,2);
	const unsigned int anchoImagen = Protocolo::extraerArgumentoNumericoDeComando(informacionDeImagen,3);
	const unsigned long int tamanioImagen = Protocolo::extraerArgumentoNumericoDeComando(informacionDeImagen,4);
	protocolo.enviarMensaje(cliente, kMensajeOK);
	return protocolo.recibirImagen(cliente,altoImagen,anchoImagen,tamanioImagen);
}


const std::string Operador::altaProducto(const std::string& comandoDeOperacion){
	const std::string nombreProducto = Protocolo::extraerArgumentoDeComando(comandoDeOperacion,2);
	const std::string descripcionProducto = Protocolo::extraerArgumentoDeComando(comandoDeOperacion,3);
	const unsigned long int idIcono = Protocolo::extraerArgumentoNumericoDeComando(comandoDeOperacion,4);
	datos.agregarProducto(new Producto(nombreProducto,descripcionProducto,idIcono));
	return kMensajeOK;
}

const std::string Operador::modificacionProducto(const std::string& comandoDeOperacion){
	const unsigned long int idProducto = Protocolo::extraerArgumentoNumericoDeComando(comandoDeOperacion,2);
	Producto* productoAModificar = datos.getProductoConId(idProducto);
	if (productoAModificar!=NULL){
		const unsigned long int idIcono = Protocolo::extraerArgumentoNumericoDeComando(comandoDeOperacion,5);
		bool existenTodasLasImagenes= datos.existeImagenConId(idIcono);
		int numeroDeArgumento=6;
		std::list<unsigned long int> nuevaListaDeIdsImagenes;
		unsigned long int idImagen;
		while ((idImagen= Protocolo::extraerArgumentoNumericoDeComando(comandoDeOperacion,numeroDeArgumento))){
			if ((idImagen) && (existenTodasLasImagenes=datos.existeImagenConId(idImagen)))
				nuevaListaDeIdsImagenes.push_back(idImagen);
			++numeroDeArgumento;
		}
		if (existenTodasLasImagenes){
			const std::string nombreProducto = Protocolo::extraerArgumentoDeComando(comandoDeOperacion,3);
			const std::string descripcionProducto = Protocolo::extraerArgumentoDeComando(comandoDeOperacion,4);
			productoAModificar->setNombre(nombreProducto);
			productoAModificar->setDescripcion(descripcionProducto);
			productoAModificar->setIdIcono(idIcono);
			actualizarImagenesProducto(productoAModificar,nuevaListaDeIdsImagenes);
			return kMensajeOK;
		}
	}
	return kMensajeError;
}

const std::string Operador::bajaProducto(const std::string& comandoDeOperacion){
	const unsigned long int idProducto = Protocolo::extraerArgumentoNumericoDeComando(comandoDeOperacion,2);
		Producto* productoADetallar = datos.getProductoConId(idProducto);
		if (productoADetallar!=NULL){
			datos.eliminarProducto(idProducto);
			return kMensajeOK;
		} else {
			return kMensajeError;
		}
}

const std::string Operador::altaAreaDeVision(const std::string& comandoDeOperacion){
	const std::string ubicacionAreaDeVision = Protocolo::extraerArgumentoDeComando(comandoDeOperacion,2);
	const std::string tipoDeCapturadorAreaDeVision = Protocolo::extraerArgumentoDeComando(comandoDeOperacion,3);
	datos.agregarAreaDeVision(new AreaDeVision(ubicacionAreaDeVision,tipoDeCapturadorAreaDeVision));
	return kMensajeOK;
}

const std::string Operador::modificacionAreaDeVision(const std::string& comandoDeOperacion){
	const unsigned long int idAreaDeVision = Protocolo::extraerArgumentoNumericoDeComando(comandoDeOperacion,2);
	AreaDeVision* AreaDeVisionAModificar = datos.getAreaDeVisionConId(idAreaDeVision);
	if (AreaDeVisionAModificar!=NULL){
		const std::string ubicacionAreaDeVision = Protocolo::extraerArgumentoDeComando(comandoDeOperacion,3);
		AreaDeVisionAModificar->setUbicacion(ubicacionAreaDeVision);
		const std::string tipoDeCapturadorAreaDeVision = Protocolo::extraerArgumentoDeComando(comandoDeOperacion,4);
		AreaDeVisionAModificar->setTipoDeCapturador(tipoDeCapturadorAreaDeVision);
		return kMensajeOK;
	} else {
		return kMensajeError;
	}
}

const std::string Operador::bajaAreaDeVision(const std::string& comandoDeOperacion){
	const unsigned long int idAreaDeVision = Protocolo::extraerArgumentoNumericoDeComando(comandoDeOperacion,2);
		AreaDeVision* AreaDeVisionADetallar = datos.getAreaDeVisionConId(idAreaDeVision);
		if (AreaDeVisionADetallar!=NULL){
			datos.eliminarAreaDeVision(idAreaDeVision);
			return kMensajeOK;
		} else {
			return kMensajeError;
		}
}

const std::string Operador::stockGeneral() const{
	const std::list<Producto*>* listaProductos = datos.getProductos();
	if (listaProductos->size()>0){
		std::stringstream acumulador;
		for(std::list<Producto*>::const_iterator it=listaProductos->begin(); it!=listaProductos->end();++it)
			acumulador<< (*it)->getId() << kMensajeDelimitadorCampos <<(*it)->getStock()<< kMensajeDelimitadorCampos;
		return acumulador.str();
	} else {
		return kMensajeError;
	}
}

const std::string Operador::stockAreaDeVision(const std::string& comandoDeOperacion){
	const unsigned long int idAreaDeVision = Protocolo::extraerArgumentoNumericoDeComando(comandoDeOperacion,2);
	AreaDeVision* areaDeVisionAInventariar = datos.getAreaDeVisionConId(idAreaDeVision);
	if (areaDeVisionAInventariar!=NULL){
		//valido que los productos anteriormente detectado en el area de vision existan realmente y no allan sido eliminados en el periodo entre actualizaciones
		validarProductosDetectados(areaDeVisionAInventariar);
		const std::list<Producto*>* productosDetectados= areaDeVisionAInventariar->getProductosDetectados();
		if (productosDetectados->size()>0){
			std::stringstream acumulador;
			for(std::list<Producto*>::const_iterator it=productosDetectados->begin(); it!=productosDetectados->end();++it)
				acumulador<< (*it)->getId() << kMensajeDelimitadorCampos<< datos.getProductoConId((*it)->getId())->getNombre() << kMensajeDelimitadorCampos <<(*it)->getStock()<< kMensajeDelimitadorCampos;
			return acumulador.str();
		}
	}
	return kMensajeError;
}

const std::string Operador::stockHistoricoProducto(const std::string& comandoDeOperacion)const{
	const unsigned long int idProducto = Protocolo::extraerArgumentoNumericoDeComando(comandoDeOperacion,2);
	Producto* productoAInventariar = datos.getProductoConId(idProducto);
	if (productoAInventariar!=NULL){
		const std::list<Stock*>* stockHistoricos = productoAInventariar->getStockHistorico();
		std::stringstream acumulador;
		for(std::list<Stock*>::const_iterator it=stockHistoricos->begin(); it!=stockHistoricos->end();++it)
			acumulador<< (*it)->getFecha() << kMensajeDelimitadorCampos <<(*it)->getCantidad()<< kMensajeDelimitadorCampos;
		return acumulador.str();
	} else {
		return kMensajeError;
	}
}


const std::string Operador::altaImagen(const std::string& comandoDeOperacion){
	Imagen imagenRecibida = recibirImagen(comandoDeOperacion);
	if (cliente.estaConectado()){
		const unsigned long int idImagen = datos.agregarImagen(imagenRecibida);
		if (idImagen){
			std::stringstream acumulador;
			acumulador<< idImagen << kMensajeDelimitadorCampos;
			return acumulador.str();
		}
	}
	return kMensajeError;
}


void Operador::actualizarDeteccionAreaDeVision(AreaDeVision* const areaDeVisionAActualizar, const Imagen& imagenCapturada,const std::string& fechaDeCaptura,const std::string& tipoDeDeteccion){
	//valido que los productos anteriormente detectado en el area de vision existan realmente y no allan sido eliminados en el periodo entre actualizaciones
	validarProductosDetectados(areaDeVisionAActualizar);
	std::list<Producto*>* productosDetectados= new std::list<Producto*>();
	//obtengo todos los producto e itero sobre las iamgenes de cada uno reconociendo la totalidad de sus apariciones.
	const std::list<Producto*>* catalogoProductos = datos.getProductos();
	for(std::list<Producto*>::const_iterator it=catalogoProductos->begin(); it!=catalogoProductos->end();++it){
		unsigned long int aparicionesDelProducto=0;
		for (std::list<unsigned long int>::const_iterator id=(*it)->getIdsImagenes()->begin(); id!=(*it)->getIdsImagenes()->end();++id)
			if (datos.existeImagenConId(*id))
				aparicionesDelProducto+=imagenCapturada.contarApariciones(datos.getImagenConId(*id),tipoDeDeteccion);

		std::cerr << "Se encontraron " << aparicionesDelProducto << " unidades de "
				<< (*it)->getNombre() << "\n";

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
		if (variacionDeStock!=0)
			(*it)->actualizarStock(variacionDeStock,fechaDeCaptura);
	}
	areaDeVisionAActualizar->actualizarDeteccion(productosDetectados);
}

const std::string Operador::actualizarStockAreaDeVision(const std::string& comandoDeOperacion){
	const std::string tipoDeDeteccion = common::Protocolo::extraerArgumentoDeComando(comandoDeOperacion,1);
	const std::string fechaDeCaptura = common::Protocolo::extraerArgumentoDeComando(comandoDeOperacion,3);
	AreaDeVision* areaDeVisionAActualizar = datos.getAreaDeVisionConId(common::Protocolo::extraerArgumentoNumericoDeComando(comandoDeOperacion,2));
	if (areaDeVisionAActualizar!=NULL){
		protocolo.enviarMensaje(cliente, kMensajeOK);
		std::string mensajeRecibido = this->protocolo.recibirMensaje(this->cliente);
		Imagen imagenRecibida = recibirImagen(mensajeRecibido);
		if (cliente.estaConectado() && imagenRecibida.esValida()){
			actualizarDeteccionAreaDeVision(areaDeVisionAActualizar,imagenRecibida,fechaDeCaptura,tipoDeDeteccion);
			return kMensajeOK;
		}
	}
	return kMensajeError;
}

void Operador::actualizarImagenesProducto(Producto* const productoAModificar, std::list<unsigned long int> nuevaListaDeIdsImagenes){
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

const std::string Operador::identificarUsuario(Socket& cliente,const Protocolo& protocolo){
	bool usuarioIdentificado=false;
	while (!usuarioIdentificado){
		const std::string mensajeIdentificacion = protocolo.recibirMensaje(cliente);
		if (mensajeIdentificacion==(kIdentificacionAdministrador+protocolo.getFinalizadorDeMensaje()) || mensajeIdentificacion==(kIdentificacionCliente+protocolo.getFinalizadorDeMensaje())){
			protocolo.enviarMensaje(cliente,kMensajeOK);
			return mensajeIdentificacion;
		} else {
			protocolo.enviarMensaje(cliente,kMensajeError);
		}
	}
	return "";
}
