/*
 * AreasDeVisionComboBoxModel.h
 *
 *  Created on: Jun 14, 2015
 *      Author: ale
 */

#ifndef CLIENTE_VISTA_CLIENT_AREASDEVISIONCOMBOBOXMODEL_H_
#define CLIENTE_VISTA_CLIENT_AREASDEVISIONCOMBOBOXMODEL_H_

#include "common_AreaDeVision.h"

using common::AreaDeVision;

class AreasDeVisionComboBoxModel : public Gtk::TreeModel::ColumnRecord{
private:
    Gtk::TreeModelColumn<AreaDeVision*> columnaValor;
    //Gtk::TreeModelColumn<int> columnaValor;
    Gtk::TreeModelColumn<Glib::ustring> columnaTexto;
public:
    AreasDeVisionComboBoxModel(){
        //El modelo tendrá dos columnas: la primera con el valor entero, la segunda con el texto string unicode.
        add(columnaValor);
        add(columnaTexto);
    }
    Gtk::TreeModelColumn<AreaDeVision*>& getColumnaValor(){
    //Gtk::TreeModelColumn<int>& getColumnaValor(){
        return columnaValor;
    }
    Gtk::TreeModelColumn<Glib::ustring>& getColumnaTexto(){
        return columnaTexto;
    }
    virtual ~AreasDeVisionComboBoxModel(){}
};

/*
//Función callback para la señal changed del combo. Muestra el valor actual por salida estándar
void on_combo_changed(Gtk::ComboBox* combo, AreasDeVisionComboBoxModel* columnas){
    if (combo->get_active()){
        Gtk::TreeModel::Row fila = *combo->get_active();
        std::cout << "Elemento elegido: " << fila[columnas->getColumnaTexto()] << " con valor: " << fila[columnas->getColumnaValor()] << std::endl;
    }
}
*/

#endif /* CLIENTE_VISTA_CLIENT_AREASDEVISIONCOMBOBOXMODEL_H_ */
