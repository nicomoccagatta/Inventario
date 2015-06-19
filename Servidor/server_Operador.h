#ifndef SERVER_OPERADOR_H_
#define SERVER_OPERADOR_H_
#include <iostream>
#include <string>
#include <list>
#include "common_Thread.h"
#include "common_Socket.h"
#include "common_Protocolo.h"
#include "server_BaseDeDatos.h"
#define kRespuestaNula ""

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
  const std::string stockAreaDeVision(const std::string& comandoDeOperacion);
  const std::string stockHistoricoProducto(const std::string& comandoDeOperacion)const;
  const std::string altaImagen(const std::string& comandoDeOperacion);
  const std::string enviarImagen(const std::string& comandoDeOperacion);
  const std::string actualizarStockAreaDeVision(const std::string& comandoDeOperacion);

  const Imagen recibirImagen(const std::string& informacionDeImagen);
  void actualizarImagenesProducto(Producto* const, std::list<unsigned long int> nuevosIdImagenes);
  void actualizarDeteccionAreaDeVision(AreaDeVision* const areaDeVisionAActualizar, const Imagen& imagenCapturada,const std::string& fechaDeCaptura,const std::string& tipoDeDeteccion);
  void validarProductosDetectados(AreaDeVision* const areaDeVisionAValidar);
};
}

#endif
