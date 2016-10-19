#include "Jugador.h"
#include <sstream>

Jugador::Jugador(int id, int velocidad, int ancho, int alto, Usuario* usuario, int piso) {

	this->id = id;
	this->velocidad = velocidad;
	this->velSalto = velocidad*2;
	this->ancho = ancho;
	this->alto = alto;
	this->puntaje = 0;
	this->usuario = usuario;
	this->piso = piso;
	this->topeSalto = piso-75;

	moverAPosicionInicial();

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

bool Jugador::estaSaltando(){
	return (this->estado == SALTA_DER || this->estado == SALTA_IZQ);
}
void Jugador::mover(int anchoEscenario, int vecesX, string accion) {

	if (this->aceptaCambios){
		if (accion == "SALTA"){
			this->estado = (vecesX >= 0)?SALTA_DER:SALTA_IZQ;
		}

		manejarSalto();

		if (vecesX == 0){
			if (!estaSaltando()){
				this->estado = PARADO;
			}
		}else{
			if (!estaSaltando()){
				this->estado =  (vecesX > 0)?CAMINA_DER:CAMINA_IZQ;
			}

			this->posX += (vecesX * this->velocidad);

			//validar limites
			if (vecesX > 0) {
				if (this->posX > (anchoEscenario - this->ancho)) {
					//no puede pasar el borde derecho
					this->posX = (anchoEscenario - this->ancho);
				}
			}else {
					if (this->posX < 0){
						//no puede retroceder en el escenario
						//un jugador desconectado sera arrastrado
						this->posX = 0;
					}
			}
		}
		this->aceptaCambios = false;
	}
}

void Jugador::manejarSalto(){


	if (estaSaltando()){
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


string Jugador::getStringMensaje() {
    stringstream x,y,estado;
    x << (this->posX);
    y << (this->posY);
    estado << (this->usuario->isConectado())?this->estado:PARADO;
    string conectado = (this->usuario->isConectado())?"C":"D";
	return (x.str() + ";" + y.str() + ";" + estado.str() + ";" + conectado);
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

void Jugador::moverAPosicionInicial(){
	this->posX = 10+this->id*60;
	this->posY = piso;
	this->estado=PARADO;
}


