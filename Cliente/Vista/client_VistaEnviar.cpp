/*
 * VistaEnviar.cpp
 *
 *  Created on: Jun 11, 2015
 *      Author: ale
 */

#include "client_VistaEnviar.h"

#include <glibmm/date.h>
#include <sys/stat.h> //para sacar el las modified
#include <time.h>
#include <list>

#define FEATURE_MATCHING 1
#define TEMPLATE_MATCHING 2

using common::AreaDeVision;

VistaEnviar::VistaEnviar(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade)
: Gtk::Viewport(cobject),
  m_refGlade(refGlade),
  m_ENVIARButton(0), m_vistaPrevia(0), m_fechaHoy(0), m_fechaUltimaMod(0),
  m_fileChooser(0), m_calendar(0), m_entryHora(0), m_entryMinutos(0),
  m_entrySegundos(0), m_templateMatching(0), m_featureMatching(0), m_AreasDeVision(0)

{
	//CONECTAR BOTONES CON SUS FUNCIONES CONTROLADORAS
	//BOTON ENVIAR
	m_refGlade->get_widget("buttonEnviar", m_ENVIARButton);
	if(m_ENVIARButton)
		m_ENVIARButton->signal_clicked().connect( sigc::mem_fun(*this, &VistaEnviar::on_button_ENVIAR) );

	//BOTON VISTA PREVIA
	m_refGlade->get_widget("buttonVistaPrevia", m_vistaPrevia);
	if(m_vistaPrevia)
		m_vistaPrevia->signal_clicked().connect( sigc::mem_fun(*this, &VistaEnviar::on_button_VistaPrevia) );

	//BOTON AUTOCOMPLETAR FECHA DE HOY
	m_refGlade->get_widget("buttonFechaHoy", m_fechaHoy);
	if(m_fechaHoy)
		m_fechaHoy->signal_clicked().connect( sigc::mem_fun(*this, &VistaEnviar::on_button_AutocompletarHoy) );

	//BOTON AUTOCOMPLETAR FECHA DE HOY
	m_refGlade->get_widget("buttonFechaUltimaMod", m_fechaUltimaMod);
	if(m_fechaUltimaMod)
		m_fechaUltimaMod->signal_clicked().connect( sigc::mem_fun(*this, &VistaEnviar::on_button_AutocompletarFechaUltimaModif) );


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
	if(controlador)
		delete controlador;
}

void VistaEnviar::asignarModelo(ModeloObservable* modelo){
	this->modelo=modelo;
	this->controlador = new ControladorVistaEnviar(modelo);
	this->update();
}

void VistaEnviar::asignarControlador(ControladorVistaEnviar* controlador){
	this->controlador = controlador;
}

void VistaEnviar::update(){
	m_refGlade->get_widget("comboboxAreasDeVision", m_AreasDeVision);

	//m_AreasDeVision->clear();
	agregarAreasAlCombo();

	show_all_children();
}

void VistaEnviar::on_button_quit(){
	this->hide(); //hide() will cause main::run() to end.
}

void VistaEnviar::on_button_AutocompletarHoy(){
	std::cerr << "AUTOCOMPLETANDO HOY\n";

	m_refGlade->get_widget("entryHora", m_entryHora);
	m_refGlade->get_widget("entryMinutos", m_entryMinutos);
	m_refGlade->get_widget("entrySegundos", m_entrySegundos);
	m_refGlade->get_widget("calendar1", m_calendar);

	time_t hora;
	std::tm* timer;
	time(&hora);
	timer = localtime (&hora);

	this->setearFechaYHora(timer);
}

void VistaEnviar::on_button_AutocompletarFechaUltimaModif(){
	m_refGlade->get_widget("entryHora", m_entryHora);
	m_refGlade->get_widget("entryMinutos", m_entryMinutos);
	m_refGlade->get_widget("entrySegundos", m_entrySegundos);
	m_refGlade->get_widget("calendar1", m_calendar);
	m_refGlade->get_widget("fileChooserAEnviar", m_fileChooser);

	Glib::ustring rutaArchivo = m_fileChooser->get_filename();
	if (rutaArchivo.empty()){
		std::cerr << "POPUP: NO SELECCIONASTE ARCHIVOOO\n";

		this->ventanaError("Ingrese un archivo valido!", "Error");
		return;
	}

	std::cerr << "Ruta archivo: " << rutaArchivo << "\n";

	std::tm* clock;
	struct stat attrib;

	stat(rutaArchivo.c_str(), &attrib);
	clock = gmtime(&(attrib.st_mtime));	// Get the last modified time and put it into the time structure

	this->setearFechaYHora(clock);
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

	if (horas.empty() || minutos.empty() || segundos.empty()){
		this->ventanaError("Ingrese un horario valido!", "Error");
		return;
	}

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

	if (rutaArchivo.empty()){
		this->ventanaError("Ingrese un archivo valido!", "Error");
		return;
	}

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

	if(!fila){
		this->ventanaError("Seleccione alguna area de vision!", "Error");
		return;
	}

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

	if (rutaArchivo.empty()){
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

}

void VistaEnviar::setearFechaYHora(std::tm* timer){
	std::stringstream ss;

	ss << timer->tm_hour;
	Glib::ustring hr;
	ss >> hr;
	m_entryHora->set_text(hr);

	ss.clear();
	ss << timer->tm_min;
	Glib::ustring mn;
	ss >> mn;
	m_entryMinutos->set_text(mn);

	ss.clear();
	ss << timer->tm_sec;
	Glib::ustring sec;
	ss >> sec;
	m_entrySegundos->set_text(sec);

	std::cerr << "Horas: " << timer->tm_hour << " ";
	std::cerr << "Minutos: " << timer->tm_min << " ";
	std::cerr << "Segundos: " << timer->tm_sec << "\n";

	m_calendar->select_day(timer->tm_mday);
	m_calendar->select_month(timer->tm_mon,timer->tm_year+1900);
}


/*
 * Salta una ventana con un mensaje.
 */
void VistaEnviar::ventanaError(const char* mensaje, const char* titulo){
	Gtk::Window ventanitaError;
	Gtk::MessageDialog dialog(ventanitaError,mensaje,false, Gtk::MESSAGE_ERROR);
	dialog.set_title(titulo);
	dialog.set_size_request(350,100);
	dialog.run();
	return;
}
