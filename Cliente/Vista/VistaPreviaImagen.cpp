/*
 * VistaPreviaImagen.cpp
 *
 *  Created on: Jul 3, 2015
 *      Author: ale
 */

#include <iostream>
#include "VistaPreviaImagen.h"

VistaPreviaImagen::VistaPreviaImagen(Glib::ustring ruta) :
	imagen(Gdk::Pixbuf::create_from_file(ruta,800,600,true)){
	set_title("Vista previa de la imagen");
	set_size_request(800,650);
	vbox = get_vbox();
	vbox->pack_start(imagen,true,true,20);

	buttonBox.add(ok);

	vbox->pack_start(buttonBox,false,false,0);

	ok.set_label("OK");
	ok.signal_clicked().connect( sigc::mem_fun(*this, &VistaPreviaImagen::on_button_OK) );
}

VistaPreviaImagen::~VistaPreviaImagen() {
	std::cerr << "DESTRUYO VISTA PREVIA\n";
}

int VistaPreviaImagen::correr(){
	this->show_all_children();
	int i = this->run();

	imagen.show();
	return i;
}

void VistaPreviaImagen::on_button_OK(){
	hide();
}
