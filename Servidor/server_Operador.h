#ifndef SERVER_OPERADOR_H_
#define SERVER_OPERADOR_H_
#include <iostream>
#include <string>
#include <list>
#include "common_Thread.h"
#include "common_Socket.h"
#include "common_Protocolo.h"
#include "server_BaseDeDatos.h"


namespace server {

class Operador : public Thread {
 public:
  Operador(const common::Socket& cliente, const common::Protocolo& protocolo,
		  BaseDeDatos& datos);
  virtual ~Operador();
  void run();
  void atenderOperaciones();
  void detenerOperaciones();
  const common::Socket& getCliente() const;

 private:
  common::Socket cliente;
  const common::Protocolo& protocolo;
  BaseDeDatos& datos;
  bool realizarOperaciones;
  const std::string realizarOperacion(std::string& comandoDeOperacion);
  static const std::string extraerArgumentoDeComando(
        const std::string& comandoDeOperacion, const size_t numeroArgumento);
  static const unsigned long int extraerArgumentoNumericoDeComando(
	        const std::string& comandoDeOperacion, const size_t numeroArgumento);
  const std::string listarProductos()const;
  const std::string listarAreasDeVision()const;
  const std::string detallarProducto(const std::string& comandoDeOperacion)const;
  const std::string altaProducto(const std::string& comandoDeOperacion);
  const std::string modificacionProducto(const std::string& comandoDeOperacion);
  const std::string bajaProducto(const std::string& comandoDeOperacion);
  const std::string altaAreaDeVision(const std::string& comandoDeOperacion);
  const std::string modificacionAreaDeVision(const std::string& comandoDeOperacion);
  const std::string bajaAreaDeVision(const std::string& comandoDeOperacion);
  const std::string stockGeneral()const;
  const std::string stockAreaDeVision(const std::string& comandoDeOperacion)const;
  const std::string stockHistoricoProducto(const std::string& comandoDeOperacion)const;
};
}

#endif
