#include "server_ParserXML.h"

namespace server {

ParserXML::ParserXML() {
	// TODO Auto-generated constructor stub

}

ParserXML::~ParserXML() {
	// TODO Auto-generated destructor stub
}

std::string ParserXML::valorDelElementoEnArchivo(const std::string& identificadorElemento,const std::string& rutaArchivoXML){
	TiXmlDocument archXML(rutaArchivoXML);
	if (archXML.LoadFile()){
		TiXmlElement* nodoElemento=archXML.FirstChildElement(identificadorElemento);
		if (nodoElemento!=NULL)
			return std::string(nodoElemento->GetText());
	}
	return "";
}

} /* namespace server */
