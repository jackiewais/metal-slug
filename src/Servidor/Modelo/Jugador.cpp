#include "Jugador.h"
#include <sstream>

Jugador::Jugador(int id, int velocidad, int posX, int posY, int ancho, int alto, Usuario* usuario) {

	this->id = id;
	this->posX = posX;
	this->posY = posY;
	this->velocidad = velocidad;
	this->velSalto = velocidad*2;
	this->ancho = ancho;
	this->alto = alto;
	this->puntaje = 0;
	this->estado = PARADO;
	this->usuario = usuario;

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

/*estadoJugador Jugador::resolverEstado(string accion, int vecesX){
	if (accion == "SALTA"){
		return SALTA;
	}else if (vecesX == 0){
		return PARADO;
	}else if (vecesX > 0){
		return CAMINA_DER;
	}else{
		return CAMINA_IZQ;
	}
}

bool Jugador::mover(int margen, int vecesX, string accion) {

	bool cruzoMargen = false;

	estadoJugador nuevoEstado = resolverEstado(accion, vecesX);

	if (this->aceptaCambios || (nuevoEstado == SALTA && this->estado != SALTA) ){
		this->estado = nuevoEstado;

		bool llegoAlPiso = manejarSalto();
		if (llegoAlPiso){
			this->estado = resolverEstado("NO SALTA", vecesX);
		}

		if (vecesX != 0){
			this->posX += (vecesX * this->velocidad);

			if (this->posX > (margen - this->ancho)) {
				//si cruza el margen se tiene que mover el escenario
				cruzoMargen = true;
			}

			if (this->posX < 0){
				//no puede retroceder en el escenario
				//un jugador desconectado sera arrastrado
				this->posX = 0;
			}
		}
		this->aceptaCambios = false;

	}
	return cruzoMargen;
}

bool Jugador::manejarSalto(){

	bool llegoAlPiso = false;

	if (this->estado == SALTA){
		this->posY += (velSalto * factorSalto);
		if (this->posY < topeSalto){
			factorSalto = 1;
		}else if (this-> posY > piso){
			factorSalto = -1;
			this-> posY = piso;
			llegoAlPiso = true;
		}
	}

	return llegoAlPiso;

}
*/
bool Jugador::mover(int margen, int vecesX, string accion) {

	bool cruzoMargen = false;

	if (this->aceptaCambios){
		if (accion == "SALTA"){
			this->estado = SALTA;
		}

		manejarSalto();

		if (vecesX == 0){
			if (this->estado != SALTA){
				this->estado = PARADO;
			}
		}else{
			if (this->estado != SALTA){
				this->estado =  (vecesX > 0)?CAMINA_DER:CAMINA_IZQ;
			}

			this->posX += (vecesX * this->velocidad);

			if (this->posX > (margen - this->ancho)) {
				//si cruza el margen se tiene que mover el escenario
				cruzoMargen = true;
			}

			if (this->posX < 0){
				//no puede retroceder en el escenario
				//un jugador desconectado sera arrastrado
				this->posX = 0;
			}
		}
		this->aceptaCambios = false;
	}
	return cruzoMargen;
}

void Jugador::manejarSalto(){


	if (this->estado == SALTA){
		this->posY += (velSalto * factorSalto);
		if (this->posY < topeSalto){
			factorSalto = 1;
		}else if (this-> posY > piso){
			factorSalto = -1;
			this-> posY = piso;
			this->estado = PARADO;
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


bool Jugador::conectado() {
	return this->usuario->isConectado();
}


int Jugador::getIdSocket() {

	return this->usuario->getIdSocket();
}
