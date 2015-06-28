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

	m_AgregarButton.set_label("Agregar");
	m_botoneraABM.pack_start(m_AgregarButton);
	m_EditarButton.set_label("Editar");
	m_botoneraABM.pack_start(m_EditarButton);
	m_EliminarButton.set_label("Eliminar");
	m_botoneraABM.pack_start(m_EliminarButton);
	m_botoneraABM.set_layout(Gtk::BUTTONBOX_END);

	m_verticalBox.pack_start(m_botoneraABM,Gtk::PACK_SHRINK,true,0);

	m_ProductosTreeView.append_column("Icono", m_ProductosList.m_Columns.m_col_imagenIcono);
	m_ProductosTreeView.append_column("Nombre", m_ProductosList.m_Columns.m_col_nombre);
	m_ProductosTreeView.append_column("Descripcion", m_ProductosList.m_Columns.m_col_descripcion);
	m_ProductosList.add(m_ProductosTreeView);
	m_ProductosList.set_size_request(Gtk::EXPAND,300);
	m_verticalBox.pack_start(m_ProductosList);

	m_viewportVentanitaBotoneraImagenes = new Gtk::Viewport(*m_ventanitaBotoneraImagenes.get_hadjustment(),*m_ventanitaBotoneraImagenes.get_vadjustment());
	m_ventanitaBotoneraImagenes.add(*m_viewportVentanitaBotoneraImagenes);
	m_viewportVentanitaBotoneraImagenes->add(m_botoneraImagenesProducto);
	m_verticalBox.pack_end(m_ventanitaBotoneraImagenes);


	m_EditarButton.signal_clicked().connect( sigc::mem_fun(*this, &VistaListadoProductos::on_button_editar));
	m_EliminarButton.signal_clicked().connect( sigc::mem_fun(*this, &VistaListadoProductos::on_button_eliminar) );

	refTreeSelection = m_ProductosTreeView.get_selection();
	refTreeSelection->signal_changed().connect(
		    sigc::mem_fun(*this, &VistaListadoProductos::on_producto_seleccionado) );
}

void VistaListadoProductos::update(){
	std::list<Gtk::Image*>::iterator it = m_listaPunteroImagenes.begin();
	for( ; it != m_listaPunteroImagenes.end() ; ++it) {
		delete (*it);
	}
	m_listaPunteroImagenes.clear();
	panelDinam->show_all();
}

void VistaListadoProductos::run(Gtk::Viewport *panelDinamico,Modelo_Observable *modelo){
	this->modelo = modelo;
	this->panelDinam = panelDinamico;

	m_refProductosListStore = Gtk::ListStore::create(m_ProductosList.m_Columns);
	m_ProductosTreeView.set_model(m_refProductosListStore);
	this->update_lista_productos();

	panelDinam->add(m_verticalBox);

	refTreeSelection = m_ProductosTreeView.get_selection();
}

VistaListadoProductos::~VistaListadoProductos() {
	delete m_viewportVentanitaBotoneraImagenes;
}

void VistaListadoProductos::on_button_editar(){

}

void VistaListadoProductos::on_button_eliminar(){
	Gtk::TreeModel::iterator iter = refTreeSelection->get_selected();
	if(iter){
		Gtk::TreeModel::Row row = *iter;
		std::cerr << "Producto seleccionado: " << row[m_ProductosList.m_Columns.m_col_nombre] <<"\n";
		modelo->eliminarProducto(row[m_ProductosList.m_Columns.m_col_id]);
		this->panelDinam->remove();
		this->modelo->actualizarProductos();
		this->run(this->panelDinam,this->modelo);
		//controlador.on_producto_seleccionado(row[m_ProductosList.m_Columns.m_col_data]);
	}

}

void VistaListadoProductos::on_producto_seleccionado(){
	std::list<Gtk::Image*>::iterator it = m_listaPunteroImagenes.begin();
	for( ; it != m_listaPunteroImagenes.end() ; ++it) {
		delete (*it);
	}
	m_listaPunteroImagenes.clear();

	Gtk::TreeModel::iterator iter = refTreeSelection->get_selected();
	if(iter){
		Gtk::TreeModel::Row row = *iter;
		std::stringstream idProd;
		idProd << (row[m_ProductosList.m_Columns.m_col_id]);
		unsigned long int idProducto;
		idProd >> idProducto;
		std::list<unsigned long int> vectorIdsImagenes = modelo->getIdsImagenes(idProducto);
		std::list<unsigned long int>::iterator itVectorImagenes = vectorIdsImagenes.begin();
		for ( ; itVectorImagenes != vectorIdsImagenes.end() ; ++itVectorImagenes){
			Gtk::Image *imagen = new Gtk::Image;
			std::string rutaImagen = modelo->getImagenConID(*itVectorImagenes);
			std::cerr << "RUTA DE IMAGEN A SETEAR" << rutaImagen << std::endl;
			imagen->set(rutaImagen);
			Glib::RefPtr<Gdk::Pixbuf> scaled1 = imagen->get_pixbuf()->scale_simple(150,150,Gdk::INTERP_BILINEAR);
			imagen->set(scaled1);
			m_listaPunteroImagenes.push_back(imagen);
			m_botoneraImagenesProducto.pack_end(*imagen);
		}
		panelDinam->show_all();
	}
}

void VistaListadoProductos::update_lista_productos(){
	const std::list<Producto*>* prods = modelo->getProductos();
	std::list<Producto*>::const_iterator it;
	for (it=prods->begin(); it!=prods->end();++it){
		Gtk::TreeModel::Row row = *(m_refProductosListStore->append());
		row[m_ProductosList.m_Columns.m_col_id] = (*it)->getId();
		row[m_ProductosList.m_Columns.m_col_nombre] = (*it)->getNombre();
		std::cout << "Actualizo producto: " << (*it)->getNombre() << std::endl;
		row[m_ProductosList.m_Columns.m_col_descripcion] = (*it)->getDescripcion();
		std::string rutaImagen = modelo->getImagenConID((*it)->getIdIcono());
		std::cout << "Ruta de imagen: " << rutaImagen << std::endl;
		Glib::RefPtr<Gdk::Pixbuf>  pic = Gdk::Pixbuf::create_from_file(rutaImagen,30,30,false);
		row[m_ProductosList.m_Columns.m_col_imagenIcono] = pic;
		row[m_ProductosList.m_Columns.m_col_data] = *it;
	}
}
