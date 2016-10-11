#ifndef PARSER_H_
#define PARSER_H_
#include "lib/pugixml.hpp"
#include "../Common/MensajeStruct.h"
#include <string>
#include <cstring>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>


using namespace pugi;
using namespace std;

class Parser
{
public:

	bool parsearArchivoXML(const std::string& nameFileXML);

	Parser();
	~Parser();

	const mensajeStruct getVentana() const {
		return ventana;
	}
	std::vector<mensajeStruct> getListaFondos() const {
		return listaFondos;
	}
	std::vector<mensajeStruct> getListaSprites() const {
		return listaSprites;
	}
	std::vector<mensajeStruct> getListaObjetos() const {
		return listaObjetos;
	}

private:

	struct fondo {
        string letra;
		int numero;
	};

	mensajeStruct ventana;
	std::vector<mensajeStruct> listaFondos;
	std::vector<mensajeStruct> listaSprites;
	std::vector<mensajeStruct> listaObjetos;

	void getxmlSprites(const pugi::xml_document* doc);
	void getxmlVentana(const pugi::xml_document* doc);
	void getxmlObjetos(const pugi::xml_document* doc);
	void getxmlFondos(const pugi::xml_document* doc);
	bool validar(std::string numero);
};

#endif /* PARSER_H_ */
