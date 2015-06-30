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
	m_ProductosList.set_size_request(430,250);
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
	m_ImagenItem.set_size_request(750,Gtk::EXPAND);

	refTreeSelection = m_ProductosTreeView.get_selection();
	refTreeSelection->signal_changed().connect(
	    sigc::mem_fun(*this, &VistaStockHistorico::on_producto_seleccionado) );
}

VistaStockHistorico::~VistaStockHistorico() {
	if (m_activarCalendarioHasta.get_active())
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
	if (!m_activarCalendarioDesde.get_active()){
		delete m_calendarioDesde;
	}else{
		m_calendarioDesde = new Gtk::Calendar;
		m_calendarioDesde->set_property("show_day_names",false);
		m_calendarioDesde->set_size_request(250,150);
		m_horizontalBoxButoneraDesde.pack_end(*m_calendarioDesde);
		panelDinam->show_all();
	}
}

void VistaStockHistorico::on_check_button_hasta() {
	if (!m_activarCalendarioHasta.get_active()){
		delete m_calendarioHasta;
	}else{
		m_calendarioHasta = new Gtk::Calendar;
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
	row[m_ProductosList.m_Columns.m_col_id] = (*it)->getId();
	row[m_ProductosList.m_Columns.m_col_data] = *it;
	}
}

void VistaStockHistorico::on_producto_seleccionado(){
	Glib::Date d_fechaDesde,d_fechaHasta;
	bool b_fechaDesde = false;
	bool b_fechaHasta = false;
	if (m_activarCalendarioDesde.get_active()){
		m_calendarioDesde->get_date(d_fechaDesde);
		b_fechaDesde = true;
	}
	if (m_activarCalendarioHasta.get_active()){
		m_calendarioHasta->get_date(d_fechaHasta);
		b_fechaHasta = true;
	}

	std::list<common::Stock> stockProducto;
	Gtk::TreeModel::iterator iter = refTreeSelection->get_selected();
	if(iter){
		Gtk::TreeModel::Row row = *iter;
		std::stringstream idProd;
		idProd << (row[m_ProductosList.m_Columns.m_col_id]);
		unsigned long int idProducto;
		idProd >> idProducto;
		stockProducto = modelo->getStockHisto(idProducto);
	}

	if (b_fechaDesde)
		eliminarStockInferior(d_fechaDesde,stockProducto);
	if (b_fechaHasta)
		eliminarStockSuperior(d_fechaHasta,stockProducto);

	m_datosGrafico.clear();
	std::list<common::Stock>::iterator it = stockProducto.begin();
	for (; it != stockProducto.end() ; ++it){
		std::string fecha = (*it).getFecha();
		double valor = (double)(*it).getCantidad();
		DatoGrafico dato(fecha,valor);
		m_datosGrafico.push_back(dato);
	}
	m_ImagenItem.actualizarDatos(m_datosGrafico);
	m_ImagenItem.redibujar();
}

void VistaStockHistorico::eliminarStockInferior(Glib::Date& fechaDesde, std::list<common::Stock>& stockProducto){
	std::stringstream ssFechaDesdeDia;
	ssFechaDesdeDia << (int)fechaDesde.get_day();
	unsigned int diaParametro;
	ssFechaDesdeDia >> diaParametro;

	std::cout << "HOLAAAAAAAAAAAAAAAAAAAAAAAAAAAA::: " << std::endl;
	std::stringstream ssFechaDesdeMes;
	ssFechaDesdeMes << (int)fechaDesde.get_month();
	unsigned int mesParametro;
	ssFechaDesdeMes >> mesParametro;

	std::stringstream ssFechaDesdeAno;
	ssFechaDesdeAno << (int)fechaDesde.get_year();
	unsigned int anoParametro;
	ssFechaDesdeAno >> anoParametro;

	//std::tm tm_fechaDesde,tm_fechaStock;
	//fechaDesde.to_struct_tm(tm_fechaDesde);
	std::list<common::Stock>::iterator it = stockProducto.begin();
	for (; it != stockProducto.end() ; ++it){
		std::string sfechaStock((*it).getFecha());

		std::cerr << "fecha a parsear: ---" << sfechaStock << "---" << std::endl;
		struct tm timeDate;
		strptime(sfechaStock.c_str(),"%a %b %d %H:%M:%S %Y",&timeDate);
		std::cerr << "Antes de mktime: Ano: " << timeDate.tm_year <<" mes: " <<timeDate.tm_mon << " dia: " <<timeDate.tm_yday << std::endl;
		mktime(&timeDate);
		std::cerr << "Despues de mktime: Ano: " << timeDate.tm_year <<" mes: " <<timeDate.tm_mon << " dia: " <<timeDate.tm_yday << std::endl;
		std::string fechaImagen(asctime(&timeDate));
		fechaImagen.erase(fechaImagen.find('\n'));
	    std::cout <<"fecha Parseada:: "<< fechaImagen << std::endl;

		std::cerr << "fecha Calendario: --dia: " << diaParametro << "-- mes: " << mesParametro << "-- ano: " << anoParametro << std::endl;
	//	std::cerr << "fecha Server: dia " <<  timeDate.tm_mday << " -- mes: " << timeDate.tm_mon << " -- ano: " << timeDate.tm_year << std::endl;;
	/*	if(ano < anoParametro)
			stockProducto.erase(it);
		else
			if((ano == anoParametro) && (mes < mesParametro))
				stockProducto.erase(it);
			else
				if ((mes == mesParametro) && (dia < diaParametro))
					stockProducto.erase(it);
					*/
	}
}

void VistaStockHistorico::eliminarStockSuperior(Glib::Date& fechaHasta, std::list<common::Stock>& stockProducto){
	std::stringstream ssFechaHastaDia;
	ssFechaHastaDia << (int)fechaHasta.get_day();
	unsigned int diaParametro;
	ssFechaHastaDia >> diaParametro;

	std::stringstream ssFechaHastaMes;
	ssFechaHastaMes << (int)fechaHasta.get_month();
	unsigned int mesParametro;
	ssFechaHastaMes >> mesParametro;

	std::stringstream ssFechaHastaAno;
	ssFechaHastaAno << (int)fechaHasta.get_year();
	unsigned int anoParametro;
	ssFechaHastaAno >> anoParametro;

	std::list<common::Stock>::iterator it = stockProducto.begin();
	for (; it != stockProducto.end() ; ++it){
		std::stringstream ssfechaStock((*it).getFecha());
		unsigned int dia,mes,ano;
		ssfechaStock >> dia;
		ssfechaStock.ignore(1);
		ssfechaStock >> mes;
		ssfechaStock.ignore(1);
		ssfechaStock >> ano;
		std::cerr << "Stock superior parseado: --dia: " << dia << "-- mes: " << mes << "-- ano: " << ano << std::endl;
		if(ano > anoParametro)
			stockProducto.erase(it);
		else
			if((ano == anoParametro) && (mes > mesParametro))
				stockProducto.erase(it);
			else
				if ((mes == mesParametro) && (dia > diaParametro))
					stockProducto.erase(it);
	}
}
