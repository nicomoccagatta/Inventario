#include "server_BaseDeDatos.h"

namespace server {

BaseDeDatos::BaseDeDatos(std::string rutaProductos,std::string rutaAreasDeVision):productos(new std::list<Producto*>()),areasDeVision(new std::list<AreaDeVision*>()),proximoIdImagenes(0){
	cargarProductos(rutaProductos);
	cargarAreasDeVision(rutaAreasDeVision);
}

BaseDeDatos::~BaseDeDatos() {
	guardarProductos();
	for (std::list<Producto*>::const_iterator it = productos->begin();it!=productos->end();++it)
		delete (*it);
	delete productos;
	guardarAreasDeVision();
	for (std::list<AreaDeVision*>::const_iterator it = areasDeVision->begin();it!=areasDeVision->end();++it)
		delete (*it);
	delete areasDeVision;
}

void BaseDeDatos::cargarProductos(std::string rutaProductos){
	Producto::inicializarCuentaId();
	TiXmlDocument archProductos(rutaProductos);
	if (archProductos.LoadFile()){
		TiXmlElement* nodoProducto=archProductos.FirstChildElement(kTagXMLProducto);
		for(;nodoProducto;nodoProducto = nodoProducto->NextSiblingElement(kTagXMLProducto)){
			Producto* productoHidratado = hidratarProductoDinamico(nodoProducto);
			productos->push_back(productoHidratado);
			contarProximoIdImagenes(productoHidratado);
		}
	}
}

Producto* BaseDeDatos::hidratarProductoDinamico(TiXmlElement* nodoProducto)const{
	if (nodoProducto==NULL)
		return NULL;
	unsigned long int idProducto;
	std::stringstream(nodoProducto->Attribute(kTagXMLId)) >> idProducto;
	TiXmlElement* atributoProducto;
	//obtengo el nombre
	std::string nombreProducto=(atributoProducto=nodoProducto->FirstChildElement())->GetText();
	//obtengo la descripcion
	std::string descripcionProducto=(atributoProducto=atributoProducto->NextSiblingElement(kTagXMLDescripcionProducto))->GetText();
	//itero obteniendo todos los stocks historicos
	std::list<Stock*>* stockHistoricoProducto= new std::list<Stock*>();
	TiXmlElement* nodoStock=(nodoProducto->FirstChildElement(kTagXMLStockHistoricoProducto))->FirstChildElement(kTagXMLStockProducto);
	for(;nodoStock;nodoStock=nodoStock->NextSiblingElement(kTagXMLStockProducto)){
		TiXmlElement* atributoStock;
		std::string fechaStock=(atributoStock=nodoStock->FirstChildElement())->GetText();
		unsigned long int cantidadStock;
		std::stringstream((atributoStock=atributoStock->NextSiblingElement(kTagXMLCantidadStockProducto))->GetText()) >> cantidadStock;
		stockHistoricoProducto->push_back(new Stock(cantidadStock,fechaStock));
	}
	//obtengo el icono
	unsigned long int idIconoProducto;
	std::stringstream((atributoProducto=atributoProducto->NextSiblingElement(kTagXMLIdIconoProducto))->GetText()) >> idIconoProducto;
	//obtengo la lista de ids de imagenes
	std::list<unsigned long int>* idsImagenesProducto = new std::list<unsigned long int>;
	TiXmlElement* nodoImagen=(nodoProducto->FirstChildElement(kTagXMLIdImagenesProducto))->FirstChildElement(kTagXMLIdImagenProducto);
	for(;nodoImagen;nodoImagen=nodoImagen->NextSiblingElement(kTagXMLIdImagenProducto)){
		unsigned long int idImagen;
		std::stringstream(nodoImagen->GetText()) >> idImagen;
		idsImagenesProducto->push_back(idImagen);
	}
	return new Producto(idProducto,nombreProducto,descripcionProducto,stockHistoricoProducto,idIconoProducto,idsImagenesProducto);
}

void BaseDeDatos::guardarProductos(std::string rutaProductos)const{
	TiXmlDocument archProductos(rutaProductos);
	if (archProductos.LoadFile()){
		archProductos.Clear();
		for (std::list<Producto*>::const_iterator it = productos->begin(); it!=productos->end(); ++it){
			archProductos.LinkEndChild(persistirProductoDinamico(*it));
		}
		archProductos.SaveFile(rutaProductos);
	}
}

TiXmlElement* BaseDeDatos::persistirProductoDinamico(Producto* productoAPersistir)const{
	//guardo el id
	TiXmlElement* nodoProducto = new TiXmlElement(kTagXMLProducto);
	nodoProducto->SetAttribute(kTagXMLId,(int)productoAPersistir->getId());
	//guardo el nombre
	TiXmlElement* atributoProducto=new TiXmlElement(kTagXMLNombreProducto);
	atributoProducto->LinkEndChild(new TiXmlText(productoAPersistir->getNombre()));
	nodoProducto->LinkEndChild(atributoProducto);
	//guardo la descripcion
	atributoProducto=new TiXmlElement(kTagXMLDescripcionProducto);
	atributoProducto->LinkEndChild(new TiXmlText(productoAPersistir->getDescripcion()));
	nodoProducto->LinkEndChild(atributoProducto);
	//guardo los stocks historicos
	atributoProducto=new TiXmlElement(kTagXMLStockHistoricoProducto);
	for (std::list<Stock*>::const_iterator stocks = productoAPersistir->getStockHistorico()->begin();stocks!=productoAPersistir->getStockHistorico()->end();++stocks){
		TiXmlElement* nodoStock=new TiXmlElement(kTagXMLStockProducto);
		//guardo la fecha
		TiXmlElement* atributoFecha=new TiXmlElement(kTagXMLFechaStockProducto);
		atributoFecha->LinkEndChild(new TiXmlText((*stocks)->getFecha()));
		nodoStock->LinkEndChild(atributoFecha);
		//guardo la cantidad
		TiXmlElement* atributoCantidad=new TiXmlElement(kTagXMLCantidadStockProducto);
		std::stringstream parseador;
		parseador << (*stocks)->getCantidad();
		atributoCantidad->LinkEndChild(new TiXmlText(parseador.str()));
		nodoStock->LinkEndChild(atributoCantidad);
		atributoProducto->LinkEndChild(nodoStock);
	}
	nodoProducto->LinkEndChild(atributoProducto);
	//guardo el icono
	atributoProducto=new TiXmlElement(kTagXMLIdIconoProducto);
	std::stringstream parseadorIcono;
	parseadorIcono << productoAPersistir->getIdIcono();
	atributoProducto->LinkEndChild(new TiXmlText(parseadorIcono.str()));
	nodoProducto->LinkEndChild(atributoProducto);
	//guardo la lista de ids de imagenes
	atributoProducto=new TiXmlElement(kTagXMLIdImagenesProducto);
	for (std::list<unsigned long int>::const_iterator idImagen = productoAPersistir->getIdsImagenes()->begin(); idImagen!= productoAPersistir->getIdsImagenes()->end(); ++idImagen){
		TiXmlElement* nodoImagen=new TiXmlElement(kTagXMLIdImagenProducto);
		std::stringstream parseador;
		parseador << (*idImagen);
		nodoImagen->LinkEndChild(new TiXmlText(parseador.str()));
		atributoProducto->LinkEndChild(nodoImagen);
	}
	nodoProducto->LinkEndChild(atributoProducto);
	return nodoProducto;
}

Producto* const BaseDeDatos::getProductoConId(const unsigned long int idProductoBuscado) const{
	for (std::list<Producto*>::const_iterator it = productos->begin(); it!=productos->end(); ++it)
		if ((*it)->getId() == idProductoBuscado)
			return (*it);
	return NULL;
}

const std::list<Producto*>* BaseDeDatos::getProductos() const{
	return productos;
}

void BaseDeDatos::agregarProducto(Producto* productoAAgregar){
	productos->push_back(productoAAgregar);
}

void BaseDeDatos::eliminarProducto(const unsigned long int idProductoBuscado){
	for (std::list<Producto*>::const_iterator it = productos->begin(); it!=productos->end(); ++it)
			if ((*it)->getId() == idProductoBuscado){
				delete (*it);
				productos->remove(*it);
				it=productos->end();
			}
}

void BaseDeDatos::cargarAreasDeVision(std::string rutaAreasDeVision){
	AreaDeVision::inicializarCuentaId();
	TiXmlDocument archAreasDeVision(rutaAreasDeVision);
	if (archAreasDeVision.LoadFile()){
		TiXmlElement* nodoAreaDeVision=archAreasDeVision.FirstChildElement(kTagXMLAreaDeVision);
		for(;nodoAreaDeVision;nodoAreaDeVision = nodoAreaDeVision->NextSiblingElement(kTagXMLAreaDeVision)){
			areasDeVision->push_back(hidratarAreaDeVisionDinamica(nodoAreaDeVision));
		}
	}
}

AreaDeVision* BaseDeDatos::hidratarAreaDeVisionDinamica(TiXmlElement* nodoAreaDeVision)const{
	if (nodoAreaDeVision==NULL)
		return NULL;
	unsigned long int idAreaDeVision;
	std::stringstream(nodoAreaDeVision->Attribute(kTagXMLId)) >> idAreaDeVision;
	TiXmlElement* atributoAreaDeVision;
	//obtengo el nombre
	std::string ubicacionAreaDeVision=(atributoAreaDeVision=nodoAreaDeVision->FirstChildElement())->GetText();
	//obtengo la descripcion
	std::string tipoDeCapturadorAreaDeVision=(atributoAreaDeVision=atributoAreaDeVision->NextSiblingElement(kTagXMLTipoDeCapturadorAreaDeVision))->GetText();
	//itero obteniendo todos los stocks historicos
	std::list<Producto*>* productosDetectadosAreaDeVision= new std::list<Producto*>();
	TiXmlElement* nodoProducto=(nodoAreaDeVision->FirstChildElement(kTagXMLProductosDetectadosAreaDeVision))->FirstChildElement(kTagXMLProducto);
	for(;nodoProducto;nodoProducto=nodoProducto->NextSiblingElement(kTagXMLProducto)){
		productosDetectadosAreaDeVision->push_back(hidratarProductoDinamico(nodoProducto));
	}
	return new AreaDeVision(idAreaDeVision,ubicacionAreaDeVision,tipoDeCapturadorAreaDeVision,productosDetectadosAreaDeVision);
}

void BaseDeDatos::guardarAreasDeVision(std::string rutaAreasDeVision)const{
	TiXmlDocument archAreasDeVision(rutaAreasDeVision);
	if (archAreasDeVision.LoadFile()){
		archAreasDeVision.Clear();
		for (std::list<AreaDeVision*>::const_iterator it = areasDeVision->begin(); it!=areasDeVision->end(); ++it){
			archAreasDeVision.LinkEndChild(persistirAreaDeVisionDinamica(*it));
		}
		archAreasDeVision.SaveFile(rutaAreasDeVision);
	}
}

TiXmlElement* BaseDeDatos::persistirAreaDeVisionDinamica(AreaDeVision* AreaDeVisionAPersistir)const{
	//guardo el id
	TiXmlElement* nodoAreaDeVision = new TiXmlElement(kTagXMLAreaDeVision);
	nodoAreaDeVision->SetAttribute(kTagXMLId,(int)AreaDeVisionAPersistir->getId());
	//guardo la ubicacion
	TiXmlElement* atributoAreaDeVision=new TiXmlElement(kTagXMLUbicacionAreaDeVision);
	atributoAreaDeVision->LinkEndChild(new TiXmlText(AreaDeVisionAPersistir->getUbicacion()));
	nodoAreaDeVision->LinkEndChild(atributoAreaDeVision);
	//guardo el tipo de capturador
	atributoAreaDeVision=new TiXmlElement(kTagXMLTipoDeCapturadorAreaDeVision);
	atributoAreaDeVision->LinkEndChild(new TiXmlText(AreaDeVisionAPersistir->getTipoDeCapturador()));
	nodoAreaDeVision->LinkEndChild(atributoAreaDeVision);
	//guardo los productos detectados
	atributoAreaDeVision=new TiXmlElement(kTagXMLProductosDetectadosAreaDeVision);
	for (std::list<Producto*>::const_iterator producto = AreaDeVisionAPersistir->getProductosDetectados()->begin();producto!=AreaDeVisionAPersistir->getProductosDetectados()->end();++producto)
		atributoAreaDeVision->LinkEndChild(persistirProductoDinamico((*producto)));
	nodoAreaDeVision->LinkEndChild(atributoAreaDeVision);
	return nodoAreaDeVision;
}

AreaDeVision* const BaseDeDatos::getAreaDeVisionConId(const unsigned long int idAreaDeVisionBuscada) const{
	for (std::list<AreaDeVision*>::const_iterator it = areasDeVision->begin(); it!=areasDeVision->end(); ++it)
		if ((*it)->getId() == idAreaDeVisionBuscada)
			return (*it);
	return NULL;
}

const std::list<AreaDeVision*>* BaseDeDatos::getAreasDeVision() const{
	return areasDeVision;
}

void BaseDeDatos::agregarAreaDeVision(AreaDeVision* AreaDeVisionAAgregar){
	areasDeVision->push_back(AreaDeVisionAAgregar);
}

void BaseDeDatos::eliminarAreaDeVision(const unsigned long int idAreaDeVisionBuscada){
	for (std::list<AreaDeVision*>::const_iterator it = areasDeVision->begin(); it!=areasDeVision->end(); ++it)
		if ((*it)->getId() == idAreaDeVisionBuscada){
			delete (*it);
			areasDeVision->remove(*it);
			it=areasDeVision->end();
		}
}

//guarda imagenes dentro de la carpeta de imagenes
const unsigned long int BaseDeDatos::agregarImagen(const Imagen& imagenAAgregar){
	mutexImagenes.bloquear();
	std::stringstream parseador;
	parseador << proximoIdImagenes;
	imagenAAgregar.guardarEnArchivo(kRutaPorDefectoImagenes+parseador.str()+kExtensionPorDefectoImagenes);
	mutexImagenes.desbloquear();
	return proximoIdImagenes++;
}

Imagen BaseDeDatos::getImagenConId(const unsigned long int idImagen){
	mutexImagenes.bloquear();
	std::stringstream parseador;
	parseador << idImagen;
	Imagen imagenSolicitada(kRutaPorDefectoImagenes+parseador.str()+kExtensionPorDefectoImagenes);
	mutexImagenes.desbloquear();
	return imagenSolicitada;
}

//elimina una iamgen con el id indicado dentro de la carpeta imagenes
void BaseDeDatos::eliminarImagen(const unsigned long int idImagen){
	mutexImagenes.bloquear();
	std::stringstream parseador;
	parseador << idImagen;
	remove((kRutaPorDefectoImagenes+parseador.str()+kExtensionPorDefectoImagenes).c_str());
	mutexImagenes.desbloquear();
}

const bool BaseDeDatos::existeImagenConId(const unsigned long int idImagen){
	mutexImagenes.bloquear();
	if (idImagen<proximoIdImagenes){
		std::stringstream parseador;
		parseador << idImagen;
		bool existeImagenSolicitada =Imagen::existeImagen(kRutaPorDefectoImagenes+parseador.str()+kExtensionPorDefectoImagenes);
		mutexImagenes.desbloquear();
		return existeImagenSolicitada;
	}
	mutexImagenes.desbloquear();
	return false;
}

void BaseDeDatos::contarProximoIdImagenes(Producto* const productoConImagenes){
	if (productoConImagenes->getIdIcono()>= proximoIdImagenes)
		proximoIdImagenes= (productoConImagenes->getIdIcono())+1;
	for (std::list<unsigned long int>::const_iterator idImagen = productoConImagenes->getIdsImagenes()->begin(); idImagen!= productoConImagenes->getIdsImagenes()->end(); ++idImagen)
		if ((*idImagen) >= proximoIdImagenes)
				proximoIdImagenes= (*idImagen)+1;
}

} /* namespace server */
