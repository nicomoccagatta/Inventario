#ifndef SERVER_DETECTORDEOBJETOS_H_
#define SERVER_DETECTORDEOBJETOS_H_

#include <list>
#include <vector>

namespace server {

class DetectorDeObjetos {
public:
	DetectorDeObjetos();
	virtual ~DetectorDeObjetos();
	static const unsigned int contarApariciones(std::list<std::vector<unsigned char> > imagenesObjeto, std::vector<unsigned char> imagenEscena);
};

} /* namespace server */

#endif /* SERVER_DETECTORDEOBJETOS_H_ */
