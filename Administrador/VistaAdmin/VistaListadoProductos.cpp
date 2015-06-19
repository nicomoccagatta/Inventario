/*
 * VistaListadoProductos.cpp
 *
 *  Created on: 17/6/2015
 *      Author: nicomoccagatta
 */

#include "VistaListadoProductos.h"

VistaListadoProductos::VistaListadoProductos()
{
	m_ProductosList.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
	m_ProductosList.set_size_request(200,400);
	m_ProductosList.add(m_ProductosTreeView);
	horizontalBox.pack_start(m_ProductosList);

	m_EditarButton.signal_clicked().connect( sigc::mem_fun(*this, &VistaListadoProductos::on_button_editar));
	m_EliminarButton.signal_clicked().connect( sigc::mem_fun(*this, &VistaListadoProductos::on_button_eliminar) );

	m_ProductosTreeView.append_column("Nombre", m_ProductosList.m_Columns.m_col_nombre);
	m_ProductosTreeView.append_column("Descripcion", m_ProductosList.m_Columns.m_col_descripcion);

	m_imagenPlusBotones.pack_start(m_imagenItem);
	m_imagenPlusBotones.pack_end(m_ButtonBox);
	horizontalBox.pack_end(m_imagenPlusBotones,Gtk::PACK_SHRINK,true,0);
	m_EditarButton.set_label("Editar");
	m_EliminarButton.set_label("Eliminar");

	m_ButtonBox.pack_start(m_EditarButton);
	m_ButtonBox.pack_start(m_EliminarButton);
	m_ButtonBox.set_layout(Gtk::BUTTONBOX_SPREAD);

	refTreeSelection = m_ProductosTreeView.get_selection();
	refTreeSelection->signal_changed().connect(
		    sigc::mem_fun(*this, &VistaListadoProductos::on_producto_seleccionado) );
}

void VistaListadoProductos::update(){
	//const std::list<Producto*>* prods = modelo->getProductos();
}

void VistaListadoProductos::run(Gtk::Viewport *panelDinamico,Modelo_Observable *modelo){
	this->modelo = modelo;
	this->panelDinam = panelDinamico;

	m_refProductosListStore = Gtk::ListStore::create(m_ProductosList.m_Columns);
	m_ProductosTreeView.set_model(m_refProductosListStore);
	this->update_lista_productos();

	panelDinam->add(horizontalBox);

	m_imagenItem.set("imagenes/imagen_vacia.png");
	Glib::RefPtr<Gdk::Pixbuf> scaled1 = m_imagenItem.get_pixbuf()->scale_simple(250,250,Gdk::INTERP_BILINEAR);
	m_imagenItem.set(scaled1);

	refTreeSelection = m_ProductosTreeView.get_selection();
}

VistaListadoProductos::~VistaListadoProductos() {
}

void VistaListadoProductos::on_button_editar(){

}

void VistaListadoProductos::on_button_eliminar(){

}

void VistaListadoProductos::on_producto_seleccionado(){
	Gtk::TreeModel::iterator iter = refTreeSelection->get_selected();
	if(iter){
		Gtk::TreeModel::Row row = *iter;
		std::cerr << "Producto seleccionado: " << row[m_ProductosList.m_Columns.m_col_nombre] <<"\n";
		m_imagenItem.set("imagenes/38.jpg");
		Glib::RefPtr<Gdk::Pixbuf> scaled1 = m_imagenItem.get_pixbuf()->scale_simple(250,250,Gdk::INTERP_BILINEAR);
		m_imagenItem.set(scaled1);
		//controlador.on_producto_seleccionado(row[m_ProductosList.m_Columns.m_col_data]);
	}
}

void VistaListadoProductos::update_lista_productos(){
	const std::list<Producto*>* prods = modelo->getProductos();
	std::list<Producto*>::const_iterator it;
	for (it=prods->begin(); it!=prods->end();++it){
	Gtk::TreeModel::Row row = *(m_refProductosListStore->append());
	row[m_ProductosList.m_Columns.m_col_nombre] = (*it)->getNombre();
	row[m_ProductosList.m_Columns.m_col_descripcion] = (*it)->getDescripcion();
	row[m_ProductosList.m_Columns.m_col_data] = *it;
	}
}
