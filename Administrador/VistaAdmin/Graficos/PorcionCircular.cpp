#include "PorcionCircular.h"
#include <cmath>
#include <iomanip>

PorcionCircular::PorcionCircular(const DatoGrafico& dato, double maximo, unsigned i,
                                 double _offset,double _x0, double _y0, double radio)
: Area(dato, maximo, i, _offset) {
    x0 = _x0;
    y0 = _y0;
    r = radio;
    valor =  2*M_PI*(dato.getValor()/max);
}

PorcionCircular::~PorcionCircular() {}

void PorcionCircular::dibujar(Cairo::RefPtr< Cairo::Context >& ctx) {
    ctx->save();
        set_line_width(ctx);
        ctx->set_source_rgba(color[0], color[1], color[2], color[3]);
        ctx->move_to(x0, y0);
        ctx->arc(x0, y0, r, offset, offset + valor);
        ctx->close_path();
        ctx->fill_preserve();
        ctx->set_source_rgba(0.0, 0.0, 0.0, 1.0);
        ctx->stroke();
    ctx->restore();
}

double PorcionCircular::getAvance() {
    return offset + valor;
}
