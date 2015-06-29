/*
 * VistaStockGeneral.cpp
 *
 *  Created on: 23/6/2015
 *      Author: nicomoccagatta
 */

#include "VistaStockGeneral.h"

VistaStockGeneral::VistaStockGeneral() : modelo(0), panelDinam(0) {
	m_ProductosList.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
	m_ProductosList.set_size_request(450,Gtk::EXPAND);

	m_ProductosTreeView.append_column("Icono", m_ProductosList.m_Columns.m_col_imagenIcono);
	m_ProductosTreeView.append_column("Nombre", m_ProductosList.m_Columns.m_col_nombre);
	m_ProductosTreeView.append_column("Cantidad", m_ProductosList.m_Columns.m_col_cantidad);
	m_ProductosTreeView.set_search_column(1);
	m_ProductosList.add(m_ProductosTreeView);
	m_HBoxGrillaEImagen.pack_start(m_ProductosList);

	m_ImagenItem.set_size_request(720,Gtk::EXPAND);
	m_HBoxGrillaEImagen.pack_end(m_ImagenItem);
}

VistaStockGeneral::~VistaStockGeneral() {
}

void VistaStockGeneral::update(){
	std::cerr << "UPDATE VISTA STOCK GENERAL.." << std::endl;
	this->update_lista_productos();
}

void VistaStockGeneral::run(Gtk::Viewport *panelDinamico,Modelo_Observable *modelo){
	this->modelo = modelo;
	this->panelDinam = panelDinamico;

	this->update_lista_productos();

	panelDinam->add(m_HBoxGrillaEImagen);
}

void VistaStockGeneral::update_lista_productos(){
	m_refProductosListStore = Gtk::ListStore::create(m_ProductosList.m_Columns);
	m_ProductosTreeView.set_model(m_refProductosListStore);

	modelo->actualizarStockGeneral();
	const std::list<Producto*>* prods = modelo->getProductos();
	std::list<Producto*>::const_iterator it;
	for (it=prods->begin(); it!=prods->end();++it){
	Gtk::TreeModel::Row row = *(m_refProductosListStore->append());
	std::string rutaImagen = modelo->getImagenConID((*it)->getIdIcono());
	Glib::RefPtr<Gdk::Pixbuf>  pic = Gdk::Pixbuf::create_from_file(rutaImagen,30,30,false);
	row[m_ProductosList.m_Columns.m_col_imagenIcono] = pic;
	row[m_ProductosList.m_Columns.m_col_nombre] = (*it)->getNombre();
	row[m_ProductosList.m_Columns.m_col_cantidad] = modelo->consultarStock((*it)->getId());
	row[m_ProductosList.m_Columns.m_col_data] = *it;
	}
}
