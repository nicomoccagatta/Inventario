#ifndef SERVER_PARSERXML_H_
#define SERVER_PARSERXML_H_

#include "tinyxml.h"

namespace server {

class ParserXML {
public:
	ParserXML();
	virtual ~ParserXML();

	static std::string valorDelElementoEnArchivo(const std::string& identificadorElemento,const std::string& rutaArchivoXML);
};

} /* namespace server */

#endif /* SERVER_PARSERXML_H_ */
