#ifndef COMMON_PROTOCOLO_H_
#define COMMON_PROTOCOLO_H_
#include <string>
#include <string.h>
#include "common_Socket.h"
#include "common_Imagen.h"
#include "common_Defines.h"

#define kFinalizadorPorDefecto "\n"
#define kRemplazoFinalizadorPorDefecto "\3"
#define kMensajeOK "ok|"
#define kMensajeError "error|"
#define kMensajeDelimitadorCampos '|'
#define kIndicadorComandoListarProductos 'A'
#define kIndicadorComandoListarAreasDeVision 'B'
#define kIndicadorComandoDetalleProducto 'C'
#define kIndicadorComandoAltaProducto 'D'
#define kIndicadorComandoModificacionProducto 'E'
#define kIndicadorComandoBajaProducto 'F'
#define kIndicadorComandoAltaAreaDeVision 'G'
#define kIndicadorComandoModificacionAreaDeVision 'H'
#define kIndicadorComandoBajaAreaDeVision 'I'
#define kIndicadorComandoStockGeneral 'J'
#define kIndicadorComandoStockAreaDeVision 'K'
#define kIndicadorComandoStockHistoricoProducto 'L'
#define kIndicadorComandoFotoTemplateMatching 'M'
#define kIndicadorComandoFotoFeatureMatching 'N'
#define kIndicadorComandoVideoTemplateMatching 'O'
#define kIndicadorComandoVideoFeatureMatching 'P'
#define kIndicadorComandoAltaImagen 'Q'
#define kIndicadorComandoSolicitudImagen 'R'
#define kIndicadorComandoBajaImagen 'S'


namespace common {

class Protocolo {
 public:
  Protocolo(const std::string& finalizador = kFinalizadorPorDefecto);
  virtual ~Protocolo();
  const std::string getFinalizadorDeMensaje() const;
  void setFinalizadorMensaje(const std::string& finalizador);
  const std::string recibirMensaje(Socket& socket) const;
  void enviarMensaje(Socket& socket, const std::string mensaje) const;
  const std::string protocolizarMensaje(std::string mensaje) const;
  Imagen recibirImagen(Socket& socket,const unsigned int altoImagen,const unsigned int anchoImagen, const unsigned long int tamanioImagen) const;
  void enviarImagen(Socket& socket,const Imagen& imagenAEnviar) const;
  static const std::string extraerArgumentoDeComando(
          const std::string& comandoDeOperacion, const size_t numeroArgumento);
  static const unsigned long int extraerArgumentoNumericoDeComando(
		  const std::string& comandoDeOperacion, const size_t numeroArgumento);
 private:
  std::string finalizadorDeMensaje;
};
}
#endif
