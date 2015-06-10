#include "server_BaseDeDatos.h"



namespace server {

BaseDeDatos::BaseDeDatos(std::string rutaProductos,std::string rutaAreasDeVision):productos(new std::list<Producto*>()),areasDeVision(new std::list<AreaDeVision*>()) {
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
			productos->push_back(hidratarProductoDinamico(nodoProducto));
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
	return new Producto(nombreProducto,descripcionProducto,stockHistoricoProducto,idProducto);
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
	return new AreaDeVision(ubicacionAreaDeVision,tipoDeCapturadorAreaDeVision,productosDetectadosAreaDeVision,idAreaDeVision);
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


} /* namespace server */
