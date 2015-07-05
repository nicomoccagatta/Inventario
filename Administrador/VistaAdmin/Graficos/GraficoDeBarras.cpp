#include "GraficoDeBarras.h"
#include "Barra.h"
#include <sstream>
#include <iomanip>
#include <iostream>

#define INIT_OFFSET     		0.2
#define SEPARACION_BASE 		0.20
#define ANCHO_BASE      		0.50
#define POS_REF         		SEPARACION_BASE + ANCHO_BASE
#define MIN_SIZE        		4
#define EJE_X0          		0.04 + INIT_OFFSET/2
#define EJE_Y0          		1.0
#define CANT_PUNTOS_EJE 		10
#define ANCHO_REF_EJE   		0.02
#define ALTURA_GRAFICO_NORMA	0.9

GraficoDeBarras::GraficoDeBarras():separacion(0),ancho(0),espacio(0),datosSize(0){
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
    normalizacion = -DBL_MAX;
    std::list< DatoGrafico >::const_iterator itDatos = datos.begin();
    for ( ; itDatos != datos.end(); ++itDatos) {
    double valor = itDatos->getValor();
        if (valor > normalizacion)
            normalizacion = valor;
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
        for (int i = 1; i <= CANT_PUNTOS_EJE; ++i) {
            std::stringstream ss;
            ss << std::setfill(' ') << std::setw(4) << std::fixed << std::setprecision(0);
            punto = (double)i/CANT_PUNTOS_EJE * ALTURA_GRAFICO_NORMA;
            altura = 1.0 - punto;
            ctx->move_to(EJE_X0, altura);
            ctx->move_to(EJE_X0 - ANCHO_REF_EJE/2, altura);
            ctx->line_to(EJE_X0 + ANCHO_REF_EJE/2, altura);
            ctx->stroke();
            ctx->save();
                ctx->set_source_rgb(0.0, 0.0, 0.0);
                ctx->move_to(0.02, altura+0.01);
                ss << (double)i*normalizacion/CANT_PUNTOS_EJE;
                ctx->show_text(ss.str());
                ss.str("");
                ss.flush();
            ctx->restore();
        }

    ctx->restore();
}

void GraficoDeBarras::dibujarEspecializacionReferencias(
        Cairo::RefPtr< Cairo::Context >& ctx) {
    ctx->move_to(POS_REF, 0.1);
}

