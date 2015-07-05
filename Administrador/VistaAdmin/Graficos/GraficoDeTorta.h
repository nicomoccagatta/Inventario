#ifndef GRAFICO_DE_TORTA_H
#define GRAFICO_DE_TORTA_H

#include "Grafico.h"

class GraficoDeTorta : public Grafico {
	void hallarNormalizacion(const std::list< DatoGrafico >& datos);
	void dibujarEspecializacion(GdkEventExpose* ev,
                    Cairo::RefPtr< Cairo::Context >& ctx);
	void dibujarEspecializacionReferencias(
            Cairo::RefPtr< Cairo::Context >& ctx);
public:
    GraficoDeTorta();
	virtual ~GraficoDeTorta();
	void actualizarDatos(const std::list< DatoGrafico >& datos);
};

#endif  // GRAFICO_DE_TORTA_H
