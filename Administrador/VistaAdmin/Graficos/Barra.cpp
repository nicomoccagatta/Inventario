#include "Barra.h"

Barra::Barra(const DatoGrafico& dato, double maximo, unsigned i, double _offset,
             double separacion, double _ancho)
: Area(dato, maximo, i, _offset) {
    sep = separacion;
    ancho = _ancho;
    hasta = (dato.getValor() / max) * (0.9);
    y0 = 1.0;
    x0 = offset;
}

Barra::~Barra() {}

void Barra::dibujar(Cairo::RefPtr< Cairo::Context >& ctx) {
    ctx->save();
        set_line_width(ctx);
        ctx->set_source_rgba(color[0], color[1], color[2], color[3]);
        ctx->rectangle(x0, y0, ancho, -hasta);
        ctx->fill_preserve();
        ctx->set_source_rgba(0.0, 0.0, 0.0, 1.0);
        ctx->stroke();
    ctx->restore();
}

double Barra::getAvance() {
    return x0 + ancho + sep;
}
