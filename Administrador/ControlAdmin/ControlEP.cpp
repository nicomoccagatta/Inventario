#include "ControlEP.h"
#include "VistaAdmin/VistaEditarProducto.h"

ControlEP::ControlEP(Gtk::VBox *button,std::string *sfiledir,void *view): boton(button), filedir(sfiledir), id(0), vista(view) {
}

ControlEP::ControlEP(Gtk::VBox *button,unsigned long int idImagen,void *view): boton(button),filedir(0), id(idImagen), vista(view) {
}

void ControlEP::on_button_eliminarIconoConFileDir(){
	((VistaEditarProducto*)(vista))->eliminarIconoPertenecienteABotonFileDir(boton,filedir);
}

void ControlEP::on_button_eliminarIconoConID(){
	((VistaEditarProducto*)(vista))->eliminarIconoPertenecienteABotonID(boton,id);
}

ControlEP::~ControlEP() {
}

