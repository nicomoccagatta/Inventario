#ifndef COMMON_STOCK_H_
#define COMMON_STOCK_H_

#include <string>

namespace common {

class Stock {
public:
	Stock(unsigned long int cantidad,std::string fecha);
	const std::string getFecha()const;
	const unsigned long int getCantidad()const;

private:
	unsigned long int cantidad;
	std::string fecha;
};

} /* namespace common */

#endif /* COMMON_STOCK_H_ */
