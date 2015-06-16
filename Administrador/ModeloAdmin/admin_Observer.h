/*
 * admin_Observer.h
 *
 *  Created on: 16/6/2015
 *      Author: nicomoccagatta
 */

#ifndef ADMINISTRADOR_MODELOADMIN_ADMIN_OBSERVER_H_
#define ADMINISTRADOR_MODELOADMIN_ADMIN_OBSERVER_H_

class Observer {
public:
	Observer();
	void update();
	virtual ~Observer();
};

#endif /* ADMINISTRADOR_MODELOADMIN_ADMIN_OBSERVER_H_ */
