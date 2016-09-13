#ifndef LOG_H_
#define LOG_H_

#include <iostream>
#include <string.h>
#include <fstream>
#include <iomanip>
#include <sstream>

using namespace std;
class Log {
private:

	void write_file(char* file_name,string message);

public:

	void log(char tipo_arch,int tipo_msg, string mensaje, string chat);

	//tipo char -> 'c':indica archivo del cliente,'s': indica archivo del servidor
	//tipo_msg -> 1:INFO,2:WARNNING,3:ERROR
	//mensaje -> mensaje basico del log
	//chat -> mensaje emitido y recibido por el cliente
};
#endif /* LOG_H_ */
