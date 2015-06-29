/*
 * VistaStockHistorico.cpp
 *
 *  Created on: 28/6/2015
 *      Author: nicomoccagatta
 */

#include "VistaStockHistorico.h"

VistaStockHistorico::VistaStockHistorico() {
	m_ProductosTreeView.append_column("Icono", m_ProductosList.m_Columns.m_col_imagenIcono);
	m_ProductosTreeView.append_column("Nombre", m_ProductosList.m_Columns.m_col_nombre);
	m_ProductosTreeView.set_search_column(1);
	m_ProductosList.add(m_ProductosTreeView);
	m_ProductosList.set_size_request(430,300);
	m_vBoxPrincipalGrilla.pack_start(m_ProductosList);

	m_labelDesde.set_text("\tDesde\t");
	m_labelDesde.set_size_request(100,50);
	m_botoneraFechaDesde.pack_start(m_labelDesde);
	m_activarCalendarioDesde.signal_clicked().connect( sigc::mem_fun(*this, &VistaStockHistorico::on_check_button_desde));
	b_calendarioDesdeSeteado = false;
	m_activarCalendarioDesde.set_size_request(80,50);
	m_botoneraFechaDesde.pack_start(m_activarCalendarioDesde);
	m_botoneraFechaDesde.set_size_request(180,150);
	m_botoneraFechaDesde.set_layout(Gtk::BUTTONBOX_START);
	m_horizontalBoxButoneraDesde.pack_start(m_botoneraFechaDesde);
	m_vBoxPrincipalGrilla.pack_start(m_horizontalBoxButoneraDesde);

	m_labelHasta.set_text("\tHasta\t");
	m_labelHasta.set_size_request(100,50);
	m_botoneraFechaHasta.pack_start(m_labelHasta);
	m_activarCalendarioHasta.signal_clicked().connect( sigc::mem_fun(*this, &VistaStockHistorico::on_check_button_hasta));
	b_calendarioHastaSeteado = false;
	m_activarCalendarioHasta.set_size_request(80,50);
	m_botoneraFechaHasta.pack_start(m_activarCalendarioHasta);
	m_botoneraFechaHasta.set_size_request(180,150);
	m_botoneraFechaHasta.set_layout(Gtk::BUTTONBOX_START);
	m_horizontalBoxButoneraHasta.pack_start(m_botoneraFechaHasta);
	m_vBoxPrincipalGrilla.pack_start(m_horizontalBoxButoneraHasta);

	m_HBoxGrillaEImagen.pack_start(m_vBoxPrincipalGrilla);
	m_HBoxGrillaEImagen.pack_end(m_ImagenItem);
}

VistaStockHistorico::~VistaStockHistorico() {
	if (b_calendarioDesdeSeteado)
		delete m_calendarioDesde;
	if (b_calendarioHastaSeteado)
		delete m_calendarioHasta;
}

void VistaStockHistorico::update(){
	std::cerr << "UPDATE VISTA STOCK HISTORICO.." << std::endl;
	m_refProductosListStore = Gtk::ListStore::create(m_ProductosList.m_Columns);
	m_ProductosTreeView.set_model(m_refProductosListStore);
	this->update_lista_productos();
}

void VistaStockHistorico::run(Gtk::Viewport *panelDinamico,Modelo_Observable *modelo){
	this->modelo = modelo;
	this->panelDinam = panelDinamico;

	this->update_lista_productos();

	panelDinam->add(m_HBoxGrillaEImagen);
}

void VistaStockHistorico::on_check_button_desde() {
	if (b_calendarioDesdeSeteado){
		delete m_calendarioDesde;
		b_calendarioDesdeSeteado = false;
	}else{
		m_calendarioDesde = new Gtk::Calendar;
		b_calendarioDesdeSeteado = true;
		m_calendarioDesde->set_property("show_day_names",false);
		m_calendarioDesde->set_size_request(250,150);
		m_horizontalBoxButoneraDesde.pack_end(*m_calendarioDesde);
		panelDinam->show_all();
	}
}

void VistaStockHistorico::on_check_button_hasta() {
	if (b_calendarioHastaSeteado){
		delete m_calendarioHasta;
		b_calendarioHastaSeteado = false;
	}else{
		m_calendarioHasta = new Gtk::Calendar;
		b_calendarioHastaSeteado = true;
		m_calendarioHasta->set_property("show_day_names",false);
		m_calendarioHasta->set_size_request(250,150);
		m_horizontalBoxButoneraHasta.pack_end(*m_calendarioHasta);
		panelDinam->show_all();
	}
}

void VistaStockHistorico::update_lista_productos(){
	m_refProductosListStore = Gtk::ListStore::create(m_ProductosList.m_Columns);
	m_ProductosTreeView.set_model(m_refProductosListStore);

	const std::list<Producto*>* prods = modelo->getProductos();
	std::list<Producto*>::const_iterator it;
	for (it=prods->begin(); it!=prods->end();++it){
	Gtk::TreeModel::Row row = *(m_refProductosListStore->append());
	std::string rutaImagen = modelo->getImagenConID((*it)->getIdIcono());
	Glib::RefPtr<Gdk::Pixbuf>  pic = Gdk::Pixbuf::create_from_file(rutaImagen,30,30,false);
	row[m_ProductosList.m_Columns.m_col_imagenIcono] = pic;
	row[m_ProductosList.m_Columns.m_col_nombre] = (*it)->getNombre();
	row[m_ProductosList.m_Columns.m_col_data] = *it;
	}
}
