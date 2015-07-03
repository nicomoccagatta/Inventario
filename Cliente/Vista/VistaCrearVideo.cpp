/*
 * VistaCrearVideo.cpp
 *
 *  Created on: Jun 29, 2015
 *      Author: ale
 */

#include <iostream>
#include <sstream>

#include "VistaCrearVideo.h"


VistaCrearVideo::VistaCrearVideo(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade)
: Gtk::Viewport(cobject),
  	  m_refGlade(refGlade),
	  activaAlSeleccionar(), labelMasVistaPreviaMasPlayStopPausa(false),
	  paraReproductor(true), reproductor(&paraReproductor){

	std::cerr << "CREANDO VISTA CREARVIDEO\n";
	//Botones Agregar y Eliminar
	m_AgregarButton.set_label("Agregar");
	m_AgregarButton.signal_clicked().connect( sigc::mem_fun(*this, &VistaCrearVideo::on_button_Agregar));

	m_EliminarButton.set_label("Eliminar");
	m_EliminarButton.signal_clicked().connect( sigc::mem_fun(*this, &VistaCrearVideo::on_button_Eliminar) );

	m_ButtonBoxAgregaryEliminar.pack_start(m_AgregarButton);
	m_ButtonBoxAgregaryEliminar.pack_start(m_EliminarButton);
	m_ButtonBoxAgregaryEliminar.set_layout(Gtk::BUTTONBOX_START);

	verticalBox.pack_start(m_ButtonBoxAgregaryEliminar,Gtk::PACK_SHRINK,true,0);

	//Lista de Imagenes
	m_ImagenesList.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
	m_ImagenesList.set_size_request(150,400);
	m_ImagenesList.add(m_ImagenesTreeView);

	std::cerr << "CREANDO IMAGENES LIST STORE\n";

	m_refImagenesListStore = Gtk::ListStore::create(m_ImagenesList.m_Columns);
	m_ImagenesTreeView.set_model(m_refImagenesListStore);

	m_ImagenesTreeView.append_column("Imagen", m_ImagenesList.m_Columns.m_col_imagenIcono);
	m_ImagenesTreeView.append_column("Nombre archivo", m_ImagenesList.m_Columns.m_col_nombre);
	m_ImagenesTreeView.append_column("Ruta", m_ImagenesList.m_Columns.m_col_ruta);
	m_ImagenesTreeView.set_reorderable();

	//Conecto la senial de cuando se selecciona alguna de la lista
	refTreeSelection = m_ImagenesTreeView.get_selection();
	refTreeSelection->signal_changed().connect(
			    sigc::mem_fun(*this, &VistaCrearVideo::on_imagen_seleccionada) );
	m_ImagenesTreeView.signal_drag_end().connect(
		    sigc::mem_fun(*this, &VistaCrearVideo::on_my_drag_end) );
	m_ImagenesTreeView.signal_drag_begin().connect(
		    sigc::mem_fun(*this, &VistaCrearVideo::on_my_drag_begin) );

	hBoxListados.pack_start(m_ImagenesList);
	//labelMasVistaPreviaMasPlayStopPausa.set_size_request(400,Gtk::EXPAND);
	hBoxListados.pack_start(m_Vseparator);
	hBoxListados.pack_end(labelMasVistaPreviaMasPlayStopPausa);

	//Agrego el box en el que se va a mostrar la imagen al box que va a tener la
	//vista y los botones
	labelMasVistaPreviaMasPlayStopPausa.pack_start(paraReproductor,true,true);

	//Creo botones y conecto sus senales
	m_PlayButton.set_label("Play");
	m_PlayButton.signal_clicked().connect( sigc::mem_fun(*this, &VistaCrearVideo::on_button_Play));

	m_PausaButton.set_label("Pausa");
	m_PausaButton.signal_clicked().connect( sigc::mem_fun(*this, &VistaCrearVideo::on_button_Pausa) );

	m_StopButton.set_label("Stop");
	m_StopButton.signal_clicked().connect( sigc::mem_fun(*this, &VistaCrearVideo::on_button_Stop) );


	m_FPSLabel.set_text("FPS: ");
	m_FPSEntry.set_max_length(6);
	m_FPSEntry.set_width_chars(6);
	hBoxFPS.pack_start(m_FPSLabel,false,false);
	hBoxFPS.pack_start(m_FPSEntry,false,false,10);
	labelMasVistaPreviaMasPlayStopPausa.pack_end(hBoxFPS);

	m_ButtonBoxPlayPausaStop.pack_start(m_PlayButton);
	m_ButtonBoxPlayPausaStop.pack_start(m_PausaButton);
	m_ButtonBoxPlayPausaStop.pack_start(m_StopButton);
	m_ButtonBoxPlayPausaStop.set_layout(Gtk::BUTTONBOX_SPREAD);
	labelMasVistaPreviaMasPlayStopPausa.pack_end(m_ButtonBoxPlayPausaStop,false,false);

	verticalBox.pack_end(hBoxListados);

	add(verticalBox);
	show_all_children();

	pthread_cond_init(&cond,NULL);

	reproductor.setMutex(this->mutex, &(this->cond));

	reproductor.start();
}

VistaCrearVideo::~VistaCrearVideo() {
	reproductor.matar();
	pthread_cond_broadcast(&cond); //para que salga del bloqueo
	std::cerr << "JOINEO\n";
	reproductor.join();


	pthread_cond_destroy(&cond);


	Gtk::TreeModel::Children children = m_refImagenesListStore->children();
	Gtk::TreeModel::Children::iterator it;

	/*Libero las imagenes*/
	for(it=children.begin(); it != children.end(); ++it){
		Gtk::TreeModel::Row row = *it;
		if (row[m_ImagenesList.m_Columns.m_col_imgGrande])
			delete row[m_ImagenesList.m_Columns.m_col_imgGrande];

	}
}

void VistaCrearVideo::on_button_Agregar(){
	/*Abro el dialogo para elegir archivo*/
	Gtk::FileChooserDialog dialog("Elige una imagen",
			Gtk::FILE_CHOOSER_ACTION_OPEN);

	dialog.set_select_multiple(true);

	//Add response buttons the the dialog:
	dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
	dialog.add_button("Select", Gtk::RESPONSE_OK);

	int result = dialog.run();

	//Handle the response:
	switch(result){
	case(Gtk::RESPONSE_OK):{
		Glib::SListHandle<Glib::ustring> nombres = dialog.get_filenames();
		Glib::SListHandle<Glib::ustring>::iterator it = nombres.begin();

		for(;it!=nombres.end();++it){
			//std::cerr << "File selected: " << *it << std::endl;
			//Agrego la imagen al listado
			this->agregarImagenALista(*it);
		}
		break;
	}
	case(Gtk::RESPONSE_CANCEL):{
		std::cerr << "Cancel clicked." << std::endl;
		return;
	}
	default:{
		std::cerr << "Exit(?) button clicked." << std::endl;
		return;
	}
	}
	/*Actualizo los frames del reproductor*/
	mutex.bloquear();
	this->actualizarFramesReproductor();
	mutex.desbloquear();
}

void VistaCrearVideo::actualizarFramesReproductor(){
	Gtk::TreeModel::Children children = m_refImagenesListStore->children();
	Gtk::TreeModel::Children::iterator it;

	std::vector< Gtk::Image* > frames;
	std::vector<Glib::ustring> rutaFrames;

	for(it=children.begin(); it != children.end(); ++it){
		Gtk::TreeModel::Row row = *it;
		frames.push_back((row[m_ImagenesList.m_Columns.m_col_imgGrande]));
		rutaFrames.push_back((row[m_ImagenesList.m_Columns.m_col_ruta]));
	}
	reproductor.setearFrames(frames);
}

/*
 * Agrega la imagen al listado, excalada a 1/8 de su tamano original.
 */
void VistaCrearVideo::agregarImagenALista(Glib::ustring rutaCompleta){
	mutex.bloquear();

	std::stringstream iss(rutaCompleta);
	std::string nombre;

	while(std::getline(iss, nombre, '/'));

	std::cerr << "EL NOMBRE ES: " << nombre
			<< "\nLA RUTA COMPLETA: " << rutaCompleta << "\n";

	Gtk::TreeModel::Row row = *(m_refImagenesListStore->append());
	Glib::RefPtr<Gdk::Pixbuf>  icon = Gdk::Pixbuf::create_from_file(rutaCompleta,30,30,false);
	Gtk::Image* image = new Gtk::Image(Gdk::Pixbuf::create_from_file(rutaCompleta,400,300,true));

	row[m_ImagenesList.m_Columns.m_col_imagenIcono] = icon;
	row[m_ImagenesList.m_Columns.m_col_nombre] = nombre;
	row[m_ImagenesList.m_Columns.m_col_ruta] = rutaCompleta;
	row[m_ImagenesList.m_Columns.m_col_imgGrande] = image;

	mutex.desbloquear();
}

/*
 * Elimina la imagen del listado
 */
void VistaCrearVideo::on_button_Eliminar(){
	mutex.bloquear();
	/*Seguramente cuando la seleccione se puso como activa*/
	if (this->activaAlSeleccionar){
			this->paraReproductor.remove(*activaAlSeleccionar);
			this->activaAlSeleccionar = 0;
	}

	Gtk::TreeModel::iterator iter = refTreeSelection->get_selected();
	Gtk::TreeModel::Row row = *iter;
	if(iter){ //If anything is selected
		/*Libero la Imagen*/
		if (row[m_ImagenesList.m_Columns.m_col_imgGrande])
			delete row[m_ImagenesList.m_Columns.m_col_imgGrande];

		m_refImagenesListStore->erase(iter);
	}
	/*Actualizo los frames (sin la que se elimino)*/
	this->actualizarFramesReproductor();
	mutex.desbloquear();
}

/*
 * Al seleccionar una imagen de la lista, esta se muestra en el box. La idea es
 * que si se apreta play continua desde ahi.
 */
void VistaCrearVideo::on_imagen_seleccionada(){
	//BOLQUEAR MUTEX
	mutex.bloquear();

	if (reproductor.estaPausado())
		reproductor.sacarImagenPausada();

	if (this->activaAlSeleccionar)
		this->paraReproductor.remove(*activaAlSeleccionar);

	Gtk::TreeModel::iterator iter = refTreeSelection->get_selected();
	if(iter){ //If anything is selected
		Gtk::TreeModel::Row row = *iter;

		this->paraReproductor.pack_start(
				*row[m_ImagenesList.m_Columns.m_col_imgGrande]);

		this->activaAlSeleccionar = row[m_ImagenesList.m_Columns.m_col_imgGrande];
		this->activaAlSeleccionar->show_now();
	}
	mutex.desbloquear();
}

/*
 * Si se cambia el orden de la visa se tiene que cambiar el orden del video.
 */
void VistaCrearVideo::on_my_drag_begin(const Glib::RefPtr<Gdk::DragContext>& context){
	mutex.bloquear();

	std::cerr << "ARRANCA EL DRAG\n";
	/*Seguramente cuando la seleccione se puso como activa*/
	if (this->activaAlSeleccionar){
		this->paraReproductor.remove(*activaAlSeleccionar);
		this->activaAlSeleccionar = 0;
	}
	mutex.desbloquear();
}
/*
 * Si se cambia el orden de la visa se tiene que cambiar el orden del video.
 */
void VistaCrearVideo::on_my_drag_end(const Glib::RefPtr<Gdk::DragContext>& context){
	std::cerr << "TERMINO EL DRAG\n";
	this->actualizarFramesReproductor();
}

/*
 * Reproduce la secuencia de imagenes desde donde se pauso por ultima vez o desde
 * el principio, por ahora.
 */
void VistaCrearVideo::on_button_Play(){
	//Si habia una imagen por seleccionar, la saco antes
	if (this->activaAlSeleccionar){
		this->paraReproductor.remove(*activaAlSeleccionar);
		this->activaAlSeleccionar = 0;
	}
/*
	if(reproductor.estaVivo()){
		std::cerr << "JOINEO\n";
		reproductor.join();
	}
*/
	std::stringstream ss;
	ss << m_FPSEntry.get_text();
	double f=0;
	ss >> f;

	if (f<=0)
		return this->ventanaError("Ingresa las FPS!", "Error");
	if (f>50)
		return this->ventanaError("Imposible tantos FPS!", "Error");

	reproductor.setFPS(f);

	mutex.bloquear();
	pthread_cond_broadcast(&cond);
	mutex.desbloquear();
}

void VistaCrearVideo::on_button_Pausa(){
	reproductor.pausa();
}

void VistaCrearVideo::on_button_Stop(){
	//mutex.desbloquear();
	//cond = true;
}

/*
 * Salta una ventana con un mensaje.
 */
void VistaCrearVideo::ventanaError(const char* mensaje, const char* titulo){
	Gtk::Window ventanitaError;
	Gtk::MessageDialog dialog(ventanitaError,mensaje,false, Gtk::MESSAGE_ERROR);
	dialog.set_title(titulo);
	dialog.set_size_request(350,100);
	dialog.run();
	return;
}
