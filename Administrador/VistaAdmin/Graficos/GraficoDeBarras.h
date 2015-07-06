#ifndef GRAFICO_DE_BARRAS_H
#define GRAFICO_DE_BARRAS_H

#include "Grafico.h"

class GraficoDeBarras : public Grafico {
    void hallarNormalizacion(const std::list< DatoGrafico >& datos);
    void dibujarEspecializacion(GdkEventExpose* ev,
                    Cairo::RefPtr< Cairo::Context >& ctx);
    void dibujarEspecializacionReferencias(
            Cairo::RefPtr< Cairo::Context >& ctx);
    double separacion;
    double ancho;
    double espacio;
    unsigned datosSize;
public:
	GraficoDeBarras();
	virtual ~GraficoDeBarras();
	void actualizarDatos(const std::list< DatoGrafico >& datos);
};

#endif  // GRAFICO_DE_BARRAS_H