#ifndef GRAFICO_DE_TORTA_H
#define GRAFICO_DE_TORTA_H

#include "Grafico.h"

class GraficoDeTorta : public Grafico {
	/*
	 * establece el valor de la normalizacion del grafico
	 */
	void hallarNormalizacion(const std::list< DatoGrafico >& datos);

	/*
	 * Dibujaria el eje, pero no hace falta un eje en este grafico
	 */
	void dibujarEspecializacion(GdkEventExpose* ev,
                    Cairo::RefPtr< Cairo::Context >& ctx);

	/*
	 * Mueve el puntero del contexto al comienzo de las referencias
	 */
	void dibujarEspecializacionReferencias(
            Cairo::RefPtr< Cairo::Context >& ctx);
public:
    GraficoDeTorta();
	virtual ~GraficoDeTorta();

	/*
	 * actualiza los datos a graficar, borrando los datos anteriores, y
	 * estableciendo los ingresados por parametro en argumento datos.
	 */
	void actualizarDatos(const std::list< DatoGrafico >& datos);
};

#endif  // GRAFICO_DE_TORTA_H
