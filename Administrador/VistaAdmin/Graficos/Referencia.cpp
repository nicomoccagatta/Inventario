#include "Referencia.h"
#include "Area.h"
#include "Grafico.h"

double Referencia::anchoCuadradito = 0.03;

Referencia::Referencia(const Area& referente) {
    etiqueta = referente.getEtiqueta();
    const double* refColor = referente.getColor();
    for (unsigned i = 0; i < 4; ++i)
        color[i] = refColor[i];

    font = Cairo::FONT_WEIGHT_NORMAL;
}

Referencia::~Referencia() {}

void Referencia::setNegrita(bool estado) {
    if (estado)
        font = Cairo::FONT_WEIGHT_BOLD;
    else
        font = Cairo::FONT_WEIGHT_NORMAL;
}

double Referencia::dibujar(Cairo::RefPtr< Cairo::Context >& ctx,
                           double offset) {
    ctx->save();
        double x, y;
        ctx->set_source_rgba(color[0], color[1], color[2], color[3]);
        ctx->get_current_point(x, y);
        ctx->rectangle(x, y+offset, anchoCuadradito, -anchoCuadradito);
        ctx->fill();
        ctx->set_source_rgba(0.0, 0.0, 0.0, 1.0);
        ctx->move_to(x + 1.5*anchoCuadradito, y+offset);
        ctx->set_font_size(anchoCuadradito);
        ctx->select_font_face("sans-serif", Cairo::FONT_SLANT_NORMAL, font);
        ctx->show_text(etiqueta);
    ctx->restore();
    return offset + 1.5*anchoCuadradito;
}
