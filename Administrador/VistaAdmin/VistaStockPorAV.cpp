/*
 * VistaStockPorAV.cpp
 *
 *  Created on: 28/6/2015
 *      Author: nicomoccagatta
 */

#include "VistaStockPorAV.h"

VistaStockPorAV::VistaStockPorAV() : modelo(0), panelDinam(0) {
	m_ProductosList.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
	m_ProductosList.set_size_request(430,530);

	m_AreasDeVision.pack_start(columnas.getColumnaTexto());
	m_AreasDeVision.signal_changed().connect(sigc::mem_fun(*this, &VistaStockPorAV::on_av_seleccionado));
	m_AreasDeVision.set_size_request(400,50);
	m_botoneraComboBox.pack_start(m_AreasDeVision);
	m_botoneraComboBox.set_layout(Gtk::BUTTONBOX_CENTER);
	m_vBoxPrincipal.pack_start(m_botoneraComboBox);

	m_ProductosTreeView.append_column("Icono", m_ProductosList.m_Columns.m_col_imagenIcono);
	m_ProductosTreeView.append_column("Nombre", m_ProductosList.m_Columns.m_col_nombre);
	m_ProductosTreeView.append_column("Cantidad", m_ProductosList.m_Columns.m_col_cantidad);
	m_ProductosTreeView.set_search_column(1);
	m_ProductosList.add(m_ProductosTreeView);
	m_refProductosListStore = Gtk::ListStore::create(m_ProductosList.m_Columns);
	m_ProductosTreeView.set_model(m_refProductosListStore);

	m_HBoxGrillaEImagen.pack_start(m_ProductosList);

	m_ImagenItem.set_size_request(770,Gtk::EXPAND);
	m_HBoxGrillaEImagen.pack_end(m_ImagenItem);
	m_vBoxPrincipal.pack_end(m_HBoxGrillaEImagen);
}

VistaStockPorAV::~VistaStockPorAV() {

}

void VistaStockPorAV::update(){
	std::cerr << "UPDATE VISTA STOCK POR AREA DE VISION.." << std::endl;
	this->update_lista_av();
	this->on_av_seleccionado();
}

void VistaStockPorAV::run(Gtk::Viewport *panelDinamico,Modelo_Observable *modelo){
	this->modelo = modelo;
	this->panelDinam = panelDinamico;

	this->update_lista_av();

	panelDinam->add(m_vBoxPrincipal);
}

void VistaStockPorAV::on_av_seleccionado(){
	m_datosGrafico.clear();

	m_refProductosListStore = Gtk::ListStore::create(m_ProductosList.m_Columns);
	m_ProductosTreeView.set_model(m_refProductosListStore);

	if (m_AreasDeVision.get_active()){
		Gtk::TreeModel::Row fila = *m_AreasDeVision.get_active();
		AreaDeVision *area = fila[columnas.getColumnaValor()];
		const std::list<Producto*>* prods = area->getProductosDetectados();
		std::list<Producto*>::const_iterator it;
		for (it=prods->begin(); it!=prods->end();++it){
			Gtk::TreeModel::Row row = *(m_refProductosListStore->append());
			std::string rutaImagen = modelo->getImagenConID((*it)->getIdIcono());
			Glib::RefPtr<Gdk::Pixbuf>  pic = Gdk::Pixbuf::create_from_file(rutaImagen,20,20,false);
			row[m_ProductosList.m_Columns.m_col_imagenIcono] = pic;
			row[m_ProductosList.m_Columns.m_col_nombre] = (*it)->getNombre();
			row[m_ProductosList.m_Columns.m_col_cantidad] = (*it)->getStock();
			row[m_ProductosList.m_Columns.m_col_data] = *it;
			DatoGrafico dato((*it)->getNombre(),(double)(*it)->getStock());
			m_datosGrafico.push_back(dato);
		}
		m_ImagenItem.actualizarDatos(m_datosGrafico);
	}
	m_ImagenItem.redibujar();
}

void VistaStockPorAV::update_lista_av(){
	modeloComboBox = Gtk::ListStore::create(columnas);
	m_AreasDeVision.set_model(modeloComboBox);

	const std::list<AreaDeVision*>* areas = modelo->getAreasDeVision();
	std::list<AreaDeVision*>::const_iterator it;
	for (it = areas->begin(); it!= areas->end(); ++it){
		Gtk::TreeModel::Row fila = *(modeloComboBox->append());
		fila[columnas.getColumnaValor()] = *it;
		fila[columnas.getColumnaTexto()] = (*it)->getUbicacion();
	}
}
