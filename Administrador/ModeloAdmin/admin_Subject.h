/*
 * admin_Subject.h
 *
 *  Created on: 16/6/2015
 *      Author: nicomoccagatta
 */

#ifndef ADMINISTRADOR_MODELOADMIN_ADMIN_SUBJECT_H_
#define ADMINISTRADOR_MODELOADMIN_ADMIN_SUBJECT_H_

#include <vector>
#include "ModeloAdmin/admin_Observer.h"

class Subject {
	std::vector<Observer*> observadores;
public:
	Subject();
	void suscribe(Observer *observador);
	void notify();
	void unsuscribe(Observer *observador);
	virtual ~Subject();
};

#endif /* ADMINISTRADOR_MODELOADMIN_ADMIN_SUBJECT_H_ */