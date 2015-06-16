/*
 * client_VistaDescargaImagenDeProductos.cpp
 *
 *  Created on: Jun 15, 2015
 *      Author: ale
 */

#include <list>

#include "client_VistaDescargaImagenDeProductos.h"
#include "../../Common/common_AreaDeVision.h"
#include "../../Common/common_Producto.h"

using common::AreaDeVision;

VistaDescargaImagenDeProductos::VistaDescargaImagenDeProductos(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade)
: Gtk::Window(cobject),
  m_refGlade(refGlade),
  m_atrasButton(0), m_descargarButton(0), m_viewport(0), m_productosVbox(true,0),
  m_hPaned(0){

	this->modelo = 0;

	//CONECTAR BOTONES CON SUS FUNCIONES CONTROLADORAS
	//BOTON ATRAS:
	m_refGlade->get_widget("AtrasButton", m_atrasButton);
	if(m_atrasButton)
		m_atrasButton->signal_clicked().connect( sigc::mem_fun(*this, &VistaDescargaImagenDeProductos::on_button_atras) );

	//BOTON ENVIAR
	m_refGlade->get_widget("DescargarButton", m_descargarButton);
	if(m_descargarButton)
		m_descargarButton->signal_clicked().connect( sigc::mem_fun(*this, &VistaDescargaImagenDeProductos::on_button_descargar) );

	/*m_refGlade->get_widget("viewport1", m_viewport);
	if (m_viewport){
		std::cerr << "ENCONTRE EL VIEWPORT\n";
		//std::list<AreaDeVision*>::const_iterator it;
			//m_viewport->add_label((*it)->getUbicacion(), true, 0, 0);
	}*/



}

VistaDescargaImagenDeProductos::~VistaDescargaImagenDeProductos() {
	// TODO Auto-generated destructor stub
}

void VistaDescargaImagenDeProductos::asignarModelo(ModeloObservable* modelo){
	this->modelo=modelo;
	this->update();
}

void VistaDescargaImagenDeProductos::update(){
	const std::list<Producto*>* prods = modelo->getProductos();
	std::list<Producto*>::const_iterator it;

	size_t cantProductos = prods->size();

	std::cerr << "Hay " << cantProductos << " productos\n";

	//m_refGlade->get_widget("productosVBox", m_productosVBox);

	/*if(!m_productosVBox){
		std::cerr << "NO ENCONTRE EL VBOX";
		return;
	}*/

	m_refGlade->get_widget("hPaned", m_hPaned);

	m_ProductosList.update(prods);
	m_hPaned->pack1(m_ProductosList);
/*
	int i;
	for (it=prods->begin(), i=0; it!=prods->end();++it, ++i){
		std::cerr << (*it)->getId() << " " << (*it)->getNombre() << std::endl;

		//Gtk::Label* lab = new Gtk::Label((*it)->getNombre(), true);

		m_productosVbox.pack_start(*Gtk::manage(new Gtk::Label((*it)->getNombre(), true)));

	}
	m_productosVbox.show();
*/
	show_all_children();
}

void VistaDescargaImagenDeProductos::on_button_atras(){
	hide();
	Gtk::Main::quit();
}

void VistaDescargaImagenDeProductos::on_button_descargar(){
	std::cerr << "DESCARGAR\n";
}

