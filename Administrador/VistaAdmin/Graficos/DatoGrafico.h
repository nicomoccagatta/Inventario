#ifndef DATOGRAFICO_H
#define DATOGRAFICO_H

#include <glibmm/ustring.h>

class DatoGrafico {
    public:
        /**
         * Constructor copia.
         * @param original el otro Hecho
         */
		DatoGrafico(const DatoGrafico& original);
        /**
         * Constructor.
         * @param etiqueta nombre del dato del área referente
         * @param valor valor del dato del área referente
         */
		DatoGrafico(const Glib::ustring& etiqueta, double valor);
        ~DatoGrafico();

        DatoGrafico& operator=(const DatoGrafico& original);

        const Glib::ustring& getEtiqueta() const;
        double getValor() const;
    private:
        Glib::ustring etiqueta;
        double valor;
};

#endif  // DATOGRAFICO_H
