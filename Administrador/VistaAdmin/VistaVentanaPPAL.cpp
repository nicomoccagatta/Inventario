#include "VistaVentanaPPAL.h"

VistaVentanaPPAL::VistaVentanaPPAL(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade)
: Gtk::Window(cobject), model(0), m_refGlade(refGlade),panelDinamicoP(0),panelDinamicoAV(0),
  	  	  	  	  	  	  	  	  panelDinamicoRSG(0),panelDinamicoRAV(0),panelDinamicoRHP(0)
{
	m_refGlade->get_widget("PanelDinamicoP", panelDinamicoP);
	m_refGlade->get_widget("PanelDinamicoAV", panelDinamicoAV);
	m_refGlade->get_widget("PanelDinamicoRSG",panelDinamicoRSG);
	m_refGlade->get_widget("PanelDinamicoRAV",panelDinamicoRAV);
	m_refGlade->get_widget("PanelDinamicoRHP",panelDinamicoRHP);

	this->signal_delete_event().connect(sigc::mem_fun(*this, &VistaVentanaPPAL::on_exit_clicked) );
}

void VistaVentanaPPAL::setearAtributos(const Glib::RefPtr<Gtk::Builder>& refGlade,Modelo_Observable *modelo){
	m_refGlade = refGlade;
	model = modelo;

	model->suscribe(&vistaLP);
	model->suscribe(&vistaLAV);
	model->suscribe(&vistaRSG);
	model->suscribe(&vistaRAV);
	model->suscribe(&vistaRHP);

	model->actualizarProductos();
	vistaLP.run(panelDinamicoP,model);

	model->actualizarAreasDeVision();
	vistaLAV.run(panelDinamicoAV,model);

	vistaRSG.run(panelDinamicoRSG,model);
	vistaRAV.run(panelDinamicoRAV,model);
	vistaRHP.run(panelDinamicoRHP,model);

	this->show_all();
}

bool VistaVentanaPPAL::on_exit_clicked(GdkEventAny* event){
	Gtk::Main::quit();
	return true;
}

VistaVentanaPPAL::~VistaVentanaPPAL() {
	delete panelDinamicoP;
	delete panelDinamicoAV;
	delete panelDinamicoRSG;
	delete panelDinamicoRAV;
	delete panelDinamicoRHP;
}
