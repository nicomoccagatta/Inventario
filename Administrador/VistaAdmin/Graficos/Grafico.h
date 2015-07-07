#ifndef GRAFICO_H
#define GRAFICO_H

#include <list>
#include <gtkmm-2.4/gtkmm.h>
#include "DatoGrafico.h"
#include "Referencia.h"
#include "Area.h"

class Grafico : public Gtk::DrawingArea {
public:
	Grafico();
	virtual ~Grafico();

	/*
	 * Sirve para refrescar el grafico en pantalla
	 */
	void redibujar();
protected:
	/*
	 * Metodo para establecer el parametro normalizacion de los graficos.
	 * Redefinido por clases hijas.
	 */
	virtual void hallarNormalizacion(const std::list<DatoGrafico>& datos) = 0;

	/*
	 * borra y regenera todas las areas
	 */
	void deleteAreas();

	/*
	 * borra y regenera todas las referencias
	 */
	void regenerarReferencias();

	/*
	 * Mueve el puntero del contexto a la posicion inicial de las referencias.
	 * Redefinido por clases hijas.
	 */
	virtual void dibujarEspecializacionReferencias(
                Cairo::RefPtr< Cairo::Context >& ctx) = 0;

	/*
	 * itera por las áreas y las grafica donde esté puesto el contexto
	 */
	void dibujarAreas(Cairo::RefPtr< Cairo::Context >& ctx);

	/*
	 * itera por las referencias y las grafica donde esté puesto el contexto
	 */
	void dibujarReferencias(Cairo::RefPtr< Cairo::Context >& ctx);

	/*
	 * Dibuja los la especializacion de los graficos.
	 * (ejes en GraficoDeBarras y nada en GraficoDeTorta)
	 */
	virtual void dibujarEspecializacion(GdkEventExpose* ev,
                        Cairo::RefPtr< Cairo::Context >& ctx) = 0;

	/*
	 *  Regrafica todo el widget
	 */
	bool on_expose_event(GdkEventExpose* ev);

	/*
	 * actualiza los datos del gráfico. Redefinido por clases hijas.
	 */
	virtual void actualizarDatos(const std::list< DatoGrafico >& datos) = 0;

	/*
	 * En caso de que el grafico necesite mas espacio, se actualizan las
	 * variables furthest_x, furthest_y para estirar la ventana
	 */
	void actualizarTamanioMinimo(double x, double y);

	/*
	 * en caso de que la booleana should_request_size sea verdadera
	 * se actualiza el tamaño del DrawingArea para que el grafico entre
	 */
	void resize();

	std::list< Referencia > referencias;
	std::list< Area* > areas;
	int ancho_ventana;
	int alto_ventana;
	int min_lado;
	bool should_request_size;
	double furthest_x, furthest_y;
	double normalizacion;
};
#endif  // GRAFICO_H
