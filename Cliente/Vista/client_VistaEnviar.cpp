/*
 * VistaEnviar.cpp
 *
 *  Created on: Jun 11, 2015
 *      Author: ale
 */

#include "client_VistaEnviar.h"

#include <glibmm/date.h>
#include <list>

#define FEATURE_MATCHING 1
#define TEMPLATE_MATCHING 2

using common::AreaDeVision;

VistaEnviar::VistaEnviar(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade)
: Gtk::Dialog(cobject),
  m_refGlade(refGlade),
  m_quitButton(0), m_ENVIARButton(0), m_vistaPrevia(0), m_fileChooser(0), m_calendar(0),
  m_entryHora(0), m_entryMinutos(0), m_entrySegundos(0), m_templateMatching(0),
  m_featureMatching(0), m_AreasDeVision(0)

{
	//CONECTAR BOTONES CON SUS FUNCIONES CONTROLADORAS
	//BOTON SALIR:
	m_refGlade->get_widget("quit_button", m_quitButton);
	if(m_quitButton)
		m_quitButton->signal_clicked().connect( sigc::mem_fun(*this, &VistaEnviar::on_button_quit) );

	//BOTON ENVIAR
	m_refGlade->get_widget("buttonEnviar", m_ENVIARButton);
	if(m_ENVIARButton)
		m_ENVIARButton->signal_clicked().connect( sigc::mem_fun(*this, &VistaEnviar::on_button_ENVIAR) );

	//BOTON VISTA PREVIA
	m_refGlade->get_widget("buttonVistaPrevia", m_vistaPrevia);
	if(m_vistaPrevia)
		m_vistaPrevia->signal_clicked().connect( sigc::mem_fun(*this, &VistaEnviar::on_button_VistaPrevia) );


	//COMBO-BOX de AreasDeVision
	//Creamos las columnas, el modelo para los datos del Combobox y el combo que en este caso será la vista para el modelo planteado
	m_refGlade->get_widget("comboboxAreasDeVision", m_AreasDeVision);
	modeloComboBox = Gtk::ListStore::create(columnas);

	//Establecemos el modelo del combo e indicamos las columnas a mostrar
	m_AreasDeVision->set_model(modeloComboBox);
	//No es necesario agregar la columna valor si sólo queremos mostrar el texto
	//combo.pack_start(columnas.getColumnaValor());
	m_AreasDeVision->pack_start(columnas.getColumnaTexto());
}

VistaEnviar::~VistaEnviar() {
	// TODO Auto-generated destructor stub
}

void VistaEnviar::asignarModelo(ModeloObservable* modelo){
	this->modelo=modelo;
	this->update();
}

void VistaEnviar::asignarControlador(ControladorVistaEnviar* controlador){
	this->controlador = controlador;
}

void VistaEnviar::update(){
	m_refGlade->get_widget("comboboxAreasDeVision", m_AreasDeVision);

	//m_AreasDeVision->clear();
	agregarAreasAlCombo();


}

void VistaEnviar::on_button_quit(){
	this->hide(); //hide() will cause main::run() to end.
}

void VistaEnviar::on_button_ENVIAR(){
	//controlador->buttonENVIARClicked(...);
	m_refGlade->get_widget("entryHora", m_entryHora);
	m_refGlade->get_widget("entryMinutos", m_entryMinutos);
	m_refGlade->get_widget("entrySegundos", m_entrySegundos);
	m_refGlade->get_widget("fileChooserAEnviar", m_fileChooser);
	m_refGlade->get_widget("radiobuttonTemplateMatching", m_templateMatching);
	m_refGlade->get_widget("radiobuttonFeatureMatching", m_featureMatching);
	m_refGlade->get_widget("comboboxAreasDeVision", m_AreasDeVision);
	m_refGlade->get_widget("calendar1", m_calendar);

	Glib::ustring horas = m_entryHora->get_text();
	Glib::ustring minutos = m_entryMinutos->get_text();
	Glib::ustring segundos = m_entrySegundos->get_text();

	std::cerr << "Horas: " << horas << " ";
	std::cerr << "Minutos: " << minutos << " ";
	std::cerr << "Segundos: " << segundos << "\n";

	Glib::Date fecha;
	guint dia, mes, anio;
	m_calendar->get_date(fecha);
	//fecha.to_struct_tm();
	m_calendar->get_date(anio,mes,dia);
	++mes;
	std::cerr << "Fecha: " << dia << "/" << mes << "/" << anio << "\n";

	Glib::ustring rutaArchivo = m_fileChooser->get_filename();
	std::cerr << "Ruta archivo: " << rutaArchivo << "\n";

	int matching = -1;
	if (m_featureMatching->get_active()){
		matching = FEATURE_MATCHING;
		std::cerr << "Feature Matching\n";
	}else{
		matching = TEMPLATE_MATCHING;
		std::cerr << "Template Matching\n";
	}
	std::cerr << matching;

	Gtk::TreeModel::Row fila = *m_AreasDeVision->get_active();
	std::cout << "Elemento elegido del Combo: "
			<< fila[columnas.getColumnaTexto()]
			<< " \n";//con valor: "
	AreaDeVision* area = fila[columnas.getColumnaValor()];

	controlador->buttonENVIARClicked(rutaArchivo,&fecha,horas,minutos,segundos,matching,area);
}

void VistaEnviar::on_button_VistaPrevia(){
	m_refGlade->get_widget("fileChooserAEnviar", m_fileChooser);

	Glib::ustring rutaArchivo = m_fileChooser->get_filename();
	std::cerr << "Ruta archivo: " << rutaArchivo << "\n";

	if (rutaArchivo.length() < 3){
		std::cerr << "POPUP: NO ELEGISTE ARCHIVO";
		return;
	}

	controlador->buttonVistaPreviaClicked(rutaArchivo);

}

void VistaEnviar::agregarAreasAlCombo(){
	const std::list<AreaDeVision*>* areas = modelo->getAreasDeVision();

	std::list<AreaDeVision*>::const_iterator it;
	for (it = areas->begin(); it!= areas->end(); ++it){
		Gtk::TreeModel::Row fila = *(modeloComboBox->append());
		fila[columnas.getColumnaValor()] = *it;
		fila[columnas.getColumnaTexto()] = (*it)->getUbicacion();
	}

	/*for (int i=1; i<10; ++i){
		Gtk::TreeModel::Row fila = *(modeloComboBox->append());
		fila[columnas.getColumnaValor()] = i;
		fila[columnas.getColumnaTexto()] = "Teeexto";
	}
	*/

}
