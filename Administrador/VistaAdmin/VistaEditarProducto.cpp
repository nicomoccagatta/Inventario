/*
 * VistaAgregarProducto.cpp
 *
 *  Created on: 21/6/2015
 *      Author: nicomoccagatta
 */

#include "VistaEditarProducto.h"

VistaEditarProducto::VistaEditarProducto(Modelo_Observable *model,unsigned long int idProducto,std::string& nombre,std::string& descripcion,
						unsigned long int idIcono,std::list<unsigned long int> idsImagenes) : modelo(model),m_idProducto(idProducto),m_idsImagenes(idsImagenes) {
	this->set_size_request(900,700);
	this->set_title("Editar Producto");
	this->set_position(Gtk::WIN_POS_CENTER);
	this->set_resizable(false);

	m_labelNombre.set_text("Nombre");
	m_labelNombre.set_size_request(100,30);
	hBoxNombre.pack_start(m_labelNombre);
	m_ingresarNombre.set_size_request(680,30);
	m_ingresarNombre.set_text(nombre);
	hBoxNombre.pack_end(m_ingresarNombre);
	m_vBoxPrincipal.pack_start(hBoxNombre);

	m_labelDescripcion.set_text("Descripcion");
	m_labelDescripcion.set_size_request(100,30);
	hBoxDescripcion.pack_start(m_labelDescripcion);
	m_ingresarDescripcion.set_size_request(680,30);
	m_ingresarDescripcion.set_text(descripcion);
	hBoxDescripcion.pack_end(m_ingresarDescripcion);
	m_vBoxPrincipal.pack_start(hBoxDescripcion);

	m_labelIcono.set_text("ICONO");
	m_vBoxPrincipal.pack_start(m_labelIcono);

	std::stringstream ssRutaIconoPpal;
	ssRutaIconoPpal << RUTA_CARPETA_TEMP << idIcono << ".jpg";
	m_ImagenIconoPPAL.set(ssRutaIconoPpal.str());
	Glib::RefPtr<Gdk::Pixbuf> scaled1 = m_ImagenIconoPPAL.get_pixbuf()->scale_simple(200,200,Gdk::INTERP_BILINEAR);
	m_ImagenIconoPPAL.set(scaled1);
	m_botonFileChooserImgPPAL.set_filename(ssRutaIconoPpal.str());

	m_botoneraImgPPAL.set_size_request(900,200);
	m_botoneraImgPPAL.pack_start(m_ImagenIconoPPAL);
	m_botonFileChooserImgPPAL.set_size_request(200,30);
	m_botoneraFileChooser.set_layout(Gtk::BUTTONBOX_CENTER);
	m_botoneraFileChooser.pack_end(m_botonFileChooserImgPPAL);
	m_botoneraImgPPAL.pack_end(m_botoneraFileChooser);
	m_botoneraImgPPAL.set_layout(Gtk::BUTTONBOX_CENTER);
	m_vBoxPrincipal.pack_start(m_botoneraImgPPAL);

	m_labelImagen.set_text("IMAGENES");
	m_botoneraImagenAgregar.pack_start(m_labelImagen);
	m_botonAgregarImagen.set_label("Agregar");
	m_botoneraImagenAgregar.pack_end(m_botonAgregarImagen);
	m_botoneraImagenAgregar.set_layout(Gtk::BUTTONBOX_START);
	m_vBoxPrincipal.pack_start(m_botoneraImagenAgregar);

	m_viewPortImagenes = new Gtk::Viewport(*m_scrolledWImagenes.get_hadjustment(),*m_scrolledWImagenes.get_vadjustment());
	m_scrolledWImagenes.add(*m_viewPortImagenes);
	m_scrolledWImagenes.set_size_request(Gtk::EXPAND,150);
	m_viewPortImagenes->add(m_botoneraImagenes);
	m_botoneraImagenes.set_layout(Gtk::BUTTONBOX_START);
	m_vBoxPrincipal.pack_start(m_scrolledWImagenes);

	for(std::list<unsigned long int>::iterator it = idsImagenes.begin() ; it != idsImagenes.end() ; ++it)
	{
		Gtk::Image *imagen = new Gtk::Image;
		std::string sfiledir;
		Gtk::Button *botonEliminar = new Gtk::Button;
		Gtk::VBox *vButtonBox = new Gtk::VBox;
		vButtonBox->set_size_request(150,150);
		vButtonBox->pack_start(*imagen);
		vButtonBox->pack_end(*botonEliminar);
		std::stringstream ssRutaImagen;
		ssRutaImagen << RUTA_CARPETA_TEMP << (*it) << ".jpg";
		sfiledir = ssRutaImagen.str();
		imagen->set(sfiledir);
		Glib::RefPtr<Gdk::Pixbuf> scaled1 = imagen->get_pixbuf()->scale_simple(135,135,Gdk::INTERP_BILINEAR);
		imagen->set(scaled1);
		ControlEP *controlador = new ControlEP(vButtonBox,(*it),this);
		botonEliminar->signal_clicked().connect( sigc::mem_fun(*controlador, &ControlEP::on_button_eliminarIconoConID));
		botonEliminar->set_label("Eliminar");
		this->controladores.push_back(controlador);
		this->m_listabotonEliminarImagenes.push_back(vButtonBox);
		this->m_refButtondelete.push_back(botonEliminar);
		this->m_refImagenesdelete.push_back(imagen);
		m_botoneraImagenes.pack_end(*vButtonBox);
	}
	m_OKButton.set_label("OK");
	m_OKButton.set_size_request(200,50);
	m_CANCELButton.set_label("CANCEL");
	m_CANCELButton.set_size_request(200,50);
	m_botoneraCANCELOK.pack_start(m_OKButton);
	m_botoneraCANCELOK.pack_end(m_CANCELButton);
	m_botoneraCANCELOK.set_layout(Gtk::BUTTONBOX_SPREAD);
	m_vBoxPrincipal.pack_end(m_botoneraCANCELOK);

	m_botonFileChooserImgPPAL.signal_selection_changed().connect( sigc::mem_fun(*this, &VistaEditarProducto::on_button_actualizarIcono));
	m_botonAgregarImagen.signal_clicked().connect( sigc::mem_fun(*this, &VistaEditarProducto::on_button_agregarImagen));
	m_OKButton.signal_clicked().connect( sigc::mem_fun(*this, &VistaEditarProducto::on_button_editarOK) );
	m_CANCELButton.signal_clicked().connect( sigc::mem_fun(*this, &VistaEditarProducto::on_button_editarCANCEL) );

	this->add(m_vBoxPrincipal);

	this->show_all();
}

VistaEditarProducto::~VistaEditarProducto() {
	std::list<ControlEP*>::iterator it = controladores.begin();
	for(; it != controladores.end(); ++it)
		delete(*it);

	if(m_viewPortImagenes)
		delete m_viewPortImagenes;

	std::list<Gtk::Image*>::iterator itIm = m_refImagenesdelete.begin();
	for(; itIm != m_refImagenesdelete.end(); ++itIm){
		delete (*itIm);
	}
	std::list<Gtk::Button*>::iterator itBu = m_refButtondelete.begin();
	for(; itBu != m_refButtondelete.end(); ++itBu){
		delete (*itBu);
	}
}

void VistaEditarProducto::on_button_actualizarIcono(){
	std::string filename = m_botonFileChooserImgPPAL.get_filename();
	m_ImagenIconoPPAL.set(filename);
	Glib::RefPtr<Gdk::Pixbuf> scaled1 = m_ImagenIconoPPAL.get_pixbuf()->scale_simple(200,200,Gdk::INTERP_BILINEAR);
	m_ImagenIconoPPAL.set(scaled1);
}

void VistaEditarProducto::on_button_agregarImagen(){
		Gtk::FileChooserDialog dialog("Seleccione imagen para el Producto",
													Gtk::FILE_CHOOSER_ACTION_OPEN);
		dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
		dialog.add_button(Gtk::Stock::OPEN, Gtk::RESPONSE_OK);

		Gtk::FileFilter filter_any;
		filter_any.set_name("Cualquier Archivo");
		filter_any.add_pattern("*");
		dialog.add_filter(filter_any);

		int result = dialog.run();
		if (result == Gtk::RESPONSE_OK)
		{
			Gtk::Image *imagen = new Gtk::Image;
			std::string *sfiledir = new std::string;
			Gtk::Button *botonEliminar = new Gtk::Button;
			Gtk::VBox *vButtonBox = new Gtk::VBox;
			vButtonBox->set_size_request(150,150);
			vButtonBox->pack_start(*imagen);
			vButtonBox->pack_end(*botonEliminar);
			*sfiledir = dialog.get_filename();
			imagen->set(*sfiledir);
			Glib::RefPtr<Gdk::Pixbuf> scaled1 = imagen->get_pixbuf()->scale_simple(135,135,Gdk::INTERP_BILINEAR);
			imagen->set(scaled1);
			ControlEP *controlador = new ControlEP(vButtonBox,sfiledir,this);
			botonEliminar->signal_clicked().connect( sigc::mem_fun(*controlador, &ControlEP::on_button_eliminarIconoConFileDir));
			botonEliminar->set_label("Eliminar");
			this->controladores.push_back(controlador);
			this->m_listabotonEliminarImagenes.push_back(vButtonBox);
			this->m_rutaImagenes.push_back(sfiledir);
			this->m_refButtondelete.push_back(botonEliminar);
			this->m_refImagenesdelete.push_back(imagen);
			m_botoneraImagenes.pack_end(*vButtonBox);
			this->show_all();
		}
}

void VistaEditarProducto::eliminarIconoPertenecienteABotonFileDir(Gtk::VBox *vbbox,std::string *sfiledir){
	std::list<Gtk::VBox*>::iterator it = m_listabotonEliminarImagenes.begin();
	std::list<std::string*>::iterator itRutasImagenes = m_rutaImagenes.begin() ;
	for (; it!=m_listabotonEliminarImagenes.end(); ++it){
		if((*it) == vbbox)
		{
			delete (*it);
			break;
		}
	}
	for (; itRutasImagenes != m_rutaImagenes.end(); ++itRutasImagenes){
		if((*itRutasImagenes) == sfiledir)
		{
			delete (*itRutasImagenes);
			break;
		}
	}
	m_listabotonEliminarImagenes.erase(std::remove(m_listabotonEliminarImagenes.begin(), m_listabotonEliminarImagenes.end(), vbbox), m_listabotonEliminarImagenes.end());
	m_rutaImagenes.erase(std::remove(m_rutaImagenes.begin(), m_rutaImagenes.end(), sfiledir), m_rutaImagenes.end());
}

void VistaEditarProducto::eliminarIconoPertenecienteABotonID(Gtk::VBox *vbbox,unsigned long int id){
	std::list<Gtk::VBox*>::iterator it = m_listabotonEliminarImagenes.begin();
	std::list<std::string*>::iterator itRutasImagenes = m_rutaImagenes.begin();
	for (; it!=m_listabotonEliminarImagenes.end(); ++it,++itRutasImagenes){
		if((*it) == vbbox)
		{
			delete (*it);
			m_listabotonEliminarImagenes.erase(it);
			break;
		}
	}
	m_listabotonEliminarImagenes.erase(std::remove(m_listabotonEliminarImagenes.begin(), m_listabotonEliminarImagenes.end(), vbbox), m_listabotonEliminarImagenes.end());
	m_idsImagenes.remove(id);
}

void VistaEditarProducto::on_button_editarOK(){
	if (m_ingresarNombre.get_text() == ""){
			Gtk::Window *ventanitaError = new Gtk::Window;
			Gtk::MessageDialog dialog(*ventanitaError,"Ingrese nombre",false, Gtk::MESSAGE_ERROR);
			dialog.set_title("Error al Agregar Producto");
			dialog.set_size_request(350,100);
			dialog.run();
			return;
	}

	std::string nombreProducto = m_ingresarNombre.get_text();
	std::string descProducto = m_ingresarDescripcion.get_text();
	std::string rutaImagenIcono = m_botonFileChooserImgPPAL.get_filename();

	std::list<std::string*>::iterator it = m_rutaImagenes.begin();
	std::cerr << "Ruta a agregrar de imagenes"<< std::endl;
	for (; it!=m_rutaImagenes.end() ; ++it){
		std::cerr << *(*it)<< std::endl;
	}

	std::cerr << "Id producto modificar: " << m_idProducto << std::endl;
	std::cerr << "Nombre: " << nombreProducto << std::endl;
	std::cerr << "Descripcion: " << descProducto << std::endl;
	std::cerr << "ruta Imagen Icono: " << rutaImagenIcono << std::endl;

	this->modelo->modificarProducto(m_idProducto,nombreProducto,descProducto,rutaImagenIcono,m_idsImagenes,m_rutaImagenes);

	Gtk::Window *ventanitaOK = new Gtk::Window;
	Gtk::MessageDialog dialog(*ventanitaOK,"Producto modificado correctamente!",false, Gtk::MESSAGE_INFO);
	dialog.set_title("Operacion Exitosa");
	dialog.set_size_request(350,100);
	dialog.run();
	modelo->notify();
	delete this;
}

void VistaEditarProducto::on_button_editarCANCEL(){
	delete this;
}
