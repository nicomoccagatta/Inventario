/*
 * VistaItemListado.cpp
 *
 *  Created on: 17/6/2015
 *      Author: nicomoccagatta
 */

#include "VistaItemListado.h"

VistaItemListado::VistaItemListado(){
}

void VistaItemListado::setear(const std::string& rutaImagen,
		const std::string& nombre,const std::string& descripcion)
{
	Gtk::Image* image1 = Gtk::manage(new Gtk::Image());
	image1->set(rutaImagen);
	Glib::RefPtr<Gdk::Pixbuf> scaled1 = image1->get_pixbuf()->scale_simple(150,150,Gdk::INTERP_BILINEAR);
	image1->set(scaled1);
	this->pack_start(*image1, true, true, 0);

	label_Nombre.set_text(nombre);
	nom_desc.pack_start(label_Nombre);

	label_Descripcion.set_text(descripcion);
	nom_desc.pack_end(label_Descripcion);

	this->pack_end(nom_desc);

	boton_editar.add_pixlabel("info.xpm",0);
	boton_eliminar.add_pixlabel("info.xpm",0);
	edit_elim.pack_start(boton_editar);
	edit_elim.pack_end(boton_eliminar);

	this->pack_end(edit_elim);
}

VistaItemListado::~VistaItemListado() {
}

