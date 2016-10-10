#include "Jugador.h"
#include <sstream>

Jugador::Jugador(int id, int velocidad, int posX, int posY, int ancho, int alto) {

	this->id = id;
	this->posX = posX;
	this->posY = posY;
	this->velocidad = velocidad;
	this->ancho = ancho;
	this->alto = alto;
	this->puntaje = 0;
	this->conectado = true;


}

Jugador::~Jugador() {

}


int Jugador::getId() {

	return this->id;
}

string Jugador::getCodJugador() {
	stringstream idS;
	idS << (this->id);
	return "J" + idS.str();
}

void Jugador::mover(int anchoEscenario, int vecesX) {

	if (vecesX == 0){
		this->estado = PARADO;
	}else{
		this->estado =  (vecesX > 0)?CAMINA_DER:CAMINA_IZQ;

		this->posX += (vecesX * this->velocidad);
		if (this->posX > (anchoEscenario-this->ancho)){
			//ESTO ES PARA QUE NO SE VAYA, HAY QUE AGREGAR EL MARGEN
			this->posX = anchoEscenario-this->ancho;
		}

		if (this->posX < 0){
			this->posX = 0;
		}
	}

}


string Jugador::getPosConcat() {

    stringstream x,y;
    x << (this->posX);
    y << (this->posY);
	return (x.str() + ";" + y.str());
}




int Jugador::getPosX() {

	return this->posX;
}


void Jugador::setPosX(int x) {

	this->posX = x;
}


int Jugador::getPosY() {

	return this->posY;
}


void Jugador::setPosY(int y) {

	this->posY = y;
}

