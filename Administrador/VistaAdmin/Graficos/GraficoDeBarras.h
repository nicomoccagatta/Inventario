#ifndef GRAFICO_DE_BARRAS_H
#define GRAFICO_DE_BARRAS_H

#include "Grafico.h"

class GraficoDeBarras : public Grafico {
	/*
	 * establece el valor de la normalizacion del grafico
	 */
    void hallarNormalizacion(const std::list< DatoGrafico >& datos);

	/*
	 * Dibuja el eje, y los valores sobre eje cartesiano y
	 */
    void dibujarEspecializacion(GdkEventExpose* ev,
                    Cairo::RefPtr< Cairo::Context >& ctx);

	/*
	 * Mueve el puntero del contexto al comienzo de las referencias
	 */
    void dibujarEspecializacionReferencias(
            Cairo::RefPtr< Cairo::Context >& ctx);

    double separacion;
    double ancho;
    double espacio;
    unsigned datosSize;
public:
	GraficoDeBarras();
	virtual ~GraficoDeBarras();

	/*
	 * actualiza los datos a graficar, borrando los datos anteriores, y
	 * estableciendo los ingresados por parametro en argumento datos.
	 */
	void actualizarDatos(const std::list< DatoGrafico >& datos);
};

#endif  // GRAFICO_DE_BARRAS_H
