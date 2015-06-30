#include "GraficoDeBarras.h"
#include "Barra.h"
#include <sstream>
#include <iomanip>

#define INIT_OFFSET     0.2
#define SEPARACION_BASE 0.20
#define ANCHO_BASE      0.50
#define POS_REF         SEPARACION_BASE + ANCHO_BASE
#define MIN_SIZE        4
#define EJE_X0          0.04 + INIT_OFFSET/2
#define EJE_Y0          1.0
#define CANT_PUNTOS_EJE 10
#define ANCHO_REF_EJE   0.02

GraficoDeBarras::GraficoDeBarras() {
    normalizacion = -DBL_MAX;
}

GraficoDeBarras::~GraficoDeBarras() {}

void GraficoDeBarras::actualizarDatos(const std::list< DatoGrafico >& datos) {
    deleteAreas();
    areas.clear();
    hallarNormalizacion(datos);

    datosSize = datos.size();
    if (datosSize < MIN_SIZE)
        datosSize = MIN_SIZE;

    espacio = POS_REF - INIT_OFFSET;
    ancho = (espacio/datosSize) * ANCHO_BASE/(POS_REF);
    separacion = (espacio/datosSize) * SEPARACION_BASE/(POS_REF);

    std::list< DatoGrafico >::const_iterator itDatos = datos.begin();
    unsigned i = 0;
    double offset = INIT_OFFSET;
    for ( ; itDatos != datos.end(); ++itDatos, ++i) {
        Barra* barra = new Barra(*itDatos, normalizacion, i, offset,
                                  separacion, ancho);
        offset = barra->getAvance();
        areas.push_back(barra);
    }

    regenerarReferencias();
}

void GraficoDeBarras::hallarNormalizacion(const std::list< DatoGrafico >& datos) {
    std::list< DatoGrafico >::const_iterator itDatos = datos.begin();
    normalizacion = -DBL_MAX;
    double siguiente = itDatos->getValor();
    for ( ; itDatos != datos.end(); ++itDatos) {
        if (siguiente > normalizacion)
            normalizacion = siguiente;
        siguiente = itDatos->getValor();
    }
}

void GraficoDeBarras::dibujarEspecializacion(GdkEventExpose* ev,
                        Cairo::RefPtr< Cairo::Context >& ctx) {
    if (normalizacion == -DBL_MAX)
        return;

    ctx->save();
        ctx->set_antialias(Cairo::ANTIALIAS_NONE);
        ctx->set_source_rgb(0.75, 0.75, 0.75);
        ctx->set_line_width(0.01);

        // dibujar ejes
        ctx->move_to(POS_REF, EJE_Y0);
        ctx->line_to(EJE_X0, EJE_Y0);
        ctx->line_to(EJE_X0, 0.1);
        ctx->stroke();

        // dibujar algunos puntos en el eje Y
        ctx->set_line_width(0.005);
        ctx->set_antialias(Cairo::ANTIALIAS_DEFAULT);
        ctx->set_line_cap(Cairo::LINE_CAP_ROUND);
        ctx->set_font_size(0.03);
        double punto, altura;
        std::stringstream ss;
        ss << std::setfill(' ') << std::setw(7) << std::fixed << std::setprecision(2);
        for (int i = 1; i < CANT_PUNTOS_EJE - 1; ++i) {
            punto = (double)i/CANT_PUNTOS_EJE;
            altura = 1.0 - punto;
            ctx->move_to(EJE_X0, altura);
            ctx->move_to(EJE_X0 - ANCHO_REF_EJE/2, altura);
            ctx->line_to(EJE_X0 + ANCHO_REF_EJE/2, altura);
            ctx->stroke();
            ctx->save();
                ctx->set_source_rgb(0.0, 0.0, 0.0);
                ctx->move_to(0.0, altura);
                ss << punto*normalizacion;
                ctx->show_text(ss.str());
                ss.str("");
            ctx->restore();
        }

    ctx->restore();
}

void GraficoDeBarras::dibujarEspecializacionReferencias(
        Cairo::RefPtr< Cairo::Context >& ctx) {
    ctx->move_to(POS_REF, 0.1);
}

