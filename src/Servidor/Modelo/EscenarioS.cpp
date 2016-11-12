#include "EscenarioS.h"
#include <sstream>
#include "SDL2/SDL.h"
EscenarioS::EscenarioS(int ancho, int alto) {

	this->ancho = ancho;
	this->alto = alto;
	this->margen = ancho/2;
	this->distancia = 5;
	this->avance = 0;
	this->avanceBloqueado = false;
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

void EscenarioS::addEnemigoInactivo(Enemigo* enemigo, int posXAbsolutaDeJugadorParaAparicion) {
	this->enemigosInactivos.insert(pair<int, Enemigo*>(posXAbsolutaDeJugadorParaAparicion,enemigo));
}

// Si no se activa ningun enemigo devuelve NULL
Enemigo* EscenarioS::activarEnemigo(int posXAbsolutaJugador) {
	Enemigo *enemigo = NULL;
	std::multimap<int,Enemigo*>::iterator it = this->enemigosInactivos.find(posXAbsolutaJugador);
	if ( it != this->enemigosInactivos.end() ) {
		enemigo = it->second;
		this->enemigosInactivos.erase(it);
		this->enemigosVivos.push_front(enemigo);
	}
	return enemigo;
}

void EscenarioS::activarEnemigos(int posXAbsolutaJugador, list<mensajeStruct>* mainList) {
	Enemigo *enemigo = NULL;
	enemigo = activarEnemigo(posXAbsolutaJugador);
	while (enemigo != NULL) {
		mainList->push_back(getMensajeEnemigoNuevo(enemigo));
		enemigo = activarEnemigo(posXAbsolutaJugador);
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
this->balas.push_front(bala);
}

void EscenarioS::moverBala(){

	list<Bala*>::iterator it;
	list<Bala*>::iterator itDelete;

	bool afuera = false;
	for (it=balas.begin(); it!=balas.end(); ++it){
	(*it)->mover();
	}

	for (it=balas.begin(); it!=balas.end(); ++it){
		if((*it)->x>this->ancho || (*it)->x< 0 || (*it)->y < 0){
		afuera = true;
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
	list<Enemigo*>::iterator itEnemigos;
	Enemigo *enemigo = NULL;

	if(estado=="DISPARO"){
	int direccion = atoi(result[2].c_str());

	this->addBala(jugador->disparar(direccion));



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

		//ESTO ES PARA PROBAR
		jugador->puntaje += 1;
		jugador->vida -= 1;
		if (jugador->vida == 0) {jugador->vida=100; jugador->municiones = 200;}

		if (jugador->vida >80 ) jugador->municiones=-1;
		if (jugador->vida ==80 ) jugador->municiones=300;
		if (jugador->vida <80 ) jugador->municiones-=2;
		if (!this->avanceBloqueado) {
			moverEscenario(&returnList);
		}
		returnList.push_back(getMensajeJugador(jugador));
		returnList.push_back(getMensajeEscenario());


		activarEnemigos(this->avance + jugador->getPosX(), &returnList);

		this->avanceBloqueado = false;
		for (itEnemigos = this->enemigosVivos.begin(); itEnemigos != this->enemigosVivos.end(); itEnemigos++) {
			enemigo = (*itEnemigos);
			enemigo->mover(this->ancho);
			if (enemigo->estaBloqueadoElAvanceDelEscenario(this->ancho)) {
				this->avanceBloqueado = true;
			}
			returnList.push_back(getMensajeEnemigoUpdate(enemigo));
		}
		if(!this->balas.empty()){
			moverBala();
			returnList.push_back(getMensajeBala());
		}
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
	list<Enemigo*>::iterator itEnemigos;
	Enemigo *enemigo = NULL;

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

		for (itEnemigos = this->enemigosVivos.begin(); itEnemigos != this->enemigosVivos.end(); itEnemigos++) {
			enemigo = (*itEnemigos);
			enemigo->retrocederSegunAvanceEscenario(minPosX);
		}
		// hardcodeado por el momento

		/*
		if (this->avance == 30) {
			mainList->push_back(getMensajeEnemigoNuevo());
		}
		if (this->avance == 700) {
			mainList->push_back(getMensajeEnemigoMuerto());
		}*/
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

mensajeStruct EscenarioS::getMensajeEnemigoNuevo(Enemigo *enemigo){
	mensajeStruct msjEnemigo;

	msjEnemigo.tipo = ENEMIGO_NEW;
	msjEnemigo.objectId = enemigo->getCodEnemigo();
	msjEnemigo.message = enemigo->getStringMensajeNew();

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

mensajeStruct EscenarioS::getMensajeEnemigoUpdate(Enemigo *enemigo){
	mensajeStruct msjEnemigo;

	msjEnemigo.tipo = ENEMIGO_UPD;
	msjEnemigo.objectId = enemigo->getCodEnemigo();
	msjEnemigo.message = enemigo->getStringMensajeUpdate();

	return msjEnemigo;
}
mensajeStruct EscenarioS::getMensajeBala(){
	mensajeStruct msjBala;
	stringstream cantidadBalas;
	msjBala.tipo = BALA_UPD;
	cantidadBalas << balas.size();
	msjBala.message = cantidadBalas.str() + ";";
	list<Bala*>::iterator it;

	for (it=balas.begin(); it!=balas.end(); ++it){
	stringstream posx;
	stringstream posy;
	posx<<(*it)->x;
	posy<<(*it)->y;
	msjBala.message+=posx.str()+";"+posy.str()+";";

	}
	return msjBala;
}

void EscenarioS::resetEscenario(){
	this->avance = 0;
	for (map<int,Jugador*>::iterator jugador=this->mapJugadores.begin(); jugador!=this->mapJugadores.end(); ++jugador){
		jugador->second->moverAPosicionInicial();
	}
}
