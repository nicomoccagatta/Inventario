/*
 * AreasDeVisionComboBoxModel.h
 *
 *  Created on: Jun 14, 2015
 *      Author: ale
 */

#ifndef CLIENTE_VISTA_CLIENT_MODELCOMBOBOXAREASDEVISION_H_
#define CLIENTE_VISTA_CLIENT_MODELCOMBOBOXAREASDEVISION_H_

#include "common_AreaDeVision.h"

using common::AreaDeVision;

/*
 * Representa el modeo del combobox que se usa para listar las areas de vision.
 */
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

#endif /* CLIENTE_VISTA_CLIENT_MODELCOMBOBOXAREASDEVISION_H_ */
