#include "Administrador.h"
#include <iostream>
#include <sstream>
#include "common_CommandParser.h"
#include "common_Imagen.h"

using common::Imagen;

Administrador::Administrador() : admin("localhost","1037"){
	if (!admin.estaConectado())
		std::cerr << "NO ESTOY CONECTADO\n";
	protocolo.enviarMensaje(this->admin,"Admin|");
	std::string respuesta = protocolo.recibirMensaje(this->admin);
	if (respuesta == "ok|\n")
		std::cerr << "Admin logueado correctamente" << std::endl;
}

Administrador::~Administrador() {
	this->data.eliminarAreasDeVision();
	this->data.eliminarProductos();
}

void Administrador::cerrarConeccion(){
	this->admin.cerrarConeccion();
}

bool Administrador::actualizarProductos(){
	if (this->admin.estaConectado()){
		protocolo.enviarMensaje(this->admin,"A|");
	}
	std::string respuesta = protocolo.recibirMensaje(this->admin);

	if (respuesta == "error|\n")
		return false;

	this->data.eliminarProductos();

	CommandParser parser;
	parser.tokenize(respuesta);

	unsigned int argum = 1;
	try{
		while (true){
			unsigned long int id;
			std::stringstream ss;
			ss << parser.getParametro(argum);
			ss >> id;
			std::string nombre = parser.getParametro(argum+1);
			std::string descripcion = parser.getParametro(argum+2);

			unsigned long int idIcono;
			ss.clear();
			ss.flush();
			ss.str("");
			ss << parser.getParametro(argum+3);
			ss >> idIcono;
			this->data.agregarProducto(nombre,descripcion,id, idIcono);
			argum+=4;
		}
	}catch (std::exception& e){
	}
	return true;
}

void Administrador::altaProducto(std::string &nombre,std::string &descripcion,std::string &rutaImagenPPAL,std::list<std::string*> &rutaImagenes){
	if (this->admin.estaConectado()){
		long unsigned int idImagen = altaImagen(rutaImagenPPAL);
		std::string mensajeEnviar = "D|" + nombre + '|' + descripcion + '|';
		std::stringstream ssID;
		ssID << idImagen;
		mensajeEnviar += ssID.str() + '|';
		protocolo.enviarMensaje(this->admin,mensajeEnviar);
		std::string respuesta = protocolo.recibirMensaje(this->admin);
		CommandParser parser;
		parser.tokenize(respuesta);
		std::stringstream ssIDProducto;
		ssIDProducto << parser.getParametro(1);

		std::list<long unsigned int> idsImagenes;
		std::list<std::string*>::iterator it = rutaImagenes.begin();
		for (; it!=rutaImagenes.end() ; ++it){
			long unsigned int idAgregar = altaImagen(*(*it));
			idsImagenes.push_back(idAgregar);
		}
		mensajeEnviar = "E|" + ssIDProducto.str() + '|' + nombre +'|' + descripcion +'|' + ssID.str() + '|';
		std::list<long unsigned int>::iterator iterator = idsImagenes.begin();
		for(; iterator != idsImagenes.end() ; ++iterator){
			std::stringstream ss;
			ss << (*iterator);
			mensajeEnviar += ss.str();
			mensajeEnviar += '|';
		}
		protocolo.enviarMensaje(this->admin,mensajeEnviar);
		respuesta = protocolo.recibirMensaje(this->admin);
	}
}

void Administrador::eliminarProducto(unsigned long int id){
	data.eliminarProducto(id);
	if (this->admin.estaConectado()){
			std::stringstream ssID;
			ssID << id;
			std::string mensajeEnviar = "F|" + ssID.str();
			protocolo.enviarMensaje(this->admin,mensajeEnviar);
		}
	std::string respuesta = protocolo.recibirMensaje(this->admin);
}

void Administrador::modificarProducto(unsigned long int id,std::string &nombre,std::string &descripcion,std::string &rutaImagenPPAL,
												std::list<unsigned long int> idsAnteriores,std::list<std::string*> &rutaImagenesAgregar){
	std::stringstream ssIDProducto;
	ssIDProducto << id;
	long unsigned int idIcono = altaImagen(rutaImagenPPAL);
	std::stringstream ssIDIcono;
	ssIDIcono << idIcono;
	std::string mensajeEnviar = "E|" + ssIDProducto.str() + '|' + nombre +'|' + descripcion +'|' + ssIDIcono.str() + '|';
	std::list<unsigned long int>::iterator it = idsAnteriores.begin();
	for(; it != idsAnteriores.end() ; ++it){
		std::stringstream ssIDAnt;
		ssIDAnt << (*it);
		mensajeEnviar += ssIDAnt.str();
		mensajeEnviar += '|';
	}
	std::list<std::string*>::iterator iterator = rutaImagenesAgregar.begin();
	for(; iterator != rutaImagenesAgregar.end() ; ++iterator){
		long unsigned int idImagen = altaImagen(*(*iterator));
		std::stringstream ss;
		ss << idImagen;
		mensajeEnviar += ss.str();
		mensajeEnviar += '|';
	}
	protocolo.enviarMensaje(this->admin,mensajeEnviar);
	std::string respuesta = protocolo.recibirMensaje(this->admin);
}

bool Administrador::actualizarAreasDeVision(){
	if (this->admin.estaConectado()){
		protocolo.enviarMensaje(this->admin,"B|");
	}
	std::string respuesta = protocolo.recibirMensaje(this->admin);

	if (respuesta == "error|\n")
		return false;

	this->data.eliminarAreasDeVision();

	CommandParser parser;

	parser.tokenize(respuesta);
	unsigned int argum = 1;
	try{
		while (true){
			unsigned long int id;
			std::stringstream ss;
			ss << parser.getParametro(argum);
			ss >> id;
			std::string preguntarProductos("K|");
			std::stringstream ssaux;
			ssaux << id;
			preguntarProductos += ssaux.str();
			std::list<Producto*>* productos;
			productos = new std::list<Producto*>;
			protocolo.enviarMensaje(this->admin,preguntarProductos);
			std::string respuestaProd = protocolo.recibirMensaje(this->admin);
			if (respuestaProd != "error|\n"){
				CommandParser parserProd;
				parserProd.tokenize(respuestaProd);
				unsigned int argumProd = 1;
				try{
					while(true){
						std::stringstream obtenerID;

						unsigned long int idProd;
						obtenerID << parserProd.getParametro(argumProd);
						obtenerID >> idProd;

						std::string nombreProd;
						nombreProd = parserProd.getParametro(argumProd+1);

						unsigned long int idIcono;
						std::stringstream ssIdIcono;
						ssIdIcono << parserProd.getParametro(argumProd+2);
						ssIdIcono >> idIcono;

						int CantProd;
						std::stringstream obtenerCant;
						obtenerCant << parserProd.getParametro(argumProd+3);
						obtenerCant >> CantProd;
						std::list<common::Stock*> *stockProd = new std::list<common::Stock*>;
						common::Stock* stockProducto = new common::Stock(CantProd,"listado");
						stockProd->push_back(stockProducto);

						argumProd += 4;

						Producto *producto = new Producto(idProd,nombreProd,"",stockProd,idIcono,0);
						productos->push_back(producto);
					}
				}catch (std::exception& e){
				}
			}
			std::string ubicacion = parser.getParametro(argum+1);
			std::string tipo = parser.getParametro(argum+2);
			this->data.agregarAreaDeVision(ubicacion,tipo,id,productos);

			argum+=3;
		}
	}catch (std::exception& e){
	}
	return true;
}

void Administrador::altaAreaVision(const std::string &ubicacion,const std::string &capturador){
	if (this->admin.estaConectado()){
			std::string mensajeAEnviar = "G|" + ubicacion + '|' + capturador + '|';
			protocolo.enviarMensaje(this->admin,mensajeAEnviar);
			std::string respuesta = protocolo.recibirMensaje(this->admin);
		}
}

void Administrador::eliminarAreaVision(unsigned long int idAV){
	data.eliminarAreaVision(idAV);
	if (this->admin.estaConectado()){
		std::stringstream ssIDAV;
		ssIDAV << idAV;
		std::string mensajeAEnviar = "I|" + ssIDAV.str() + '|';
		protocolo.enviarMensaje(this->admin,mensajeAEnviar);
	}
	std::string respuesta = protocolo.recibirMensaje(this->admin);
}

void Administrador::modificarAreaVision(unsigned long int idAV,std::string& ubicacion,std::string& capturador){
	if (this->admin.estaConectado()){
		std::stringstream ssID;
		ssID << idAV;
		std::string mensajeAEnviar = "H|" + ssID.str() + '|' + ubicacion + '|' + capturador + '|';
		protocolo.enviarMensaje(this->admin,mensajeAEnviar);
		std::string respuesta = protocolo.recibirMensaje(this->admin);
	}
}

long unsigned int Administrador::altaImagen(std::string &rutaImagen){
	Imagen imgppal(rutaImagen);
	protocolo.enviarImagen(this->admin,imgppal);
	std::string respuesta = protocolo.recibirMensaje(this->admin);
	CommandParser parser;
	parser.tokenize(respuesta);
	std::stringstream ssID;
	ssID << parser.getParametro(1);
	long unsigned int id;
	ssID >> id;
	return id;
}

std::list<unsigned long int> Administrador::getIdsImagenes(unsigned long int idProducto){
	std::list<unsigned long int> listaIDS;
	if (this->admin.estaConectado()){
		std::stringstream ssId;
		ssId << idProducto;
		std::string mensajeAEnviar = "C|" + ssId.str() + '|';
		protocolo.enviarMensaje(this->admin,mensajeAEnviar);
		std::string respuesta = protocolo.recibirMensaje(this->admin);
		CommandParser parserProd;
		parserProd.tokenize(respuesta);
		for(unsigned int argumImagen = 4; argumImagen < parserProd.getCantParamtros() ; argumImagen++)
		{
				int idImagen;
				std::stringstream obtenerID;
				obtenerID << parserProd.getParametro(argumImagen);
				obtenerID >> idImagen;
				this->getImagenConID(idImagen);
				listaIDS.push_back(idImagen);
		}
	}
	return listaIDS;
}

std::string Administrador::getImagenConID(unsigned long int id){
	std::string ruta;
	if (this->admin.estaConectado()){
		std::list<unsigned long int>::iterator it = idsDescargados.begin();
		bool idYaEsta = false;
		for ( ; it != idsDescargados.end() ; ++it){
			if (id == (*it))
					idYaEsta = true;
		}
		if (!idYaEsta){
				std::stringstream ssConsulta;
				ssConsulta << "R|" << id << "|";
				protocolo.enviarMensaje(this->admin,ssConsulta.str());
			std::string respuestaDatosImagen = protocolo.recibirMensaje(this->admin);
			if (respuestaDatosImagen == "error|\n"){
				std::cerr << "No encontro imagen del ID: " << id << "\n";
				return IMAGEN_DEFAULT;
			}
			const unsigned int altoImagen = Protocolo::extraerArgumentoNumericoDeComando(respuestaDatosImagen,2);
			const unsigned int anchoImagen = Protocolo::extraerArgumentoNumericoDeComando(respuestaDatosImagen,3);
			const unsigned long int tamanioImagen = Protocolo::extraerArgumentoNumericoDeComando(respuestaDatosImagen,4);
			protocolo.enviarMensaje(this->admin, kMensajeOK);

			Imagen img = protocolo.recibirImagen(this->admin,altoImagen,anchoImagen,tamanioImagen);
			idsDescargados.push_back(id);

			if (!img.esValida()){
				std::cerr << "No recibio bien\n";
				return IMAGEN_DEFAULT;
			}
			std::stringstream ss;
			ss << RUTA_CARPETA_TEMP << id << ".jpg";
			ruta = ss.str();
			img.guardarEnArchivo(ruta);
			return ruta;
		}else{
			std::stringstream ss;
			ss << RUTA_CARPETA_TEMP << id << ".jpg";
			ruta = ss.str();
			return ruta;
		}
}
	return IMAGEN_DEFAULT;
}

void Administrador::actualizarStockGeneral(){
	stockGeneral.clear();
	if (this->admin.estaConectado()){
		std::string mensajeAEnviar = "J|";
		protocolo.enviarMensaje(this->admin,mensajeAEnviar);
		std::string respuesta = protocolo.recibirMensaje(this->admin);
		CommandParser parserProd;
		parserProd.tokenize(respuesta);
		for(unsigned int argum = 1; argum < parserProd.getCantParamtros() ; argum+=2)
		{
			unsigned long int idProducto,cantidad;
			std::stringstream ssIDProducto, ssCantidad;
			ssIDProducto << parserProd.getParametro(argum);
			ssIDProducto >> idProducto;
			ssCantidad << parserProd.getParametro(argum+1);
			ssCantidad >> cantidad;
			stockGeneral[idProducto] = cantidad;
		}
	}
}

unsigned long int Administrador::consultarStock(unsigned long int idProd){
	return stockGeneral[idProd];
}

std::list<common::Stock> Administrador::getStockHisto(unsigned long int idProducto){
	std::list<common::Stock> stockList;
	if (this->admin.estaConectado()){
		std::stringstream ssIdProducto;
		ssIdProducto << idProducto;
		std::string mensajeAEnviar = "L|" + ssIdProducto.str() + '|';
		protocolo.enviarMensaje(this->admin,mensajeAEnviar);
		std::string respuesta = protocolo.recibirMensaje(this->admin);
		CommandParser parserProd;
		parserProd.tokenize(respuesta);
		for(unsigned int argum = 1; argum < parserProd.getCantParamtros() ; argum+=2){
			std::string fecha = parserProd.getParametro(argum);
			unsigned long int cantidad;
			std::stringstream ssCantidad;
			ssCantidad << parserProd.getParametro(argum+1);
			ssCantidad >> cantidad;
			common::Stock stock(cantidad,fecha);
			stockList.push_back(stock);
		}
	}
	return stockList;
}

const std::list<AreaDeVision*>* Administrador::getAreasDeVision() const{
	return data.getAreasDeVision();
}

const std::list<Producto*>* Administrador::getProductos() const {
	return data.getProductos();
}
