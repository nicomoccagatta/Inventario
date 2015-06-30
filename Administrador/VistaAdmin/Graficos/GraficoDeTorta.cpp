#include "GraficoDeTorta.h"
#include <cairomm/context.h>
#include "PorcionCircular.h"

#define INIT_OFFSET 0.0
#define X_0     0.4
#define Y_0     0.5
#define RADIO   0.3

GraficoDeTorta::GraficoDeTorta(){
}

GraficoDeTorta::~GraficoDeTorta() {}

void GraficoDeTorta::actualizarDatos(const std::list< DatoGrafico >& datos) {
    deleteAreas();
    areas.clear();
    hallarNormalizacion(datos);

    std::list< DatoGrafico >::const_iterator itDatos = datos.begin();
    unsigned i = 0;
    double offset = INIT_OFFSET;
    for ( ; itDatos != datos.end(); ++itDatos, ++i) {
        PorcionCircular* porcion = new PorcionCircular(*itDatos, normalizacion,
                                                       i, offset,
                                                       X_0, Y_0, RADIO);
        offset = porcion->getAvance();

        areas.push_back(porcion);
    }

    regenerarReferencias();
}

void GraficoDeTorta::hallarNormalizacion(const std::list< DatoGrafico >& datos) {
    normalizacion = 0;
    std::list< DatoGrafico >::const_iterator itDatos = datos.begin();
    for ( ; itDatos != datos.end(); ++itDatos)
        normalizacion += itDatos->getValor();
}

void GraficoDeTorta::dibujarEspecializacion(GdkEventExpose* ev,
                        Cairo::RefPtr< Cairo::Context >& ctx) {}

void GraficoDeTorta::dibujarEspecializacionReferencias(
        Cairo::RefPtr< Cairo::Context >& ctx) {
    ctx->move_to(0.75, 0.1);
}

