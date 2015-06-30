/*
 * VistaCrearVideo.cpp
 *
 *  Created on: Jun 29, 2015
 *      Author: ale
 */

#include <iostream>

#include "VistaCrearVideo.h"


VistaCrearVideo::VistaCrearVideo(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade)
: Gtk::Viewport(cobject),
  	  m_refGlade(refGlade), activa(0){


	m_AgregarButton.set_label("Agregar");
	m_AgregarButton.signal_clicked().connect( sigc::mem_fun(*this, &VistaCrearVideo::on_button_Agregar));

	m_EliminarButton.set_label("Eliminar");
	m_EliminarButton.signal_clicked().connect( sigc::mem_fun(*this, &VistaCrearVideo::on_button_Eliminar) );

	m_ButtonBoxAgregaryEliminar.pack_start(m_AgregarButton);
	m_ButtonBoxAgregaryEliminar.pack_start(m_EliminarButton);
	m_ButtonBoxAgregaryEliminar.set_layout(Gtk::BUTTONBOX_START);

	verticalBox.pack_start(m_ButtonBoxAgregaryEliminar,Gtk::PACK_SHRINK,true,0);

	m_ImagenesList.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
	m_ImagenesList.set_size_request(150,400);
	m_ImagenesList.add(m_ImagenesTreeView);

	m_refImagenesListStore = Gtk::ListStore::create(m_ImagenesList.m_Columns);
	m_ImagenesTreeView.set_model(m_refImagenesListStore);

	m_ImagenesTreeView.append_column("Imagen", m_ImagenesList.m_Columns.m_col_imagenIcono);
	m_ImagenesTreeView.append_column("Nombre archivo", m_ImagenesList.m_Columns.m_col_nombre);
	m_ImagenesTreeView.append_column("Ruta", m_ImagenesList.m_Columns.m_col_ruta);
	m_ImagenesTreeView.set_reorderable();

	refTreeSelection = m_ImagenesTreeView.get_selection();
	refTreeSelection->signal_changed().connect(
			    sigc::mem_fun(*this, &VistaCrearVideo::on_producto_seleccionado) );

	hBoxListados.pack_start(m_ImagenesList);
	labelMasVistaPreviaMasPlayStopPausa.set_size_request(400,Gtk::EXPAND);
	hBoxListados.pack_start(m_Vseparator);
	hBoxListados.pack_end(labelMasVistaPreviaMasPlayStopPausa);

	labelMasVistaPreviaMasPlayStopPausa.pack_start(paraImagenMala, false, false, 0);

	m_PlayButton.set_label("Play");
	m_PlayButton.signal_clicked().connect( sigc::mem_fun(*this, &VistaCrearVideo::on_button_Play));

	m_PausaButton.set_label("Pausa");
	m_PausaButton.signal_clicked().connect( sigc::mem_fun(*this, &VistaCrearVideo::on_button_Pausa) );

	m_StopButton.set_label("Stop");
	m_StopButton.signal_clicked().connect( sigc::mem_fun(*this, &VistaCrearVideo::on_button_Stop) );


	m_ButtonBoxPlayPausaStop.pack_start(m_PlayButton);
	m_ButtonBoxPlayPausaStop.pack_start(m_PausaButton);
	m_ButtonBoxPlayPausaStop.pack_start(m_StopButton);
	m_ButtonBoxPlayPausaStop.set_layout(Gtk::BUTTONBOX_START);
	labelMasVistaPreviaMasPlayStopPausa.pack_end(m_ButtonBoxPlayPausaStop);


	verticalBox.pack_end(hBoxListados);

	add(verticalBox);
	show_all_children();

}

VistaCrearVideo::~VistaCrearVideo() {
	// TODO Auto-generated destructor stub
}

void VistaCrearVideo::on_button_Agregar(){
	/*Abro el dialogo para elegir nombre de archivo, la extencion se pone sola
	 * la misma de la imagen original*/
	Gtk::FileChooserDialog dialog("Elige una imagen",
			Gtk::FILE_CHOOSER_ACTION_OPEN);

	//Add response buttons the the dialog:
	dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
	dialog.add_button("Select", Gtk::RESPONSE_OK);

	int result = dialog.run();

	//Handle the response:
	switch(result){
	case(Gtk::RESPONSE_OK):{
		std::cerr << "Select clicked." << std::endl;
		std::cerr << "Folder selected: " << dialog.get_filename()
		        				<< std::endl;

		this->agregarImagenALista(dialog.get_filename());

		break;
	}
	case(Gtk::RESPONSE_CANCEL):{
		std::cerr << "Cancel clicked." << std::endl;
		break;
	}
	default:{
		std::cerr << "Unexpected button clicked." << std::endl;
		break;
	}
	}
}

void VistaCrearVideo::agregarImagenALista(Glib::ustring rutaCompleta){
	std::stringstream iss(rutaCompleta);
	std::string nombre;

	while(std::getline(iss, nombre, '/'));

	std::cerr << "EL NOMBRE ES: " << nombre
			<< "\nLA RUTA COMPLETA: " << rutaCompleta << "\n";

	Gtk::TreeModel::Row row = *(m_refImagenesListStore->append());
	Glib::RefPtr<Gdk::Pixbuf>  icon = Gdk::Pixbuf::create_from_file(rutaCompleta,30,30,false);
	//AspectPreservingScalingImage* apsi = new AspectPreservingScalingImage(Gdk::Pixbuf::create_from_file(rutaCompleta));//,300,300,true);
	Gtk::Image* image = new Gtk::Image(rutaCompleta);
	Glib::RefPtr<Gdk::Pixbuf> buf = image->get_pixbuf();

	std::cerr << "WIDTH: " << buf->get_width()
			<< " HEIGHT: " << buf->get_height() << std::endl;

	Glib::RefPtr<Gdk::Pixbuf> scaled1 = image->get_pixbuf()->scale_simple(
			buf->get_width()/8,buf->get_height()/8,Gdk::INTERP_BILINEAR);
	image->set(scaled1);

	row[m_ImagenesList.m_Columns.m_col_imagenIcono] = icon;
	row[m_ImagenesList.m_Columns.m_col_nombre] = nombre;
	row[m_ImagenesList.m_Columns.m_col_ruta] = rutaCompleta;
	row[m_ImagenesList.m_Columns.m_col_imgGrande] = image;
}

void VistaCrearVideo::on_button_Eliminar(){
	Gtk::TreeModel::iterator iter = refTreeSelection->get_selected();
	if(iter){ //If anything is selected
		m_refImagenesListStore->erase(iter);
	}
}

void VistaCrearVideo::on_producto_seleccionado(){

	if (this->activa)
		this->paraImagenMala.remove(*activa);

	Gtk::TreeModel::iterator iter = refTreeSelection->get_selected();
	if(iter){ //If anything is selected
		Gtk::TreeModel::Row row = *iter;

		this->paraImagenMala.pack_start(
				*row[m_ImagenesList.m_Columns.m_col_imgGrande], false, false, 0);

		this->activa = row[m_ImagenesList.m_Columns.m_col_imgGrande];
	}
	show_all_children();
}

void VistaCrearVideo::on_button_Play(){

}

void VistaCrearVideo::on_button_Pausa(){

}

void VistaCrearVideo::on_button_Stop(){

}
