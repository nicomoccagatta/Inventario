/*
 * VistaAgregarProducto.cpp
 *
 *  Created on: 21/6/2015
 *      Author: nicomoccagatta
 */

#include "VistaAgregarProducto.h"

VistaAgregarProducto::VistaAgregarProducto() {
	m_labelNombre.set_text("Nombre Producto:(*)");
	m_labelNombre.set_size_request(Gtk::SHRINK,20);
	hBoxNombre.pack_start(m_labelNombre);
	m_ingresarNombre.set_size_request(500,40);
	hBoxNombre.pack_end(m_ingresarNombre);
	vBoxPrincipal.pack_start(hBoxNombre);

	m_labelDescripcion.set_text("Descripcion:");
	m_labelDescripcion.set_size_request(Gtk::SHRINK,20);
	hBoxDescripcion.pack_start(m_labelDescripcion);
	m_ingresarDescripcion.set_size_request(500,40);
	hBoxDescripcion.pack_end(m_ingresarDescripcion);
	vBoxPrincipal.pack_start(hBoxDescripcion);

	m_labelAreaVision.set_text("Area de Vision(*)");
	hBoxAreaVision.pack_start(m_labelAreaVision);
	m_AreasDeVision.pack_start(columnas.getColumnaTexto());
	hBoxAreaVision.pack_end(m_AreasDeVision);
	vBoxPrincipal.pack_start(hBoxAreaVision);

	m_calendario.signal_day_selected().connect( sigc::mem_fun(*this, &VistaAgregarProducto::on_cambio_dia_calendario));
	m_calendario.get_date(m_fechaAnterior);
	hBoxStock.pack_start(m_calendario);
	m_labelCantidad.set_text("Cantidad");
	m_botoneraStock.pack_start(m_labelCantidad);
	m_ingresarCantidad.set_size_request(15,30);
	m_botoneraStock.pack_end(m_ingresarCantidad);
	m_botoneraStock.set_layout(Gtk::BUTTONBOX_CENTER);
	hBoxStock.pack_end(m_botoneraStock);
	vBoxPrincipal.pack_start(hBoxStock);

	m_ImagenIconoPPAL.signal_clicked().connect( sigc::mem_fun(*this, &VistaAgregarProducto::on_button_ImagenPPAL));
	m_botoneraImgPPAL.pack_start(m_ImagenIconoPPAL);
	hBoxImagenes.pack_start(m_botoneraImgPPAL);
	hBoxImagenes.pack_start(m_botoneraImagenes);
	hBoxImagenes.pack_end(m_botoneraIconosSecundarios);
	m_AgregarIconosSecundarios.set_label("Agregar Imagen");
	m_botoneraIconosSecundarios.pack_end(m_AgregarIconosSecundarios);
	vBoxPrincipal.pack_start(hBoxImagenes);

	m_AgregarProducto.set_label("Agregar Producto");
	vBoxPrincipal.pack_end(m_AgregarProducto);

	m_AgregarIconosSecundarios.signal_clicked().connect( sigc::mem_fun(*this, &VistaAgregarProducto::on_button_agregarIcono));
	m_AgregarProducto.signal_clicked().connect( sigc::mem_fun(*this, &VistaAgregarProducto::on_button_agregarProducto) );
}

VistaAgregarProducto::~VistaAgregarProducto() {
	std::list<ControlAP*>::iterator it = controladores.begin();
	for(; it != controladores.end(); ++it)
		delete(*it);
}


void VistaAgregarProducto::update(){
}

void VistaAgregarProducto::run(Gtk::Viewport *panelDinamico,Modelo_Observable *modelo){
	this->modelo = modelo;
	this->panelDinam = panelDinamico;

	std::list<common::Stock*>::iterator it = stockProducto.begin();
	for (;it != stockProducto.end(); ++it){
		delete (*it);
	}
	stockProducto.clear();

	modeloComboBox = Gtk::ListStore::create(columnas);
	m_AreasDeVision.set_model(modeloComboBox);
	this->update_lista_av();

	m_ingresarNombre.set_text("");
	m_ingresarDescripcion.set_text("");
	m_ingresarCantidad.set_text("");
	this->borrarIconosAnteriores();
	panelDinam->add(vBoxPrincipal);

	m_ImagenBotonIconoPPAL.set("imagenes/imagen_vacia.png");
	m_ImagenSeteada=false;
	m_rutaImagenPPAL = "";
	m_ImagenIconoPPAL.set_image(m_ImagenBotonIconoPPAL);
	Glib::RefPtr<Gdk::Pixbuf> scaled1 = m_ImagenBotonIconoPPAL.get_pixbuf()->scale_simple(200,200,Gdk::INTERP_BILINEAR);
	m_ImagenBotonIconoPPAL.set(scaled1);
}

void VistaAgregarProducto::on_button_ImagenPPAL(){
	  Gtk::FileChooserDialog dialog("Seleccione el Icono del Producto",
	          Gtk::FILE_CHOOSER_ACTION_OPEN);
	  dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
	  dialog.add_button(Gtk::Stock::OPEN, Gtk::RESPONSE_OK);

	  Gtk::FileFilter filter_any;
	  filter_any.set_name("Cualquier Archivo");
	  filter_any.add_pattern("*");
	  dialog.add_filter(filter_any);

	  int result = dialog.run();

	  switch(result)
	  {
	    case(Gtk::RESPONSE_OK):
	    {
	      std::string filename = dialog.get_filename();
	      m_ImagenBotonIconoPPAL.set(filename);
	      m_ImagenIconoPPAL.set_image(m_ImagenBotonIconoPPAL);
	      m_rutaImagenPPAL = filename;
	      Glib::RefPtr<Gdk::Pixbuf> scaled1 = m_ImagenBotonIconoPPAL.get_pixbuf()->scale_simple(200,200,Gdk::INTERP_BILINEAR);
	      m_ImagenBotonIconoPPAL.set(scaled1);
	      m_ImagenSeteada=true;
	      break;
	    }
	    case(Gtk::RESPONSE_CANCEL):
	    {
	      std::cout << "Cancel clicked." << std::endl;
	      break;
	    }
	    default:
	    {
	      std::cout << "Unexpected button clicked." << std::endl;
	      break;
	    }
	  }
}

void VistaAgregarProducto::on_button_agregarIcono(){
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

		switch(result)
		{
			case(Gtk::RESPONSE_OK):
	    	{
				std::string filename = dialog.get_filename();
				Gtk::Image *imagen = new Gtk::Image;
				m_rutaImagenesIconos.push_back(filename);
				imagen->set(filename);
				Gtk::Button *boton = new Gtk::Button;
				ControlAP *controlador = new ControlAP(boton,this);
				boton->signal_clicked().connect( sigc::mem_fun(*controlador, &ControlAP::on_button_eliminarIcono));
				boton->set_image(*imagen);
				Glib::RefPtr<Gdk::Pixbuf> scaled1 = imagen->get_pixbuf()->scale_simple(100,100,Gdk::INTERP_BILINEAR);
				imagen->set(scaled1);
				this->controladores.push_back(controlador);
				this->m_ImagenIconosSecundarios.push_back(boton);
				m_botoneraImagenes.pack_start(*boton);
				panelDinam->remove();
				panelDinam->add(vBoxPrincipal);
				panelDinam->show_all();
				break;
	    	}
			default:
			{
				break;
			}
		}
	}else{
		Gtk::Window *ventanitaError = new Gtk::Window;
		Gtk::MessageDialog dialog(*ventanitaError,"Ingrese Icono Principal Primero",false, Gtk::MESSAGE_ERROR);
		dialog.set_title("Error");
		dialog.set_size_request(350,100);
		dialog.run();
	}
}

void VistaAgregarProducto::eliminarIconoPertenecienteABoton(Gtk::Button *boton){
	std::list<Gtk::Button*>::iterator it = m_ImagenIconosSecundarios.begin();
	std::list<std::string>::iterator itRutasImagenes = m_rutaImagenesIconos.begin();
	for (; it!=m_ImagenIconosSecundarios.end(); ++it){
		itRutasImagenes++;
		if((*it) == boton)
		{
			delete ((*it)->get_image());
			delete (*it);
			m_ImagenIconosSecundarios.erase(it);
			m_rutaImagenesIconos.erase(itRutasImagenes);
			break;
		}
	}
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
	if( m_AreasDeVision.get_active_row_number() == (-1) ){
			Gtk::Window *ventanitaError = new Gtk::Window;
			Gtk::MessageDialog dialog(*ventanitaError,"Seleccione Area de Vision",false, Gtk::MESSAGE_ERROR);
			dialog.set_title("Error en Area de Vision");
			dialog.set_size_request(350,100);
			dialog.run();
			return;
	}
	/*
	char* pchEnd = 0;
	int cantidad = strtol(m_ingresarCantidad.get_text().c_str(), &pchEnd, 10);
	if (((cantidad < 0) || (m_ingresarCantidad.get_text() == "")) && (stockProducto.size()==0)){
			Gtk::Window *ventanitaError = new Gtk::Window;
			Gtk::MessageDialog dialog(*ventanitaError,"Cantidad ingresada incorrecta",false, Gtk::MESSAGE_ERROR);
			dialog.set_title("Error al Ingresar Cantidad");
			dialog.set_size_request(350,100);
			dialog.run();
			return;
	}
	*/
	if (!m_ImagenSeteada){
		Gtk::Window *ventanitaError = new Gtk::Window;
		Gtk::MessageDialog dialog(*ventanitaError,"Ingrese Icono de Producto!",false, Gtk::MESSAGE_ERROR);
		dialog.set_title("Error Icono Principal");
		dialog.set_size_request(350,100);
		dialog.run();
		return;
	}

	Gtk::TreeModel::Row fila = *m_AreasDeVision.get_active();
	AreaDeVision* area = fila[columnas.getColumnaValor()];

	/*
	m_calendario.get_date(m_fechaAnterior);
	std::list<common::Stock*>::iterator it = stockProducto.begin();
	std::string sfecha;
		std::stringstream day;
		day<< (int) m_fechaAnterior.get_day();
		sfecha = day.str();
		sfecha += "/";
		std::stringstream month;
		month << (int)m_fechaAnterior.get_month();
		sfecha += month.str();
		sfecha += "/" ;
		std::stringstream year;
		year << (int)m_fechaAnterior.get_year();
		sfecha += year.str();

	bool fechaGuardada=false;
	for(; it != stockProducto.end() ; ++it){
		if ((*it)->getFecha() == sfecha)
			fechaGuardada=true;
	}
	if (!fechaGuardada){
		common::Stock *stock = new common::Stock(cantidad,sfecha);
		stockProducto.push_back(stock);
	}
	*/

	std::string nombreProducto = m_ingresarNombre.get_text();
	std::string descProducto = m_ingresarDescripcion.get_text();
	this->modelo->altaProducto(nombreProducto,descProducto,area->getId(),m_rutaImagenPPAL,m_rutaImagenesIconos);

	Gtk::Window *ventanitaOK = new Gtk::Window;
	Gtk::MessageDialog dialog(*ventanitaOK,"Producto agregado correctamente!",false, Gtk::MESSAGE_INFO);
	dialog.set_title("Operacion Exitosa");
	dialog.set_size_request(350,100);
	dialog.run();

	panelDinam->remove();
	modelo->actualizarAreasDeVision();
	this->run(panelDinam,modelo);
}

void VistaAgregarProducto::on_cambio_dia_calendario(){
	char* pchEnd = 0;
		int cantidad = strtol(m_ingresarCantidad.get_text().c_str(), &pchEnd, 10);
		std::string fecha;
		if ((cantidad >= 0) && (m_ingresarCantidad.get_text() != "")){
			std::stringstream day;
			day<< (int) m_fechaAnterior.get_day();
			fecha = day.str();
			fecha += "/";
			std::stringstream month;
			month << (int)m_fechaAnterior.get_month();
			fecha += month.str();
			fecha += "/" ;
			std::stringstream year;
			year << (int)m_fechaAnterior.get_year();
			fecha += year.str();

			std::list<common::Stock*>::iterator it = stockProducto.begin();
			bool encontroProducto=false;
			for (;it != stockProducto.end(); ++it){
				if ((*it)->getFecha() == fecha){
					encontroProducto=true;
				}
			}
			if (!encontroProducto){
				common::Stock *stock = new common::Stock (cantidad,fecha);
				stockProducto.push_back(stock);
			}
		}
		m_calendario.get_date(m_fechaAnterior);
		this->comprobarsiFechaEstaEnStock(m_fechaAnterior,m_ingresarCantidad);
}

void VistaAgregarProducto::comprobarsiFechaEstaEnStock(Glib::Date &fecha,Gtk::Entry &entryCantidad){
	std::string sfecha;
	std::stringstream day;
	day<< (int) fecha.get_day();
	sfecha = day.str();
	sfecha += "/";
	std::stringstream month;
	month << (int)fecha.get_month();
	sfecha += month.str();
	sfecha += "/" ;
	std::stringstream year;
	year << (int)fecha.get_year();
	sfecha += year.str();
	std::list<common::Stock*>::iterator it = stockProducto.begin();
	bool encontroProducto=false;
	for (;it != stockProducto.end(); ++it){
		if ((*it)->getFecha() == sfecha){
			std::stringstream cantidad;
			cantidad<< (*it)->getCantidad();
			entryCantidad.set_text(cantidad.str());
			encontroProducto=true;
			break;
		}
	}
	if (!encontroProducto)
		entryCantidad.set_text("");
}

void VistaAgregarProducto::borrarIconosAnteriores(){
	std::list<Gtk::Button*>::iterator it;
	for (it=m_ImagenIconosSecundarios.begin(); it!=m_ImagenIconosSecundarios.end(); ++it){
		delete ((*it)->get_image());
		delete (*it);
		m_rutaImagenesIconos.clear();
	}
	m_ImagenIconosSecundarios.clear();
}

void VistaAgregarProducto::update_lista_av(){
	const std::list<AreaDeVision*>* areas = modelo->getAreasDeVision();

	std::list<AreaDeVision*>::const_iterator it;
	for (it = areas->begin(); it!= areas->end(); ++it){
		Gtk::TreeModel::Row fila = *(modeloComboBox->append());
		fila[columnas.getColumnaValor()] = *it;
		fila[columnas.getColumnaTexto()] = (*it)->getUbicacion();
	}
}
