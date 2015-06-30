/*
 * VistaCrearVideo.cpp
 *
 *  Created on: Jun 29, 2015
 *      Author: ale
 */

#include "VistaCrearVideo.h"

VistaCrearVideo::VistaCrearVideo(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade)
: Gtk::Viewport(cobject),
  	  m_refGlade(refGlade){
	// TODO Auto-generated constructor stub

}

VistaCrearVideo::~VistaCrearVideo() {
	// TODO Auto-generated destructor stub
}

