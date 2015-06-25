/*
 * VistaStockGeneral.cpp
 *
 *  Created on: 23/6/2015
 *      Author: nicomoccagatta
 */

#include "VistaStockGeneral.h"

VistaStockGeneral::VistaStockGeneral() {
	m_ProductosList.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
	m_ProductosList.set_size_request(200,400);

	m_ProductosTreeView.append_column("ID", m_ProductosList.m_Columns.m_col_id);
	m_ProductosTreeView.append_column("Nombre", m_ProductosList.m_Columns.m_col_nombre);
	m_ProductosTreeView.append_column("Cantidad", m_ProductosList.m_Columns.m_col_cantidad);
	m_ProductosList.add(m_ProductosTreeView);
	m_HBoxGrillaEImagen.pack_start(m_ProductosList);

	m_HBoxGrillaEImagen.pack_end(m_ImagenItem);

	refTreeSelection = m_ProductosTreeView.get_selection();
	refTreeSelection->signal_changed().connect(
			    sigc::mem_fun(*this, &VistaStockGeneral::on_producto_seleccionado) );
}

VistaStockGeneral::~VistaStockGeneral() {
}

void VistaStockGeneral::update(){

}

void VistaStockGeneral::run(Gtk::Viewport *panelDinamico,Modelo_Observable *modelo){
	this->modelo = modelo;
	this->panelDinam = panelDinamico;

	m_refProductosListStore = Gtk::ListStore::create(m_ProductosList.m_Columns);
	m_ProductosTreeView.set_model(m_refProductosListStore);
	this->update_lista_productos();

	panelDinam->add(m_HBoxGrillaEImagen);

	m_ImagenItem.set("imagenes/imagen_vacia.png");
	Glib::RefPtr<Gdk::Pixbuf> scaled1 = m_ImagenItem.get_pixbuf()->scale_simple(250,250,Gdk::INTERP_BILINEAR);
	m_ImagenItem.set(scaled1);

	refTreeSelection = m_ProductosTreeView.get_selection();
}


void VistaStockGeneral::on_producto_seleccionado(){
	Gtk::TreeModel::iterator iter = refTreeSelection->get_selected();
	if(iter){
		Gtk::TreeModel::Row row = *iter;
		std::stringstream idIcono;
		//idIcono << (row[m_ProductosList.m_Columns.m_col_idIcono]);
		std::string rutaImagen = "imagenes/" + idIcono.str() +".jpg";
		m_ImagenItem.set(rutaImagen);
		Glib::RefPtr<Gdk::Pixbuf> scaled1 = m_ImagenItem.get_pixbuf()->scale_simple(250,250,Gdk::INTERP_BILINEAR);
		m_ImagenItem.set(scaled1);
	}
}


void VistaStockGeneral::update_lista_productos(){
	const std::list<Producto*>* prods = modelo->getProductos();
	std::list<Producto*>::const_iterator it;
	for (it=prods->begin(); it!=prods->end();++it){
	Gtk::TreeModel::Row row = *(m_refProductosListStore->append());
	row[m_ProductosList.m_Columns.m_col_id] = (*it)->getId();
	row[m_ProductosList.m_Columns.m_col_nombre] = (*it)->getNombre();
	row[m_ProductosList.m_Columns.m_col_cantidad] = 0;//modelo->consultarStock((*it)->getId());
//	row[m_ProductosList.m_Columns.m_col_idIcono] = (*it)->getIdIcono();
	row[m_ProductosList.m_Columns.m_col_data] = *it;
	}
}
