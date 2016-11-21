#ifndef PARSER_H_
#define PARSER_H_
#include "lib/pugixml.hpp"
#include "../Common/MensajeStruct.h"
#include "../Common/Modelo.h"
#include <string>
#include <cstring>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>


using namespace pugi;
using namespace std;

class Parser
{
public:

	bool parsearArchivoXML(const std::string& nameFileXML);

	Parser();
	Parser(int cli);
	~Parser();

	const mensajeStruct getVentana() const {
		return ventana;
	}
	std::vector<mensajeStruct> getListaFondos()  {
		return listaFondos;
	}
	std::vector<mensajeStruct> getListaSprites()  {
		return listaSprites;
	}
	std::vector<mensajeStruct> getListaObjetos()  {
		return listaObjetos;
	}
	std::vector<mensajeStruct> getListaEstadosSpritesObjetos()  {
		return listaEstadosSprites;
	}
	std::vector<enemigoStruct> getListaEnemigos()  {
		return listaEnemigos;
	}

	std::vector<mensajeStruct> getBasicSprites()  {
		return listaBasicSprites;
	}
	std::map<int,bonus> getBonuses()  {
		return bonuses;
	}
	std::vector<mensajeStruct> getListaPlataformas()  {
		return listaPlataformas;
	}
	int getAnchoJugador();
	int getAltoJugador();
	int getAnchoEscenario();
	int getAltoEscenario();
	int getCantJugadores();

private:

	struct fondo {
        string letra;
		int numero;
	};
    int cliente;
	mensajeStruct ventana;
	std::vector<mensajeStruct> listaFondos;
	std::vector<mensajeStruct> listaSprites;
	std::vector<mensajeStruct> listaObjetos;
	std::vector<mensajeStruct> listaEstadosSprites;
	std::vector<enemigoStruct> listaEnemigos;
	std::vector<mensajeStruct> listaBasicSprites;
	std::vector<mensajeStruct> listaPlataformas;

	std::map<int,bonus> bonuses;

	string anchoJugador;
	string altoJugador;
	string anchoEscenario;
	string altoEscenario;
	int cantJugadores;

	void getxmlCantJugadores(const pugi::xml_document* doc);
	void getxmlSprites(const pugi::xml_document* doc);
	void getxmlVentana(const pugi::xml_document* doc);
	void getxmlObjetos(const pugi::xml_document* doc);
	void getxmlFondos(const pugi::xml_document* doc);
	void getxmlEnemigos(const pugi::xml_document* doc);
	void getxmlEstadosSprites(const pugi::xml_document* doc);
	void getxmlBasicSprites(const pugi::xml_document* doc);
	void getxmlBonuses(const pugi::xml_document* doc);
	bool validar(std::string numero);
	void setAnchoJugador(const pugi::xml_document* doc);
	void setAltoJugador(const pugi::xml_document* doc);
	void setAnchoEscenario(const pugi::xml_document* doc);
	void setAltoEscenario(const pugi::xml_document* doc);
	void getxmlPlataformas(const pugi::xml_document* doc);
};

#endif /* PARSER_H_ */
