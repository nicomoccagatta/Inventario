#ifndef GRAFICO_DE_TORTA_H
#define GRAFICO_DE_TORTA_H

#include "Grafico.h"

/** @class GraficoDeTorta
 * Consultante que muestra sus resultados como un gráfico de torta.
 */
class GraficoDeTorta : public Grafico {
    public:
        GraficoDeTorta();
        virtual ~GraficoDeTorta();

        void actualizarDatos(const std::list< DatoGrafico >& datos);
    private:
        void hallarNormalizacion(const std::list< DatoGrafico >& datos);
        void dibujarEspecializacion(GdkEventExpose* ev,
                        Cairo::RefPtr< Cairo::Context >& ctx);
        void dibujarEspecializacionReferencias(
                Cairo::RefPtr< Cairo::Context >& ctx);
};

#endif  // GRAFICO_DE_TORTA_H
