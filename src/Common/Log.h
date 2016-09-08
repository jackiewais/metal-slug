#ifndef LOG_H_
#define LOG_H_

#include <iostream>
#include <string.h>
#include <fstream>
#include <iomanip>
#include <sstream>

class Log {
private:

	void write_file(char* file_name,char* message);

public:

	void log_servidor(int nivel, int tipo, char msg[], char* usuario);
	//Puede tener 4 niveles, 1.Productivo, 2.Debugin Simple sin msg ingresado,
	//3.Debugin con 128 caracteres de msg ingresado, 4.Debugin con mensaje ingresado completo
	void log_cliente(int nivel, int tipo);
	//Solo puede tener 2 niveles, 1.Productivo, 2.Debugin

//En ambos casos "tipo" corresponde al tipo de mensaje para cada caso.

};
#endif /* LOG_H_ */
