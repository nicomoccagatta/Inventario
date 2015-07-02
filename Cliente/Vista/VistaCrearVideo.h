/*
 * VistaCrearVideo.h
 *
 *  Created on: Jun 29, 2015
 *      Author: ale
 */

#ifndef CLIENTE_VISTA_VISTACREARVIDEO_H_
#define CLIENTE_VISTA_VISTACREARVIDEO_H_

#include <gtkmm-2.4/gtkmm.h>
#include <gtkmm/viewport.h>

#include "ListaImagenesEnOrden.h"
#include "AspectPreservingScalingImage.h"
#include "ThReproductorVideo.h"

class VistaCrearVideo: public Gtk::Viewport {
public:
	VistaCrearVideo(BaseObjectType* cobject,
			const Glib::RefPtr<Gtk::Builder>& refGlade);
	virtual ~VistaCrearVideo();

private:
	void on_button_Agregar();
	void on_button_Eliminar();
	void on_imagen_seleccionada();

	void on_button_Play();
	void on_button_Pausa();
	void on_button_Stop();

	void agregarImagenALista(Glib::ustring ruta);

	void ventanaError(const char* mensaje, const char* titulo);

protected:
	Glib::RefPtr<Gtk::Builder> m_refGlade;

	Glib::RefPtr<Gtk::ListStore> m_refImagenesListStore;
	Gtk::TreeView m_ImagenesTreeView;
	Glib::RefPtr<Gtk::TreeSelection> refTreeSelection;

	Gtk::VBox verticalBox;
	Gtk::HButtonBox m_ButtonBoxAgregaryEliminar;
	Gtk::Button m_AgregarButton;
	Gtk::Button m_EliminarButton;

	Gtk::HBox hBoxListados;
	ListaImagenesEnOrden m_ImagenesList;
	Gtk::VSeparator m_Vseparator;
	Gtk::VBox labelMasVistaPreviaMasPlayStopPausa;
	Gtk::Label labelVistaPrevia;

	Gtk::HButtonBox m_ButtonBoxPlayPausaStop;
	Gtk::Button m_PlayButton;
	Gtk::Button m_PausaButton;
	Gtk::Button m_StopButton;

	Gtk::HBox hBoxFPS;
	Gtk::Label m_FPSLabel;
	Gtk::Entry m_FPSEntry;

	Gtk::VBox paraReproductor;
	ThReproductorVideo reproductor;
};

#endif /* CLIENTE_VISTA_VISTACREARVIDEO_H_ */
