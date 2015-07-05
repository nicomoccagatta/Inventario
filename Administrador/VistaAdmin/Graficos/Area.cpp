#include "Area.h"
#include "DatoGrafico.h"

#define MAX_VALORES 15

double Area::colores[MAX_VALORES][4] = {
	{0.77, 0.2, 0.4, 1.0}, {0.4, 0.77, 0.2, 1.0}, {0.4, 0.3, 0.77, 1.0},
    {0.4, 0.67, 0.9, 1.0}, {0.9, 0.67, 0.4, 1.0}, {0.9, 0.4, 0.67, 1.0},
    {0.22, 0.2, 0.4, 1.0}, {0.4, 0.22, 0.2, 1.0}, {0.2, 0.4, 0.22, 1.0},
    {0.99, 0.3, 0.9, 1.0}, {0.1, 0.9, 0.99, 1.0}, {0.4, 0.9, 0.99, 1.0},
	{0.7, 0.3, 0.77, 1.0}, {0.1, 0.7, 0.77, 1.0}, {0.4, 0.9, 0.77, 1.0},
};

Area::Area(const DatoGrafico& _dato, double maximo, unsigned i, double _offset)
: dato(_dato) {
    lineWidth = 0.01;
    offset = _offset;
    max = maximo;
    unsigned color_i = i % MAX_VALORES;
    for (unsigned j = 0; j < 4; ++j)
        color[j] = colores[color_i][j];
}

Area::~Area() {}

const Glib::ustring& Area::getEtiqueta() const {
    return dato.getEtiqueta();
}

const double* Area::getColor() const {
    return color;
}

void Area::set_line_width(Cairo::RefPtr< Cairo::Context >& ctx) {
    ctx->set_line_width(lineWidth);
}
