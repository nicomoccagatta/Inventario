/*
 * CommandParser.cpp
 *
 *  Created on: Apr 27, 2015
 *      Author: ale
 */

#include <sstream>
#include <string>
#include <vector>
#include "common_CommandParser.h"

#define TO_REPLACE " "
#define REPLACEMENT '|'


void CommandParser::tokenize(std::string& comandoCompleto){
	std::stringstream iss(comandoCompleto);

	std::string item;
	while (std::getline(iss, item, DELIMITER)) {
		tokens.push_back(item);
	}
}
/*
void CommandParser::parsear(std::string& comandoCompleto){
	std::vector<std::string> tokens;
	tokens = tokenize(comandoCompleto);
	comando = "";
	parametros.clear();

	std::stringstream iss;

	if (tokens.size() > 0)
		comando = tokens[0];
	if (tokens.size() > 1){
		for(size_t i=1; i<tokens.size(); ++i){
			iss.clear();
			int param;
			iss << tokens[i];
			iss >> param;
			parametros.push_back(param);
		}
	}
}

void CommandParser::protocolizar(std::string& msj){
	size_t pos = 0;
	while((pos = msj.find(TO_REPLACE, pos)) != std::string::npos){
		msj.replace(pos, 1, sizeof(char), REPLACEMENT);
		pos += sizeof(char);
	}
}
*/
