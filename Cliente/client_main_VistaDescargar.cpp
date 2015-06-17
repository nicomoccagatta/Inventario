/*
 * client_main.cpp
 *
 *  Created on: Jun 11, 2015
 *      Author: ale
 */
#include <string>
#include <iostream>

#include "Control/client_ControladorVistaEnviar.h"
#include "Modelo/client_ModeloObservable.h"
#include "Vista/client_VistaEnviar.h"
#include "Vista/client_VistaDescargaImagenDeProductos2.h"

#define VISTA_ENVIAR "Enviar_Imagen_2.4.glade"
#define VISTA_DESCARGAR "Descargar_Imagenes_Productos.glade"




int main(int argc, char* argv[]) {
  ModeloObservable modelo;

  modelo.actualizarProductos();
  modelo.actualizarAreasDeVision();

  Gtk::Main kit(argc, argv);

  VistaDescargaImagenDeProductos2 vista(&modelo);

  //vista.asignarModelo(&modelo);

  vista.show();

  Gtk::Main::run();

  return 0;
}
