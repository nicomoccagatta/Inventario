/*
 * CommandParser.h
 *
 *  Created on: Apr 27, 2015
 *      Author: ale
 */

#ifndef COMMON_COMMANDPARSER_H_
#define COMMON_COMMANDPARSER_H_

#include <vector>
#include <string>
#include <exception>
#include <stdexcept>

#define DELIMITER '|'

/*La clase es la encargada de parsear los comandos que puede recibir el
 * server. Estos se reciben de la forma
 * <comando>|[<parametro1>|<parametro2>|...]
 */
class CommandParser {

	std::vector<std::string> tokens;

public:
	CommandParser(){}
	virtual ~CommandParser(){}


	void tokenize(std::string& comandoCompleto);

	/*Parsa el string. Guarda el comando en comando y los parametros
	 * en el vector de parametros.
	 */
	//void parsear(std::string& comandoCompleto);

	size_t getCantParamtros(){
		return tokens.size();
	}

	/*Devuelve el parametro numero num*/
	std::string& getParametro(unsigned int num){
		if (num > tokens.size() || num <= 0)
			throw std::out_of_range("No existe ese parametro");
		return tokens[num-1];
	}

	/*reemplaza los TO_REPLACE por DELIMITADOR */
	//void protocolizar(std::string& msje);
};

#endif /* COMMON_COMMANDPARSER_H_ */
