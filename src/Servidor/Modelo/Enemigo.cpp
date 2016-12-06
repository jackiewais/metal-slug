#include "Enemigo.h"
#include <string>
#include <iostream>
#include <sstream>
#include <stdlib.h>

using namespace std;


Enemigo::Enemigo(int id, int velocidad, int ancho, int alto, int altoEscenario, map<int, Jugador*> *mapJugadores, string sprite = "enemigo") {
	this->id = id;
	this->velocidad = velocidad;
	this->velSalto = velocidad*2;
	this->ancho = ancho;
	this->alto = alto;
	this->piso = altoEscenario - 150;
	this->topeSalto = piso-100;
	this->plataforma = topeSalto + 40;
	this->mapJugadores = mapJugadores;
	this->distanciaHastaLaQueSeAcercaAJugador = 10 + rand() % (801 - 10);
	this->avanceEscenarioBloqueado = false;
	this->vida = 10;
	this->sprite = sprite;

	moverAPosicionInicial();
}

Enemigo::~Enemigo() {
	// TODO Auto-generated destructor stub
}

bool Enemigo::estaSaltando() {
	return (this->estado == SALTA_DER_GUN|| this->estado == SALTA_IZQ_GUN);
}

void Enemigo::mover(int anchoEscenario) {
	Jugador *unJugador;
	map<int, Jugador*>::iterator it = this->mapJugadores->begin();

	if ( it != this->mapJugadores->end() ) {
		unJugador = it->second;

		if (this->posY < this->piso) {
			this->posY += 5;
			//this->estado = DISPARANDO_DER;
			if (this->posY >= this->piso) {
				this->posY = this->piso;
				this->estado = PARADO_GUN;
			}
		} else {

			if ( (this->posX - unJugador->getPosX()) > this->distanciaHastaLaQueSeAcercaAJugador ) {
				this->mover(anchoEscenario, -1, "CAMINA_IZQ");
			} else if ( (this->posX - unJugador->getPosX()) < -this->distanciaHastaLaQueSeAcercaAJugador ) {
				this->mover(anchoEscenario, 1, "CAMINA_DER");
			} else if ( (this->posX < 0) && (this->posX < unJugador->getPosX()) ) {
				this->mover(anchoEscenario, 1, "CAMINA_DER");
			} else if ( (this->posX > (anchoEscenario - this->ancho)) && (this->posX > unJugador->getPosX()) ) {
				this->mover(anchoEscenario, -1, "CAMINA_IZQ");
			} else {
				this->mover(anchoEscenario, 0, "PARADO_GUN");
			}
		}
	}
}

void Enemigo::mover(int anchoEscenario, int vecesX, string accion) {

	if (accion=="SALTA"){
		this->estado = (vecesX >= 0)?SALTA_DER_GUN:SALTA_IZQ_GUN;
	}

	//manejarSalto();

	if (vecesX == 0){
		if (!estaSaltando()){
			this->estado = PARADO_GUN;
		}
	}else{
		if (!estaSaltando()){
			this->estado =  (vecesX > 0)?CAMINA_DER_GUN:CAMINA_IZQ_GUN;
		}

		this->posX += (vecesX * this->velocidad);
	}
}

void Enemigo::manejarSalto(){
	if (estaSaltando()){
		this->posY += (velSalto * factorSalto);
		if (this->posY < topeSalto){
			factorSalto = 1;
		}else if (this-> posY > piso){
			factorSalto = -1;
			this-> posY = piso;
			this->estado = PARADO_GUN;
		}else if (this->posY ==plataforma && factorSalto == 1 && this->posX > 100 && this->posX < 200){
			factorSalto = -1;
			this-> posY = plataforma;
			this->estado = PARADO_GUN;
		}
	}else{
		if (this->posY ==plataforma && this->posX < 100) {
			factorSalto = 1;
			this->estado = SALTA_IZQ_GUN;
		}else if(this->posY ==plataforma && this->posX > 200){
			factorSalto = 1;
			this->estado = SALTA_DER_GUN;
		}
	}

}

void Enemigo::moverAPosicionInicial(){
	this->posX = 800;
	this->posY = piso;
	this->estado=PARADO_GUN;
}

void Enemigo::saltandoDeAvion(int x, int y){
	this->posX = x;
	this->posY = y;
	this->estado = SALTA_DER_GUN;
	this->vida = 50;
}

string Enemigo::getUtimoChar(){
	return "C";
}
string Enemigo::getStringMensajeUpdate() {
    stringstream x,y,estado;
    x << (this->posX);
    y << (this->posY);
    estado << this->estado;
	return (x.str() + ";" + y.str() + ";" + estado.str() + ";"+this->getUtimoChar());
}

string Enemigo::getStringMensajeNew() {
    stringstream x,y,estado;
    x << (this->posX);
    y << (this->posY);
	return (this->sprite + ";" + x.str() + ";" + y.str());
}

string Enemigo::getCodEnemigo() {
	stringstream idS;
	idS << (this->id);
	return "T" + idS.str();
}

void Enemigo::retrocederSegunAvanceEscenario(int avance) {
	this->posX -= avance;
}

void Enemigo::bloquearAvanceEscenario() {
	this->avanceEscenarioBloqueado = true;
}

bool Enemigo::estaBloqueadoElAvanceDelEscenario(int anchoEscenario) {
	if (this->avanceEscenarioBloqueado) {
		return true;
	}
	return false;
}

void Enemigo::aparecerPorIzquierda() {
	this->posX = 0;
}

bool Enemigo::esEnemigoFinal() {
	return false;
}

// Devuelve true cuando se muere
bool Enemigo::restarVida(weapon arma) {
	switch (arma){
		case GUN:
			this->vida -= 10;
		break;
		case MACHINEGUN:
			this->vida -= 20;

		break;
		case SHOOTGUN:
			this->vida -= 50;
		break;

	}
	if (this->vida <= 0) {
		return true;
	}
	return false;
}
list<Bala*> Enemigo::dispararComun(){

	list<Bala*> balas;

	Bala* bala1 = new Bala(this->posX+12,this->posY+12,RIGHT,0,2);
	bala1->tipoDeBala = GUN;
	balas.push_front(bala1);


return balas;


}
list<Bala*> Enemigo::disparar(){
	list<Bala*> balas;
	if(this->ancho<400){
	Bala* bala1 = new Bala(this->posX+50,this->posY+60,LEFT,0,2);
	bala1->tipoDeBala = BOMB;
	balas.push_front(bala1);
	Bala* bala2 = new Bala(this->posX+50,this->posY+60,DOWN,0,2);
	bala2->tipoDeBala = BOMB;
	balas.push_front(bala2);
	Bala* bala3 = new Bala(this->posX+50,this->posY+60,RIGHT,0,2);
	bala3->tipoDeBala = BOMB;
	balas.push_front(bala3);}
	else { // ES EL TANQUE
		Bala* bala1 = new Bala(this->posX+80,this->posY+150,LEFT,0,2);
			bala1->tipoDeBala = TANIOHGUN;
			balas.push_front(bala1);
			Bala* bala2 = new Bala(this->posX+80,this->posY+20,LEFT,0,2);
			bala2->tipoDeBala = TANIOHGUN;
			balas.push_front(bala2);


	}




	return balas;
}

Enemigo* Enemigo::lanzarEnemigo(){
	return NULL;
}
