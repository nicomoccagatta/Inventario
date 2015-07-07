#ifndef SERVER_OPERADOR_H_
#define SERVER_OPERADOR_H_
#include <iostream>
#include <string>
#include <list>
#include "common_Thread.h"
#include "common_Socket.h"
#include "common_Protocolo.h"
#include "server_MonitorBaseDeDatos.h"
#include "common_Defines.h"
#define kRespuestaNula ""
#define kIdentificacionAdministrador "Admin|"
#define kIdentificacionCliente "Client|"


using common::Protocolo;
using common::Socket;

namespace server {

class Operador : public Thread {
 public:
  Operador(Socket& cliente, const Protocolo& protocolo, MonitorBaseDeDatos& datos);
	virtual ~Operador();
	void run();
	void atenderOperaciones();
	void detenerOperaciones();
	const common::Socket& getCliente() const;
	const std::string realizarOperacion(std::string& comandoDeOperacion);

 private:
	Socket cliente;
	const Protocolo& protocolo;
	MonitorBaseDeDatos& datos;
	bool realizarOperaciones;
	const std::string identificadorUsuario;
	static const std::string identificarUsuario(Socket& cliente, const Protocolo& protocolo);
	const std::string realizarOperacionEspecifica(std::string& comandoDeOperacion);
	const std::string listarProductos()const;
	const std::string listarAreasDeVision()const;
	const std::string detallarProducto(const std::string& comandoDeOperacion)const;
	const std::string enviarImagen(const std::string& comandoDeOperacion);
	const Imagen recibirImagen(const std::string& informacionDeImagen);
	const std::string actualizarStockAreaDeVision(const std::string& comandoDeOperacion);
	const std::string altaProducto(const std::string& comandoDeOperacion);
	const std::string modificacionProducto(const std::string& comandoDeOperacion);
	const std::string bajaProducto(const std::string& comandoDeOperacion);
	const std::string altaAreaDeVision(const std::string& comandoDeOperacion);
	const std::string modificacionAreaDeVision(const std::string& comandoDeOperacion);
	const std::string bajaAreaDeVision(const std::string& comandoDeOperacion);
	const std::string stockGeneral()const;
	const std::string stockAreaDeVision(const std::string& comandoDeOperacion);
	const std::string stockHistoricoProducto(const std::string& comandoDeOperacion)const;
	const std::string altaImagen(const std::string& comandoDeOperacion);
};
}

#endif
