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
