/*
 * client_ClienteDemo.cpp
 *
 *  Created on: Jun 10, 2015
 *      Author: ale
 */

#include <iostream>
#include <sstream>

#include "client_ClienteDemo.h"
#include "common_CommandParser.h"
#include "common_Imagen.h"
#include "common_Video.h"

using common::Imagen;
using common::Video;

ClienteDemo::ClienteDemo() : client("localhost","1037"){
	if (!client.estaConectado())
		std::cerr << "NO ESTOY CONECTADO\n";

	if (!this->identificarse())
		std::cerr << "NO ME IDENTIFICO BIEN!\n";
}

ClienteDemo::~ClienteDemo() {
	this->data.eliminarAreasDeVision();
	this->data.eliminarProductos();
}

bool ClienteDemo::identificarse(){
	if (this->client.estaConectado()){
		std::cerr << "Indetificandose...\n";
		protocolo.enviarMensaje(this->client, "Client|");
	}
	if (this->protocolo.recibirMensaje(this->client) == "ok|")
		return true;
	return false;
}

void ClienteDemo::cerrarConeccion(){
	this->client.cerrarConeccion();
}

void ClienteDemo::actualizarIdImagenesDeProducto(Producto* prod){
	if (this->client.estaConectado()){
		std::stringstream ss;
		ss << "C|" << prod->getId() << "|";
		protocolo.enviarMensaje(this->client,ss.str());
	}
	std::string respuesta = protocolo.recibirMensaje(this->client);

	if (respuesta == "error|\n")
		return;

	CommandParser parser;

	parser.tokenize(respuesta);

	std::list<unsigned long int>* ids = prod->getIdsImagenes();

	unsigned int argum = 4;
	try{
		while (true){
			unsigned long int id = 0;
			std::stringstream ss;
			ss << parser.getParametro(argum);
			if (ss.str() == "\n")
				return;
			ss >> id;

			std::cerr << "agrego " << ss.str() << "\n";

			ids->push_back(id);
			++argum;
		}
	}catch (std::exception& e){
		//std::cout << "ya se manejar excepciones:)\n";
		//std::cout << e.what();
	}

}

bool ClienteDemo::actualizarProductos(){
	if (this->client.estaConectado()){
		protocolo.enviarMensaje(this->client,"A|");
	}
	std::string respuesta = protocolo.recibirMensaje(this->client);

	if (respuesta == "error|\n"){
		std::cerr << "error pidiendo productos\n";
		return false;
	}

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
			Producto* nuevo = this->data.agregarProducto(nombre,descripcion,id, idIcono);

			std::cerr << "Agregando Producto:" << id << " "
					  << nombre << " " << descripcion
					  << " id Icono: " << idIcono << std::endl;

			this->actualizarIdImagenesDeProducto(nuevo);

			std::list<unsigned long int>* ids = nuevo->getIdsImagenes();

			std::list<unsigned long int>::iterator it;

			for (it=ids->begin(); it!=ids->end();++it){
				std::cerr << "ID IMAGEN AGREGADA AL MODELO: " << *it << "\n";
			}

			argum+=4;
		}
	}catch (std::exception& e){
		//std::cout << "ya se manejar excepciones:)\n";
		//std::cout << e.what();
	}
	return true;
}

void ClienteDemo::agregarImagenACocaLata(std::string ruta){
	Imagen img(ruta);
	img.mostrarImagen();
	protocolo.enviarImagen(this->client,img);

	std::string idImagen = protocolo.recibirMensaje(this->client);

	std::cerr << "ID: " << idImagen;

	protocolo.enviarMensaje(this->client,"E|16|Coca|lata chiquita y golpeada|3|"+idImagen+"|");

	std::cerr << protocolo.recibirMensaje(this->client);
}

bool ClienteDemo::actualizarAreasDeVision(){
	if (this->client.estaConectado()){
		/*this->agregarImagenACocaLata("/home/ale/git/Inventario/Imagenes/Coca-cola/lunes.jpg");
		this->agregarImagenACocaLata("/home/ale/git/Inventario/Imagenes/Coca-cola/martes.png");
		this->agregarImagenACocaLata("/home/ale/git/Inventario/Imagenes/Coca-cola/miercoles.jpg");
		this->agregarImagenACocaLata("/home/ale/git/Inventario/Imagenes/Coca-cola/jueves.png");
		this->agregarImagenACocaLata("/home/ale/git/Inventario/Imagenes/Coca-cola/viernes.jpg");
		this->agregarImagenACocaLata("/home/ale/git/Inventario/Imagenes/Coca-cola/sabado.jpg");
*/
		protocolo.enviarMensaje(this->client,"B|");
	}
	std::string respuesta = protocolo.recibirMensaje(this->client);

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
			std::string ubicacion = parser.getParametro(argum+1);
			std::string tipo = parser.getParametro(argum+2);

			this->data.agregarAreaDeVision(ubicacion,tipo,id);

			std::cerr << "Agregando Area:" << id << " " << ubicacion << " " << tipo << std::endl;
			argum+=3;
		}
	}catch (std::exception& e){
		//std::cout << "ya se manejar excepciones:)\n";
		//std::cout << e.what();
	}
	return true;
}

const std::list<AreaDeVision*>* ClienteDemo::getAreasDeVision() const{
	return data.getAreasDeVision();
}

const std::list<Producto*>* ClienteDemo::getProductos() const {
	return data.getProductos();
}

std::string ClienteDemo::getImagenConId(unsigned long int id){
	if (this->client.estaConectado()){
		std::stringstream ss;
		ss << "R|" << id << "|";
		protocolo.enviarMensaje(this->client,ss.str());
	}
	std::string respuestaDatosImagen = protocolo.recibirMensaje(this->client);
	std::cerr << "RESPUESTA A R|" << id << "|\n";
	std::cerr << respuestaDatosImagen << "\n";
	if (respuestaDatosImagen == "error|\n")
		return "";
	const unsigned int altoImagen = Protocolo::extraerArgumentoNumericoDeComando(respuestaDatosImagen,2);
	const unsigned int anchoImagen = Protocolo::extraerArgumentoNumericoDeComando(respuestaDatosImagen,3);
	const unsigned long int tamanioImagen = Protocolo::extraerArgumentoNumericoDeComando(respuestaDatosImagen,4);
	protocolo.enviarMensaje(this->client, kMensajeOK);

	std::cerr << "Recibiendo IMAGEN...\n";
	Imagen img = protocolo.recibirImagen(this->client,altoImagen,anchoImagen,tamanioImagen);
	std::cerr << "IMAGEN recibida\n";

	if (!img.esValida()){
		std::cerr << "No recibio bien\n";
		return "";
	}

	std::stringstream ss;
	ss << "clienteDemoImagenes/" << id << ".jpg";
	std::string ruta(ss.str());

	img.guardarEnArchivo(ruta);

	return ruta;
}

void ClienteDemo::enviarFoto(const char* comando, unsigned long int idArea, std::string& fecha,Imagen& img){
	std::stringstream ss;

	ss << comando << idArea << kMensajeDelimitadorCampos << fecha << kMensajeDelimitadorCampos;
	std::cerr << "ENVIANDO: " << ss.str() << "\n";


	this->protocolo.enviarMensaje(this->client,ss.str());

	if (this->protocolo.recibirMensaje(this->client) == kMensajeOK+protocolo.getFinalizadorDeMensaje()){
		this->protocolo.enviarImagen(this->client, img);
	}
	else{
		std::cerr << "NO LLEGO SE ENVIARON BIEN LOS DETALLES NADA\n";
	}
	if (this->protocolo.recibirMensaje(this->client) == kMensajeOK+protocolo.getFinalizadorDeMensaje()){
		std::cerr << "TODO PIOLA\n";
	}else{
		std::cerr << "NO LLEGO NADA\n";
	}

}

void ClienteDemo::enviarFotoTemplateMatching(unsigned long int idArea, std::string& fecha,std::string& rutaDeImagen){
	Imagen img(rutaDeImagen);

	this->enviarFoto("M|",idArea,fecha,img);
}

void ClienteDemo::enviarFotoFeatureMatching(unsigned long int idArea, std::string& fecha,std::string& rutaDeImagen){
	Imagen img(rutaDeImagen);

	this->enviarFoto("N|",idArea,fecha,img);
}



void ClienteDemo::enviarVideo(const char* comando, unsigned long int idArea, std::string& fechaInicio,Video& vid){
	std::stringstream ss;

	std::list<Imagen> frames;
	std::list<std::string> fechas;

	vid.capturasPeriodicasVideo(frames,fechas,fechaInicio,1);

	std::list<Imagen>::iterator itIm;
	std::list<std::string>::iterator itStr;

	for (itIm=frames.begin(), itStr=fechas.begin();
			itIm != frames.end(); ++itIm, ++itStr){
		this->enviarFoto(comando,idArea,*itStr,*itIm);
	}


}

void ClienteDemo::enviarVideoTemplateMatching(unsigned long int idArea, std::string& fechaInicio,std::string& rutaDeVideo){
	Video vid(rutaDeVideo);
	this->enviarVideo("M|",idArea,fechaInicio,vid);
}

void ClienteDemo::enviarVideoFeatureMatching(unsigned long int idArea, std::string& fechaInicio,std::string& rutaDeVideo){
	Video vid(rutaDeVideo);

	this->enviarVideo("N|",idArea,fechaInicio,vid);
}
