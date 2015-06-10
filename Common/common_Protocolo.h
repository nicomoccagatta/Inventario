#ifndef COMMON_PROTOCOLO_H_
#define COMMON_PROTOCOLO_H_
#include <string>
#include <string.h>
#include "common_Socket.h"
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


namespace common {

class Protocolo {
 public:
  Protocolo(const std::string& finalizador = kFinalizadorPorDefecto,
            const std::string& remplazoFinalizador =
                kRemplazoFinalizadorPorDefecto);
  virtual ~Protocolo();
  const std::string getFinalizadorDeMensaje() const;
  void setFinalizadorMensaje(const std::string& finalizador);
  const std::string getRemplazoFinalizadorDeMensaje() const;
  void setRemplazoFinalizadorMensaje(const std::string& remplazoFinalizador);
  const std::string recibirMensaje(common::Socket& socket) const;
  void enviarMensaje(common::Socket& socket, const std::string mensaje) const;
  const std::string protocolizarMensaje(std::string mensaje) const;

 private:
  std::string finalizadorDeMensaje;
  std::string remplazoFinalizadorDeMensaje;
};
}
#endif
