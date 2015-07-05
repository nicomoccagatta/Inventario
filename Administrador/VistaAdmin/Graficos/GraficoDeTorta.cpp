#include "GraficoDeTorta.h"
#include <cairomm/context.h>
#include "PorcionCircular.h"

GraficoDeTorta::GraficoDeTorta(){
}

GraficoDeTorta::~GraficoDeTorta() {}

void GraficoDeTorta::actualizarDatos(const std::list< DatoGrafico >& datos) {
    deleteAreas();
    areas.clear();
    hallarNormalizacion(datos);

    std::list< DatoGrafico >::const_iterator itDatos = datos.begin();
    unsigned i = 0;
    double offset = 0.0;
    for ( ; itDatos != datos.end(); ++itDatos, ++i) {
        PorcionCircular* porcion = new PorcionCircular(*itDatos, normalizacion,
                                                    i, offset,0.4,0.5,0.3);
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

