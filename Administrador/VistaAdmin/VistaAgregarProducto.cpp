#include "VistaAgregarProducto.h"

VistaAgregarProducto::VistaAgregarProducto(Modelo_Observable *model) : modelo(model) {
	this->set_size_request(900,700);
	this->set_title("Agregar Producto");
	this->set_position(Gtk::WIN_POS_CENTER);
	this->set_resizable(false);

	m_labelNombre.set_text("Nombre");
	m_labelNombre.set_size_request(100,30);
	hBoxNombre.pack_start(m_labelNombre);
	m_ingresarNombre.set_size_request(680,30);
	hBoxNombre.pack_end(m_ingresarNombre);
	m_vBoxPrincipal.pack_start(hBoxNombre);

	m_labelDescripcion.set_text("Descripcion");
	m_labelDescripcion.set_size_request(100,30);
	hBoxDescripcion.pack_start(m_labelDescripcion);
	m_ingresarDescripcion.set_size_request(680,30);
	hBoxDescripcion.pack_end(m_ingresarDescripcion);
	m_vBoxPrincipal.pack_start(hBoxDescripcion);

	m_labelIcono.set_text("ICONO");
	m_vBoxPrincipal.pack_start(m_labelIcono);

	m_ImagenIconoPPAL.set(RUTA_IMAGEN_DEFECTO);
	Glib::RefPtr<Gdk::Pixbuf> scaled1 = m_ImagenIconoPPAL.get_pixbuf()->scale_simple(200,200,Gdk::INTERP_BILINEAR);
	m_ImagenIconoPPAL.set(scaled1);
	m_ImagenSeteada = false;

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

	m_AgregarProducto.set_label("Agregar Producto");
	m_AgregarProducto.set_size_request(880,40);
	m_butoneraAgregarBoton.pack_start(m_AgregarProducto);
	m_butoneraAgregarBoton.set_layout(Gtk::BUTTONBOX_CENTER);
	m_vBoxPrincipal.pack_end(m_butoneraAgregarBoton);

	m_botonFileChooserImgPPAL.signal_selection_changed().connect( sigc::mem_fun(*this, &VistaAgregarProducto::on_button_actualizarIcono));
	m_botonAgregarImagen.signal_clicked().connect( sigc::mem_fun(*this, &VistaAgregarProducto::on_button_agregarImagen));
	m_AgregarProducto.signal_clicked().connect( sigc::mem_fun(*this, &VistaAgregarProducto::on_button_agregarProducto) );

	this->add(m_vBoxPrincipal);

	this->show_all();
}

VistaAgregarProducto::~VistaAgregarProducto() {
	std::list<ControlAP*>::iterator it = controladores.begin();
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

void VistaAgregarProducto::on_button_actualizarIcono(){
	std::string filename = m_botonFileChooserImgPPAL.get_filename();
	m_ImagenIconoPPAL.set(filename);
	Glib::RefPtr<Gdk::Pixbuf> scaled1 = m_ImagenIconoPPAL.get_pixbuf()->scale_simple(200,200,Gdk::INTERP_BILINEAR);
	m_ImagenIconoPPAL.set(scaled1);
	m_ImagenSeteada=true;
}

void VistaAgregarProducto::on_button_agregarImagen(){
	if(m_ImagenSeteada == true){
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
			m_rutaImagenesIconos.push_back(sfiledir);
			imagen->set(*sfiledir);
			Glib::RefPtr<Gdk::Pixbuf> scaled1 = imagen->get_pixbuf()->scale_simple(135,135,Gdk::INTERP_BILINEAR);
			imagen->set(scaled1);
			ControlAP *controlador = new ControlAP(vButtonBox,sfiledir,this);
			botonEliminar->signal_clicked().connect( sigc::mem_fun(*controlador, &ControlAP::on_button_eliminarIcono));
			botonEliminar->set_label("Eliminar");
			this->controladores.push_back(controlador);
			this->m_listabotonEliminarImagenes.push_back(vButtonBox);
			this->m_refButtondelete.push_back(botonEliminar);
			this->m_refImagenesdelete.push_back(imagen);
			m_botoneraImagenes.pack_end(*vButtonBox);
			this->show_all();
		}
	}else{
		Gtk::Window *ventanitaError = new Gtk::Window;
		Gtk::MessageDialog dialog(*ventanitaError,"Ingrese Icono Principal Primero",false, Gtk::MESSAGE_ERROR);
		dialog.set_title("Error");
		dialog.set_size_request(350,100);
		dialog.run();
	}
}

void VistaAgregarProducto::eliminarIconoPertenecienteABoton(Gtk::VBox *vbbox,std::string *sfiledir){
	std::list<Gtk::VBox*>::iterator it = m_listabotonEliminarImagenes.begin();
	std::list<std::string*>::iterator itRutasImagenes = m_rutaImagenesIconos.begin();
	for (; it!=m_listabotonEliminarImagenes.end(); ++it,++itRutasImagenes){
		if((*it) == vbbox)
		{
			delete (*it);
			delete (*itRutasImagenes);
			break;
		}
	}
	m_listabotonEliminarImagenes.erase(std::remove(m_listabotonEliminarImagenes.begin(), m_listabotonEliminarImagenes.end(), vbbox), m_listabotonEliminarImagenes.end());
	m_rutaImagenesIconos.erase(std::remove(m_rutaImagenesIconos.begin(), m_rutaImagenesIconos.end(), sfiledir), m_rutaImagenesIconos.end());
}

void VistaAgregarProducto::on_button_agregarProducto(){
	if (m_ingresarNombre.get_text() == ""){
			Gtk::Window *ventanitaError = new Gtk::Window;
			Gtk::MessageDialog dialog(*ventanitaError,"Ingrese nombre",false, Gtk::MESSAGE_ERROR);
			dialog.set_title("Error al Agregar Producto");
			dialog.set_size_request(350,100);
			dialog.run();
			return;
	}
	if (!m_ImagenSeteada){
		Gtk::Window *ventanitaError = new Gtk::Window;
		Gtk::MessageDialog dialog(*ventanitaError,"Ingrese Icono de Producto!",false, Gtk::MESSAGE_ERROR);
		dialog.set_title("Error Icono Principal");
		dialog.set_size_request(350,100);
		dialog.run();
		return;
	}

	std::string nombreProducto = m_ingresarNombre.get_text();
	std::string descProducto = m_ingresarDescripcion.get_text();
	std::string rutaImagenIcono = m_botonFileChooserImgPPAL.get_filename();

	std::list<std::string*>::iterator it = m_rutaImagenesIconos.begin();
	std::cerr << "Ruta a agregrar de imagenes"<< std::endl;
	for (; it!=m_rutaImagenesIconos.end() ; ++it){
		std::cerr << *(*it)<< std::endl;
	}

	this->modelo->altaProducto(nombreProducto,descProducto,rutaImagenIcono,m_rutaImagenesIconos);

	Gtk::Window *ventanitaOK = new Gtk::Window;
	Gtk::MessageDialog dialog(*ventanitaOK,"Producto agregado correctamente!",false, Gtk::MESSAGE_INFO);
	dialog.set_title("Operacion Exitosa");
	dialog.set_size_request(350,100);
	dialog.run();
	modelo->notify();
	delete this;
}
