#ifndef SRC_SERVIDOR_JUGADOR_H_
#define SRC_SERVIDOR_JUGADOR_H_
#include <string>
#include <iostream>
#include "../../Common/Modelo.h"
#include "../Usuario.h"

using namespace std;

class Jugador{

private:
	int id;
	string nombre;
	int puntaje;
	int factorSalto = -1;
	int piso;
	int topeSalto;
	int posX;
	int posY;
	Usuario* usuario;

public:
	bool aceptaCambios = true;
	int alto;
	int ancho;
	int velocidad;
	int velSalto;

	estadoJugador estado;




	Jugador(int id, int velocidad, int ancho, int alto, Usuario* usuario, int altoEscenario);
	virtual ~Jugador();
	int getId();
	void mover(int anchoEscenario, int vecesX, string accion);
	string getStringMensaje();
	string getCodJugador();
	int getPosX();
	void setPosX(int x);
	int getPosY();
	void setPosY(int y);
	//bool manejarSalto();
	void manejarSalto();
	bool conectado();
	int getIdSocket();
	bool estaSaltando();
	void moverAPosicionInicial();
	//estadoJugador resolverEstado(string accion, int vecesX);
};

#endif /* SRC_SERVIDOR_JUGADOR_H_ */
