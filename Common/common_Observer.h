#ifndef ADMINISTRADOR_MODELOADMIN_ADMIN_OBSERVER_H_
#define ADMINISTRADOR_MODELOADMIN_ADMIN_OBSERVER_H_

#include <iostream>

class Observer {
public:
	virtual void update() = 0;
	virtual ~Observer();
};

#endif /* ADMINISTRADOR_MODELOADMIN_ADMIN_OBSERVER_H_ */
