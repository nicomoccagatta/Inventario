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
#include "../../Common/common_AreaDeVision.h"
#include "../../Common/common_Producto.h"

using common::AreaDeVision;

VistaDescargaImagenDeProductos2::VistaDescargaImagenDeProductos2(ModeloObservable* modelo){

	this->modelo = modelo;

	set_title ("Descarga de imagenes de productos");
	set_border_width(10);
	set_default_size(450, 400);

	/* Add a vpaned widget to our toplevel window */
	add(m_hPaned);

	const std::list<Producto*>* prods = modelo->getProductos();

	size_t cantProductos = prods->size();

	std::cerr << "Hay " << cantProductos << " productos\n";

	m_ProductosList.update(prods);
	m_hPaned.pack1(m_ProductosList);

	m_VBox.pack_end(m_ButtonBox, Gtk::PACK_SHRINK);

	m_DescargarButton.set_label("Descargar");
	m_AtrasButton.set_label("Atras");

	m_ButtonBox.pack_start(m_DescargarButton, Gtk::PACK_SHRINK);
	m_ButtonBox.pack_start(m_AtrasButton, Gtk::PACK_SHRINK);
	m_ButtonBox.set_spacing(6);
	m_ButtonBox.set_layout(Gtk::BUTTONBOX_SPREAD);

	m_VBox.pack_start(m_HBoxImagenes, Gtk::PACK_EXPAND_WIDGET);

	//Gtk::Image a("/home/ale/git/Inventario/Servidor/imagenes/0.jpg");

	m_hPaned.pack2(m_VBox);

	m_AtrasButton.signal_clicked().connect( sigc::mem_fun(*this, &VistaDescargaImagenDeProductos2::on_button_atras) );
	m_DescargarButton.signal_clicked().connect( sigc::mem_fun(*this, &VistaDescargaImagenDeProductos2::on_button_descargar));

	ponerImagenesSeleccion();

	const Glib::RefPtr<const Gtk::TreeSelection> refTreeSelection =
	    m_ProductosList.getTreeView().get_selection();

	//refTreeSelection->signal_changed().connect(
		//    sigc::mem_fun(*this, &VistaDescargaImagenDeProductos2::on_producto_seleccionado) );

	show_all_children();
}

VistaDescargaImagenDeProductos2::~VistaDescargaImagenDeProductos2() {
	// TODO Auto-generated destructor stub
}

bool VistaDescargaImagenDeProductos2::on_imagen_button_press(GdkEventButton* m){
	std::cerr << "APRETE UNA IMAGEN\n";
	return true;
}

void VistaDescargaImagenDeProductos2::on_producto_seleccionado(){

}

void VistaDescargaImagenDeProductos2::asignarModelo(ModeloObservable* modelo){
	this->modelo=modelo;
	this->update();
}

void VistaDescargaImagenDeProductos2::update(){

	//m_ProductosList.borrarLosAnteriores()

	const std::list<Producto*>* prods = modelo->getProductos();

	size_t cantProductos = prods->size();

	std::cerr << "Hay " << cantProductos << " productos\n";

	m_ProductosList.update(prods);
	m_hPaned.add1(m_ProductosList);


	show_all_children();
}

void VistaDescargaImagenDeProductos2::on_button_atras(){
	hide();
	Gtk::Main::quit();
}

void VistaDescargaImagenDeProductos2::on_button_descargar(){
	std::cerr << "DESCARGAR\n";
}

void VistaDescargaImagenDeProductos2::ponerImagenesSeleccion(){
	Gtk::Image* image1 = Gtk::manage(new Gtk::Image());
	image1->set("/home/ale/git/Inventario/Servidor/imagenes/0.jpg");
	Glib::RefPtr<Gdk::Pixbuf> scaled1 = image1->get_pixbuf()->scale_simple(150,150,Gdk::INTERP_BILINEAR);
	image1->set(scaled1);

	Gtk::Image* image2 = Gtk::manage(new Gtk::Image());
	image2->set("/home/ale/git/Inventario/Servidor/imagenes/37.jpg");
	Glib::RefPtr<Gdk::Pixbuf> scaled2 = image2->get_pixbuf()->scale_simple(150,150,Gdk::INTERP_BILINEAR);
	image2->set(scaled2);


	Gtk::VBox* vbox1 = Gtk::manage(new Gtk::VBox());
	Gtk::RadioButton* radio1 = Gtk::manage(new Gtk::RadioButton("radio1"));

	Gtk::VBox* vbox2 = Gtk::manage(new Gtk::VBox());
	Gtk::RadioButton* radio2 = Gtk::manage(new Gtk::RadioButton("radio2"));

	radio1->set_group(radioGroup);
	radio2->set_group(radioGroup);

	vbox1->pack_start(*image1, true, true, 0);
	vbox1->pack_start(*radio1, true, true, 0);

	vbox2->pack_start(*image2, Gtk::PACK_EXPAND_WIDGET);
	vbox2->pack_start(*radio2, Gtk::PACK_EXPAND_WIDGET);

	m_HBoxImagenes.pack_start(*vbox1, true, true, 5);
	m_HBoxImagenes.pack_start(*vbox2, true, true, 5);

}

