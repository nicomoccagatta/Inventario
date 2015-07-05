#ifndef ADMINISTRADOR_VISTAADMIN_VISTAEDITARAREAVISION_H_
#define ADMINISTRADOR_VISTAADMIN_VISTAEDITARAREAVISION_H_

#include <gtkmm-2.4/gtkmm.h>
#include "ModeloAdmin/admin_ModeloObservable.h"
#include "TiposCapturadorComboBoxModel.h"

class VistaEditarAreaVision : public Gtk::Window {
	void on_button_OK();
	void on_button_CANCEL();

	Modelo_Observable *modelo;

	Gtk::VBox m_VBoxPrincipal;

	Gtk::HBox m_hBoxUbicacion;
	Gtk::Label m_labelUbicacion;
	Gtk::Entry m_obtenerUbicacion;

	Gtk::HBox m_hBoxCapturador;
	Gtk::Label m_labelCapturador;
	Gtk::ComboBox m_TiposCapturador;
	TiposCapturadorComboBoxModel columnas;
	Glib::RefPtr<Gtk::ListStore> modeloComboBox;

	Gtk::HButtonBox m_botoneraBotonOK;
	Gtk::Button m_ButtonCrearAV;
	Gtk::Button m_ButtonCANCEL;

	unsigned long int idAV;
public:
	VistaEditarAreaVision(Modelo_Observable *model,unsigned long int id,std::string& ubicacion,std::string capturador);
	virtual ~VistaEditarAreaVision();
};

#endif /* ADMINISTRADOR_VISTAADMIN_VISTAEDITARAREAVISION_H_ */
