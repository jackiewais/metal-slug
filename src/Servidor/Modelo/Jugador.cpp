#include "Jugador.h"
#include <sstream>


Jugador::Jugador(int id, int velocidad, int ancho, int alto, Usuario* usuario, int altoEscenario) {

	this->id = id;
	this->velocidad = velocidad;
	this->velSalto = velocidad*2;
	this->ancho = ancho;
	this->alto = alto;
	this->puntaje = 0;
	this->municiones = -1;
	this->vida=100;
	this->usuario = usuario;
	this->piso = altoEscenario - 150;
	this->topeSalto = piso-100;
	this->plataforma = topeSalto + 40;

	moverAPosicionInicial();

}

Jugador::~Jugador() {

}

list<Bala*> Jugador::disparar(aimDirection direccion){
	list<Bala*> balasDisparadas;
	Bala *bala= new Bala(this->posX+3,this->getPosY()+20,direccion,this->id);
	Bala *bala1 = new Bala(this->posX+3,this->getPosY()+20,direccion,this->id);
	Bala *bala2 = new Bala(this->posX+3,this->getPosY()+30,direccion,this->id);
	Bala *bala3 = new Bala(this->posX+3,this->getPosY()+30,direccion,this->id);
	Bala *bala4 = new Bala(this->posX+3,this->getPosY()+30,direccion,this->id);
	Bala *bala5 = new Bala(this->posX+3,this->getPosY()+30,direccion,this->id);

	switch (this->arma){
		case GUN:
			bala->tipoDeBala = GUN;
			bala->x = this->posX+3;
			bala->y = this->getPosY()+20;
			balasDisparadas.push_front(bala);
		break;
		case MACHINEGUN:
			bala->tipoDeBala = MACHINEGUN;
			bala->balaMachine= down;

			bala1->balaMachine= middle;
			bala1->tipoDeBala = MACHINEGUN;

			bala2->balaMachine= up;
			bala2->tipoDeBala = MACHINEGUN;

			bala3->tipoDeBala = MACHINEGUN;
			bala3->balaMachine= down;

			bala4->balaMachine= middle;
			bala4->tipoDeBala = MACHINEGUN;

			bala5->balaMachine= up;
			bala5->tipoDeBala = MACHINEGUN;

			//SI ESTOY APUNTADO ARRIBA CAMBIA LA POSICION INICIAL DE LAS BALAS
			if(direccion == UP){
			//PRIMER RONDA
			bala->x = this->posX+10;
			bala->y = this->getPosY()+73;

			bala1->x = this->posX+10;
			bala1->y = this->getPosY()+83;

			bala2->x = this->posX+10;
			bala2->y = this->getPosY()+93;
			// SEGUNDA RONDA

			bala3->x = this->posX+10;
			bala3->y = this->getPosY()+23;

			bala4->x = this->posX+10;
			bala4->y = this->getPosY()+33;

			bala5->x = this->posX+10;
			bala5->y = this->getPosY()+43;


			}else{

			bala->x = this->posX+73;
			bala->y = this->getPosY()+30;

			bala1->x = this->posX+83;
			bala1->y = this->getPosY()+30;

			bala2->x = this->posX+93;
			bala2->y = this->getPosY()+30;
			// SEGUNDA RONDA

			bala3->x = this->posX+23;
			bala3->y = this->getPosY()+30;

			bala4->x = this->posX+33;
			bala4->y = this->getPosY()+30;

			bala5->x = this->posX+43;
			bala5->y = this->getPosY()+30;
			}

			//PRIMER RONDA
			balasDisparadas.push_front(bala);

			balasDisparadas.push_front(bala1);

			balasDisparadas.push_front(bala2);
			// SEGUNDA RONDA
			balasDisparadas.push_front(bala3);

			balasDisparadas.push_front(bala4);

			balasDisparadas.push_front(bala5);
		break;
		case SHOOTGUN:
			bala->tipoDeBala = SHOOTGUN;
			bala->x = this->posX+3;
			bala->y = this->getPosY()+20;
			balasDisparadas.push_front(bala);
		break;

	}
	return balasDisparadas;
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
		if (accion=="SALTA"){
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
		}else if (this->posY ==plataforma && factorSalto == 1 && this->posX > 100 && this->posX < 200){
			factorSalto = -1;
			this-> posY = plataforma;
			this->estado = PARADO;
		}
	}else{
		if (this->posY ==plataforma && this->posX < 100) {
			factorSalto = 1;
			this->estado = SALTA_IZQ;
		}else if(this->posY ==plataforma && this->posX > 200){
			factorSalto = 1;
			this->estado = SALTA_DER;
		}
	}

}


string Jugador::getStringMensaje() {
    stringstream x,y,estado,puntos,vida,munic;
    x << (this->posX);
    y << (this->posY);
    estado << this->estado;
    puntos<< this->puntaje;
    vida<<this->vida;
    munic<<this->municiones;
    string conectado = (this->activo())?"C":"D";
	return (x.str() + ";" + y.str() + ";" + estado.str() + ";" + conectado + ";" + puntos.str() + ";" + vida.str() + ";" + munic.str());
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


bool Jugador::activo() {
	return this->usuario->isConectado() && !this->gameOver;
}

int Jugador::getIdSocket() {

	return this->usuario->getIdSocket();
}

void Jugador::moverAPosicionInicial(){
	this->posX = 10+this->id*60;
	this->posY = piso;
	this->estado=PARADO;
	this->gameOver=false;
	this->puntaje = 0;
	this->municiones = -1;
	this->vida=100;

}


