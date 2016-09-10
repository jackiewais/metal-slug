#ifndef IMPORTARCSV_H_
#define IMPORTARCSV_H_

#include <string>

using namespace std;

class ImportarCSV {

private:
	int cantidadUsuarios;
	int datos;
	string  **tablaUsuarios;

public:
	ImportarCSV();
	virtual ~ImportarCSV();
	string** importar(string csv);
	int getCantidadUsuarios();
};

#endif /* IMPORTARCSV_H_ */
