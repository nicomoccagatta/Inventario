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
#include "ThReproductorVideo.h"
#include "common_Mutex.h"

/*
 * La vista sirve para anadir imagenes a la ListStore y luego reproducirlas
 * en orden descendiente. Tiene un ThReproductor para reproducir el video.
 */
class VistaCrearVideo: public Gtk::Viewport {

	ThReproductorVideo reproductor;

	common::Mutex mutex;
	pthread_cond_t cond;

public:
	VistaCrearVideo(BaseObjectType* cobject,
			const Glib::RefPtr<Gtk::Builder>& refGlade);
	virtual ~VistaCrearVideo();

private:
	/*
	 * Agrega una o varias imagenes al ListStore.
	 */
	void on_button_Agregar();
	/*
	 * Remueve la imagen seleccionada del ListStore.
	 */
	void on_button_Eliminar();
	/*
	 * Al seleccionar una imagen, se muestra en el Box.
	 */
	void on_imagen_seleccionada();
	/*
	 * Al iniciar un drag, se saca la imagen que se selecciono.
	 */
	void on_my_drag_begin(const Glib::RefPtr<Gdk::DragContext>& context);
	/*
	 * Al finalizar un drag, se actualiza la lista de frames del reproductor
	 * con el nuevo orden.
	 */
	void on_my_drag_end(const Glib::RefPtr<Gdk::DragContext>& context);

	/*
	 * Broadcastea al reproductor la variable cond para que se levante.
	 * Antes setea las FPS.
	 */
	void on_button_Play();

	/*
	 * Detiene la reproduccion.
	 */
	void on_button_Pausa();

	/*
	 * Detiene la reproduccion y vuelve al inicio al volver a reproducir.
	 */
	void on_button_Stop();

	/*
	 * Interfaz para descargar el video de acuerdo a las imagenes en orden
	 * descendiente y las FPS ingresadas.
	 */
	void on_button_Descargar();

	void agregarImagenALista(Glib::ustring ruta);

	void actualizarFramesReproductor();

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
	Gtk::Button m_DescargarButton;

	Gtk::Image* activaAlSeleccionar;

	Gtk::VBox paraReproductor;
};

#endif /* CLIENTE_VISTA_VISTACREARVIDEO_H_ */
