#include "EscenarioS.h"
#include <sstream>

EscenarioS::EscenarioS(int ancho, int alto) {

	this->ancho = ancho;
	this->alto = alto;
	this->margen = ancho/2;
	this->distancia = 5;
	this->avance = 0;
}

EscenarioS::~EscenarioS() {
	// TODO Auto-generated destructor stub
}


Jugador* EscenarioS::getJugadorById(int id) {

	Jugador* jugador = NULL;

		map<int, Jugador*>::iterator it;

		if((it = this->mapJugadores.find(id)) != this->mapJugadores.end())
			jugador = this->mapJugadores[id];

		return jugador;
}


void EscenarioS::addJugador(Jugador* jugador) {

	this->mapJugadores[jugador->getId()] = jugador;
	if (this->mapJugadores.size() > 1) {
		this->margen = (this->ancho -(50));
	}
}


void splitE(const string &s, char delim, vector<string> &elems) {
    stringstream ss;
    ss.str(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
}


vector<string> splitE(const string &s, const char delim) {
    vector<string> elems;
    splitE(s, delim, elems);
    return elems;
}

mensajeStruct EscenarioS::getMensajeDesconexion(int jugadorId){
	Jugador* jugador = this->mapJugadores[jugadorId];
	return getMensajeJugador(jugador);
}
void EscenarioS::addBala(Bala *bala){
cout << "agrega bala a lista" << endl;
this->balas.push_front(bala);
}

void EscenarioS::moverBala(){

	list<Bala*>::iterator it;
bool afuera = false;
	for (it=balas.begin(); it!=balas.end(); ++it){
		(*it)->mover();
	}

		list<Bala*>::iterator itDelete;

				for (it=balas.begin(); it!=balas.end(); ++it){
						if((*it)->x>this->ancho || (*it)->y > this->alto){
						afuera = true;
							cout << "elimno una bala en pos " << (*it)->x << " " << (*it)->y <<endl;
						itDelete = it;
						}
				     }
				if(afuera){
					balas.erase(itDelete);
				}

}


list<mensajeStruct> EscenarioS::moverJugador(int jugadorId, string mensaje) {
	Jugador* jugador = this->mapJugadores[jugadorId];
	vector<string> result = splitE(mensaje, ';');
	int vecesX = atoi(result[0].c_str());
	string estado = result[1];
	list<mensajeStruct> returnList;
	if(estado=="DISPARO"){

	Bala *bala = new Bala(jugador->getPosX()+10,jugador->getPosY()+10,1);
	this->addBala(bala);


	}
	if(estado=="RESET"){
		mensajeStruct msjReset;
		msjReset.tipo = RESET;
		msjReset.objectId = "X0";
		msjReset.message = "RESET";
		returnList.push_back(msjReset);
		this->resetEscenario();
	}else{
		jugador->mover(this->ancho,vecesX, estado);
		moverEscenario(&returnList);
		returnList.push_back(getMensajeJugador(jugador));
		returnList.push_back(getMensajeEscenario());

		// hardcodeado por el momento
		if ((this->avance >= 30) && (this->avance <= 700) ) {
			returnList.push_back(getMensajeEnemigoUpdate());
		}

		if(!this->balas.empty()){
		moverBala();
		//itero para madar un mensaje por bala ( después seria un solo mensaje
		//con todas las balas).
		list<Bala*>::iterator it;
			for (it=balas.begin(); it!=balas.end(); ++it){
				returnList.push_back(getMensajeBala((*it)));
			}

		}

		cout << "sale de armar mensaje de bala" << endl;
	}

	return returnList;
}

void EscenarioS::aceptarCambios(){
	for (map<int,Jugador*>::iterator jugador=this->mapJugadores.begin(); jugador!=this->mapJugadores.end(); ++jugador){
		jugador->second->aceptaCambios = true;
	}
}

void EscenarioS::moverEscenario(list<mensajeStruct>* mainList) {

	bool cruzoMargen = false;
	int minPosX = this->distancia;

	for (map<int,Jugador*>::iterator jugador=this->mapJugadores.begin(); jugador!=this->mapJugadores.end(); ++jugador){
		if (jugador->second->conectado()) {
			if (jugador->second->getPosX() < minPosX) {
				minPosX = jugador->second->getPosX();

			} else if (jugador->second->getPosX() > (this->margen - jugador->second->ancho)) {
					   //si cruza el margen se tiene que mover el escenario
						cruzoMargen = true;
				   }
		}
	}

	if (minPosX != 0 && cruzoMargen) {
/*
		int distRecorrida = 1;

		while (distRecorrida <= (minPosX/velocidad)) {
			for (map<int,Jugador*>::iterator jugador=this->mapJugadores.begin(); jugador!=this->mapJugadores.end(); ++jugador) {
					jugador->second->mover(this->ancho,this->margen,-1, "");
					mainList->push_back(getMensajeJugador(jugador->second));
			}
			this->avance += distRecorrida;
			mainList->push_back(getMensajeEscenario());
			distRecorrida += 1;
		}
*/

		//Por ahora solo le seteo la posicion final del retroceso, desp hay que tener en cuenta la velocidad para las demas posiciones
		int posActual;
		for (map<int,Jugador*>::iterator jugador=this->mapJugadores.begin(); jugador!=this->mapJugadores.end(); ++jugador) {
			posActual = jugador->second->getPosX() - minPosX;
			if (!jugador->second->conectado() && posActual < 0) {
				jugador->second->setPosX(0);
			}
			else {
				jugador->second->setPosX(posActual);
			}
			mainList->push_back(getMensajeJugador(jugador->second));
		}
		this->avance += minPosX;

		// hardcodeado por el momento

		if (this->avance == 30) {
			mainList->push_back(getMensajeEnemigoNuevo());
		}
		if (this->avance == 700) {
			mainList->push_back(getMensajeEnemigoMuerto());
		}
	}
}



mensajeStruct EscenarioS::getMensajeJugador(Jugador* jugador){
	mensajeStruct msjJug;
	msjJug.tipo = JUGADOR_UPD;
	msjJug.message = jugador->getStringMensaje();
	msjJug.objectId = jugador->getCodJugador();
	return msjJug;
}

mensajeStruct EscenarioS::getMensajeEscenario(){
	mensajeStruct msjEscenario;
	stringstream avanceFondo;
	avanceFondo << this->avance;

	msjEscenario.tipo = ESCENARIO_UPD;
	msjEscenario.message = ("-"+ avanceFondo.str());
	msjEscenario.objectId = "E00";

	return msjEscenario;
}

mensajeStruct EscenarioS::getMensajeEnemigoNuevo(){
	mensajeStruct msjEnemigo;

	msjEnemigo.tipo = ENEMIGO_NEW;
	// id fruta, cambiar despues
	msjEnemigo.objectId="T1";
	msjEnemigo.message="jugador1;800;450";

	return msjEnemigo;
}

mensajeStruct EscenarioS::getMensajeEnemigoMuerto(){
	mensajeStruct msjEnemigo;

	msjEnemigo.tipo = ENEMIGO_DELETE;
	// id fruta, cambiar despues
	msjEnemigo.objectId="T1";
	msjEnemigo.message="";

	return msjEnemigo;
}

mensajeStruct EscenarioS::getMensajeEnemigoUpdate(){
	mensajeStruct msjEnemigo;
	stringstream posXEnemigo;
	// un movimiento cualquiera para probar
	posXEnemigo << (800 - this->avance);

	msjEnemigo.tipo = ENEMIGO_UPD;
	// id fruta, cambiar despues
	msjEnemigo.objectId="T1";
	msjEnemigo.message=posXEnemigo.str() + ";450;03;C";

	return msjEnemigo;
}
mensajeStruct EscenarioS::getMensajeBala(Bala* bala){
	mensajeStruct msjBala;
	stringstream posx;
	stringstream posy;
	//ACA TENDRIA QUE ARMAR EL MENSAJE DE TODAS LAS BALAS
	posx<<bala->x;
	posy<<bala->y;
	msjBala.tipo = BALA_UPD;
	msjBala.message="bala;" + posx.str() + ";" + posy.str();

	return msjBala;
}

void EscenarioS::resetEscenario(){
	this->avance = 0;
	for (map<int,Jugador*>::iterator jugador=this->mapJugadores.begin(); jugador!=this->mapJugadores.end(); ++jugador){
		jugador->second->moverAPosicionInicial();
	}
}
