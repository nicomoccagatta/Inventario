#include <string>
#include <iostream>
#include "common_Socket.h"

using common::Socket;

Socket::Socket(int skt)
    : buffer(new char[kLargoBuffer]()), elementosEnBuffer(0), skt(skt) {
  if (skt < 0)
    this->coneccionExitosa = false;
  else
    this->coneccionExitosa = true;
}

Socket::Socket(const Socket& otroSocket)
    : buffer(new char[kLargoBuffer]()),
      coneccionExitosa(otroSocket.coneccionExitosa),
      direccionVinculada(otroSocket.direccionVinculada),
      elementosEnBuffer(otroSocket.elementosEnBuffer),
      skt(otroSocket.skt) {
  strncpy(this->buffer, otroSocket.buffer, kLargoBuffer);
}

Socket::~Socket() { delete[] this->buffer; }

bool Socket::estaConectado() const { return this->coneccionExitosa; }

void Socket::enviarMensaje(const std::string& mensaje) {
  if (this->estaConectado()) {
    unsigned int largoMensaje = mensaje.length();
    unsigned int bytesEnviados = 0;
    int resultadoDeEmision;
    while (bytesEnviados < largoMensaje && this->estaConectado()) {
      resultadoDeEmision = send(this->skt, &mensaje[bytesEnviados],
                                largoMensaje - bytesEnviados, MSG_NOSIGNAL);
      if (resultadoDeEmision <= 0)
        this->cerrarConeccion();
      else
        bytesEnviados += resultadoDeEmision;
    }
  }
}

std::string Socket::recibirMensajeFinalizado(const std::string& finalizador) {
  std::string mensaje = "";
  while (this->estaConectado()) {
    // si hay elementos en el buffer los vuelco al mensaje.
    mensaje.append(this->corrimientoBuffer(finalizador));
    // si no se completo el mensaje trato de recibir hasta finalizarlo.
    if (mensaje.length() == 0 ||
        (mensaje.length() > 0 &&
         mensaje[mensaje.length() - 1] != finalizador[0])) {
      int bytesRecibidos =
          recv(this->skt, this->buffer, kLargoBuffer, MSG_NOSIGNAL);
      if (bytesRecibidos <= 0)
        this->cerrarConeccion();
      else
        this->elementosEnBuffer += bytesRecibidos;
    } else {
      return mensaje;
    }
  }
  return mensaje;
}

void Socket::enviarBytes(const unsigned char* const bytesAEnviar, const unsigned long int cantidadDeBytesAEnviar){
	if (this->estaConectado()) {
		unsigned int bytesEnviados = 0;
		int resultadoDeEmision;
		while (bytesEnviados < cantidadDeBytesAEnviar && this->estaConectado()) {
		  resultadoDeEmision = send(this->skt, &bytesAEnviar[bytesEnviados],
									cantidadDeBytesAEnviar - bytesEnviados, MSG_NOSIGNAL);
		  if (resultadoDeEmision <= 0)
			this->cerrarConeccion();
		  else
			bytesEnviados += resultadoDeEmision;
		}
	  }
}

unsigned char* const Socket::recibirBytesDinamicos(const unsigned long int cantidadDeBytesARecibir){
	unsigned char* buffer;
	try{
		buffer = new unsigned char[cantidadDeBytesARecibir];
	} catch (...){
		return NULL;
	}
	unsigned long int cantidadDeBytesRecibidos=0;
	while (this->estaConectado() && (cantidadDeBytesRecibidos<cantidadDeBytesARecibir)) {
	      int bytesRecibidos = recv(this->skt, &buffer[cantidadDeBytesRecibidos], (cantidadDeBytesARecibir-cantidadDeBytesRecibidos), MSG_NOSIGNAL);
	      if (bytesRecibidos <= 0)
	        this->cerrarConeccion();
	      else
	    	  cantidadDeBytesRecibidos += bytesRecibidos;
	}
	std::cerr << "RECIBI " << cantidadDeBytesRecibidos << "\n";
	return buffer;
}

std::string Socket::corrimientoBuffer(const std::string& finalizador) {
  std::stringstream mensaje;
  bool mensajeFinalizado = false;
  unsigned int tamanioOriginalBuffer = this->elementosEnBuffer;
  for (unsigned int i = 0; i < tamanioOriginalBuffer && !mensajeFinalizado;
       i++) {
    mensaje << this->buffer[i];
    this->elementosEnBuffer--;
    if (this->buffer[i] == finalizador[0])
      strncpy(this->buffer, &this->buffer[i + 1], this->elementosEnBuffer);
  }
  return mensaje.str();
}

void Socket::abortarConeccion() {
  if (this->estaConectado()) {
    shutdown(this->skt, SHUT_RDWR);
    close(skt);
  }
}

void Socket::cerrarConeccion() {
  if (this->estaConectado()) {
    this->abortarConeccion();
    this->coneccionExitosa = false;
  }
}

void Socket::conectarConDireccion(const addrinfo& direccionAConectar) {
  if (this->estaConectado()) {
    this->cerrarConeccion();
  }
  this->skt =
      socket(direccionAConectar.ai_family, direccionAConectar.ai_socktype,
             direccionAConectar.ai_protocol);
  if (this->skt == -1) {
    this->coneccionExitosa = false;
  } else {
    if (connect(skt, direccionAConectar.ai_addr,
                direccionAConectar.ai_addrlen) != -1) {
      this->coneccionExitosa = true;
    } else {
      this->coneccionExitosa = false;
    }
  }
}

void Socket::esperarConecciones(const addrinfo& direccionAEscuchar,
                                size_t maximoDeClientesAEscuchar) {
  if (this->estaConectado()) {
    this->cerrarConeccion();
  }
  this->skt =
      socket(direccionAEscuchar.ai_family, direccionAEscuchar.ai_socktype,
             direccionAEscuchar.ai_protocol);
  if (this->skt == -1) {
    this->coneccionExitosa = false;
  } else {
    if (bind(this->skt, direccionAEscuchar.ai_addr,
             direccionAEscuchar.ai_addrlen) == -1) {
      close(skt);
      this->coneccionExitosa = false;
    } else {
      if (listen(skt, maximoDeClientesAEscuchar)) {
        close(skt);
        this->coneccionExitosa = false;
      } else {
        this->coneccionExitosa = true;
      }
    }
  }
}

Socket Socket::aceptarCliente() {
  if (this->estaConectado()) {
    int nuevoSocket = accept(this->skt, NULL, NULL);
    if (nuevoSocket != -1) {
      return Socket(nuevoSocket);
    } else {
      this->cerrarConeccion();
    }
  }
  return Socket();
}
