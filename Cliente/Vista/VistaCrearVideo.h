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

class VistaCrearVideo: public Gtk::Viewport {
public:
	VistaCrearVideo(BaseObjectType* cobject,
			const Glib::RefPtr<Gtk::Builder>& refGlade);
	virtual ~VistaCrearVideo();

private:
	Glib::RefPtr<Gtk::Builder> m_refGlade;
};

#endif /* CLIENTE_VISTA_VISTACREARVIDEO_H_ */
