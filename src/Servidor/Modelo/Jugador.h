#ifndef SRC_SERVIDOR_JUGADOR_H_
#define SRC_SERVIDOR_JUGADOR_H_
#include <string>
#include <iostream>
#include "../../Common/Modelo.h"
#include "../Usuario.h"
#include "Bala.h"
#include <list>

using namespace std;

class Jugador{

private:
	int id;
	//string nombre;
	int factorSalto = -1;
	int piso;
	int topeSalto;
	int plataforma;
	weapon arma = MACHINEGUN;

	estadoJugador getEstadoParado();
	estadoJugador getEstadoSaltarIzquierda();
	estadoJugador getEstadoSaltarDerecha();
	estadoJugador getEstadoCaminarIzquierda();
	estadoJugador getEstadoCaminarDerecha();

public:
	list<Bala*> disparar(aimDirection direccion);
	Usuario* usuario;
	bool aceptaCambios = true;
	int posX;
	int posY;
	int alto;
	int ancho;
	int velocidad;
	int velSalto;

	int puntaje;
	int vida;
	int municiones;
	bool gameOver = false;

	estadoJugador estado;
	string equipo = "1";



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
	bool activo();
	int getIdSocket();
	bool estaSaltando();
	void moverAPosicionInicial();
	void reiniciar();
	//estadoJugador resolverEstado(string accion, int vecesX);
};

#endif /* SRC_SERVIDOR_JUGADOR_H_ */
