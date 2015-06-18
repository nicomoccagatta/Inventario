/*
 * client_VistaDescargaImagenDeProductos.cpp
 *
 *  Created on: Jun 15, 2015
 *      Author: ale
 */

#include <list>
#include <gdkmm-2.4/gdkmm.h>
#include <gtkmm-2.4/gtkmm.h>

#include "client_VistaDescargaImagenDeProductos2.h"
#include "common_AreaDeVision.h"
#include "common_Producto.h"

using common::AreaDeVision;

VistaDescargaImagenDeProductos2::VistaDescargaImagenDeProductos2(ModeloObservable* modelo):
	controlador(modelo,this){

	this->modelo = modelo;

	set_title ("Descarga de imagenes de productos");
	set_border_width(10);
	set_default_size(600, 400);

	/* Add a vpaned widget to our toplevel window */
	add(m_hPaned);

	/* Create a new scrolled window, with scrollbars only if needed */
	m_ProductosList.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
	m_ProductosList.set_size_request(200,400);

	m_ProductosList.add(m_ProductosTreeView);

	/* create list store */
	m_refProductosListStore = Gtk::ListStore::create(m_ProductosList.m_Columns);

	m_ProductosTreeView.set_model(m_refProductosListStore);

	const std::list<Producto*>* prods = modelo->getProductos();

	size_t cantProductos = prods->size();
	std::cerr << "Hay " << cantProductos << " productos\n";

	this->update_lista_productos();
	//Add the Model's column to the View's columns:
	m_ProductosTreeView.append_column("IdIcono", m_ProductosList.m_Columns.m_col_icon_id);
	m_ProductosTreeView.append_column("Productos", m_ProductosList.m_Columns.m_col_text);

	m_hPaned.pack1(m_ProductosList);

	m_VBox.pack_end(m_ButtonBox, Gtk::PACK_SHRINK);

	m_DescargarButton.set_label("Descargar");
	m_AtrasButton.set_label("Atras");

	m_ButtonBox.pack_start(m_DescargarButton, Gtk::PACK_SHRINK);
	m_ButtonBox.pack_start(m_AtrasButton, Gtk::PACK_SHRINK);
	m_ButtonBox.set_spacing(6);
	m_ButtonBox.set_layout(Gtk::BUTTONBOX_SPREAD);

	m_HBoxImagenes = new Gtk::HBox(false, 5);
	m_VBox.pack_start(*m_HBoxImagenes, Gtk::PACK_SHRINK);

	//Gtk::Image a("/home/ale/git/Inventario/Servidor/imagenes/0.jpg");

	m_hPaned.pack2(m_VBox);

	m_AtrasButton.signal_clicked().connect( sigc::mem_fun(*this, &VistaDescargaImagenDeProductos2::on_button_atras) );
	m_DescargarButton.signal_clicked().connect( sigc::mem_fun(*this, &VistaDescargaImagenDeProductos2::on_button_descargar));

	//this->update_lista_imagenes();

	//SIGNALSSSSSSSSSSSs
	refTreeSelection = m_ProductosTreeView.get_selection();
	refTreeSelection->signal_changed().connect(
		    sigc::mem_fun(*this, &VistaDescargaImagenDeProductos2::on_producto_seleccionado) );

	show_all_children();
}

VistaDescargaImagenDeProductos2::~VistaDescargaImagenDeProductos2() {
	// TODO Auto-generated destructor stub
}

void VistaDescargaImagenDeProductos2::on_producto_seleccionado(){
	Gtk::TreeModel::iterator iter = refTreeSelection->get_selected();
	if(iter){ //If anything is selected
		Gtk::TreeModel::Row row = *iter;
		std::cerr << "APRETE EL PRODUCTO " << row[m_ProductosList.m_Columns.m_col_text] <<"\n";
		controlador.on_producto_seleccionado(row[m_ProductosList.m_Columns.m_col_data]);
	}
}

void VistaDescargaImagenDeProductos2::update(){

	//m_ProductosList.borrarLosAnteriores()

	const std::list<Producto*>* prods = modelo->getProductos();

	size_t cantProductos = prods->size();

	std::cerr << "Hay " << cantProductos << " productos\n";


	//show_all_children();
}

void VistaDescargaImagenDeProductos2::update_lista_productos(){
	const std::list<Producto*>* prods = modelo->getProductos();

	/* Add some messages to the window */
	std::list<Producto*>::const_iterator it;

	for (it=prods->begin(); it!=prods->end();++it){
		std::cerr << (*it)->getId() << " " << (*it)->getNombre()
				<< " iconoID: " << (*it)->getIdIcono() << std::endl;

		Gtk::TreeModel::Row row = *(m_refProductosListStore->append());
		row[m_ProductosList.m_Columns.m_col_icon_id] = (*it)->getIdIcono();
		row[m_ProductosList.m_Columns.m_col_text] = (*it)->getNombre();
		row[m_ProductosList.m_Columns.m_col_data] = *it;
	}
}



void VistaDescargaImagenDeProductos2::on_button_atras(){
	hide();
	Gtk::Main::quit();
}

void VistaDescargaImagenDeProductos2::on_button_descargar(){
	std::cerr << "DESCARGAR\n";
	//this->radioGroup.
}

void VistaDescargaImagenDeProductos2::update_lista_imagenes(std::list<unsigned long int>* ids){
	//m_VBox.remove(*m_HBoxImagenes);
	//delete m_HBoxImagenes;
	//m_HBoxImagenes = new Gtk::HBox(false, 5);
	//m_VBox.pack_start(*m_HBoxImagenes, Gtk::PACK_SHRINK);

	/*Glib::ListHandle<Widget*> radios = m_HBoxImagenes->get_children();

	Glib::ListHandle<Widget*>::const_iterator radioIter;

	for (radioIter = radios.begin(); radioIter!=radios.end(); ++radioIter){
		delete (*radioIter);
	}

	Gtk::Box_Helpers::BoxList *childList = &m_HBoxImagenes->children();
	Gtk::Box_Helpers::BoxList::iterator start = childList->begin();
	Gtk::Box_Helpers::BoxList::iterator end = childList->end();

	childList->erase(start, end);
*/
	std::list<unsigned long int>::iterator it;

	for (it=ids->begin(); it!=ids->end();++it){
		std::string ruta = modelo->getImagenConId(*it);

		Gtk::Image* image = Gtk::manage(new Gtk::Image());
		image->set(ruta.c_str());
		Glib::RefPtr<Gdk::Pixbuf> scaled1 = image->get_pixbuf()->scale_simple(150,150,Gdk::INTERP_BILINEAR);
		image->set(scaled1);

		//Gtk::VBox* vbox = Gtk::manage(new Gtk::VBox());
		Gtk::RadioButton* radio = Gtk::manage(new Gtk::RadioButton());

		radio->set_image(*image);
		radio->set_group(radioGroup);

		//vbox->pack_start(*image, Gtk::PACK_SHRINK);
		//vbox->pack_start(*radio, Gtk::PACK_SHRINK);

		m_HBoxImagenes->pack_start(*radio, Gtk::PACK_SHRINK);
	}
	get_settings()->set_property("gtk-button-images",true);
	show_all_children();
}

