#include "VistaEditarAreaVision.h"

VistaEditarAreaVision::VistaEditarAreaVision(Modelo_Observable *model,unsigned long int id,std::string& ubicacion,std::string capturador): modelo(model), idAV(id) {
	this->set_size_request(500,150);
	this->set_title("Editar Area de Vision");
	this->set_position(Gtk::WIN_POS_CENTER);
	this->set_resizable(false);

	m_labelUbicacion.set_text("Ubicacion:");
	m_labelUbicacion.set_size_request(150,30);
	m_hBoxUbicacion.pack_start(m_labelUbicacion);
	m_obtenerUbicacion.set_size_request(350,30);
	m_obtenerUbicacion.set_text(ubicacion);
	m_hBoxUbicacion.pack_end(m_obtenerUbicacion);

	m_VBoxPrincipal.pack_start(m_hBoxUbicacion);

	m_labelCapturador.set_text("Tipo de Capturador:");
	m_labelCapturador.set_size_request(150,30);
	m_hBoxCapturador.pack_start(m_labelCapturador);

	modeloComboBox = Gtk::ListStore::create(columnas);
	m_TiposCapturador.set_model(modeloComboBox);
	Gtk::TreeModel::Row fila = *modeloComboBox->append();
	fila[columnas.getColumnaCapturador()] = "Foto";
	fila = *(modeloComboBox->append());
	fila[columnas.getColumnaCapturador()] = "Video";
	m_TiposCapturador.pack_start(columnas.getColumnaCapturador());
	m_TiposCapturador.set_size_request(350,30);
	if (capturador == "Foto" || capturador == "foto")
		m_TiposCapturador.set_active(0);
	else if(capturador == "Video" || capturador == "video")
		m_TiposCapturador.set_active(1);
	m_hBoxCapturador.pack_end(m_TiposCapturador);

	m_VBoxPrincipal.pack_start(m_hBoxCapturador);

	m_ButtonCrearAV.set_label("OK");
	m_ButtonCrearAV.signal_clicked().connect( sigc::mem_fun(*this, &VistaEditarAreaVision::on_button_OK));
	m_botoneraBotonOK.pack_start(m_ButtonCrearAV);
	m_ButtonCANCEL.set_label("CANCEL");
	m_ButtonCANCEL.signal_clicked().connect( sigc::mem_fun(*this, &VistaEditarAreaVision::on_button_CANCEL));
	m_botoneraBotonOK.pack_start(m_ButtonCANCEL);
	m_botoneraBotonOK.set_layout(Gtk::BUTTONBOX_CENTER);
	m_VBoxPrincipal.pack_end(m_botoneraBotonOK);

	this->signal_delete_event().connect(sigc::mem_fun(*this, &VistaEditarAreaVision::on_exit_clicked) );

	this->add(m_VBoxPrincipal);
	this->show_all();
}

VistaEditarAreaVision::~VistaEditarAreaVision() {
}

void VistaEditarAreaVision::on_button_OK(){
	if( m_obtenerUbicacion.get_text() == "" ){
		Gtk::Window *ventanitaError = new Gtk::Window;
		Gtk::MessageDialog dialog(*ventanitaError,"Ingrese Ubicacion",false, Gtk::MESSAGE_ERROR);
		dialog.set_title("Error Ubicacion");
		dialog.set_size_request(350,100);
		dialog.run();
		return;
	}
	if( m_TiposCapturador.get_active_row_number() == (-1) ){
		Gtk::Window *ventanitaError = new Gtk::Window;
		Gtk::MessageDialog dialog(*ventanitaError,"Seleccione Tipo de Capturador",false, Gtk::MESSAGE_ERROR);
		dialog.set_title("Error Tipo Capturador");
		dialog.set_size_request(350,100);
		dialog.run();
		return;
	}
	Gtk::TreeModel::Row fila = *m_TiposCapturador.get_active();
	Glib::ustring tCapturador = fila[columnas.getColumnaCapturador()];
	std::string capturador = tCapturador;
	std::string ubicacion = m_obtenerUbicacion.get_text();
	this->modelo->modificarAreaVision(idAV,ubicacion,capturador);

	Gtk::Window *ventanitaOK = new Gtk::Window;
	Gtk::MessageDialog dialog(*ventanitaOK,"Area de Vision modificada correctamente!",false, Gtk::MESSAGE_INFO);
	dialog.set_title("Operacion Exitosa");
	dialog.set_size_request(370,100);
	dialog.run();

	modelo->notify();
	delete this;
}

void VistaEditarAreaVision::on_button_CANCEL(){
	delete this;
}

bool VistaEditarAreaVision::on_exit_clicked(GdkEventAny* event){
	delete this;
	return true;
}
