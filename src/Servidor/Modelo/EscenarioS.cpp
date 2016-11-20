#include "EscenarioS.h"
#include <sstream>
#include "SDL2/SDL.h"
#include "Colision.h"

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

void EscenarioS::addEnemigoInactivo(enemigoStruct enemigoStruct) {
	int id = this->enemigosInactivos.size() + 1;
	int velocidad = enemigoStruct.velocidad;
	int ancho = enemigoStruct.ancho;
	int alto = enemigoStruct.alto;
	Enemigo *enemigo = new Enemigo(id,velocidad,ancho,alto,this->alto,&this->mapJugadores);
	if (enemigoStruct.bloquearAvanceEscenario != 0) {
		enemigo->bloquearAvanceEscenario();
	}
	if (enemigoStruct.aparecePorIzq != 0) {
		enemigo->aparecerPorIzquierda();
	}
	this->enemigosInactivos.insert(pair<int, Enemigo*>(enemigoStruct.posXAbsolutaDeJugadorParaAparicion,enemigo));
}

void EscenarioS::addEnemigoFinalInactivo() {
	int id = this->enemigosInactivos.size() + 1;
	/*int velocidad = enemigoStruct.velocidad;
	int ancho = enemigoStruct.ancho;
	int alto = enemigoStruct.alto;*/
	Enemigo *enemigo = new EnemigoAirbusterRiberts(id,5,362,222,this->alto,&this->mapJugadores);
	/*if (enemigoStruct.bloquearAvanceEscenario != 0) {
		enemigo->bloquearAvanceEscenario();
	}
	if (enemigoStruct.aparecePorIzq != 0) {
		enemigo->aparecerPorIzquierda();
	}*/
	this->enemigosInactivos.insert(pair<int, Enemigo*>(500,enemigo));
}

void EscenarioS::activarEnemigos(int posXAbsolutaJugador, list<mensajeStruct>* mainList) {
	Enemigo *enemigo = NULL;
	std::multimap<int,Enemigo*>::iterator it, itLow, itUp;

	itLow = this->enemigosInactivos.lower_bound(0);
	itUp = this->enemigosInactivos.upper_bound(posXAbsolutaJugador);
	for (it = itLow; it != itUp; it++) {
		enemigo = it->second;
		this->enemigosInactivos.erase(it);
		this->enemigosVivos[enemigo->getCodEnemigo()] = enemigo;
		mainList->push_back(getMensajeEnemigoNuevo(enemigo));
	}
}
void EscenarioS::moverBonuses(list<mensajeStruct>* mainList) {
	bool encontro = true;

	while (encontro){
		encontro = false;
		int id;
		for (map<int, bonus>::iterator  it = this->bonusInactivos.begin(); it != this->bonusInactivos.end(); it++) {
			if (it->second.posXAbs >= this->avance && it->second.posXAbs <= this->avance + this->ancho){
				encontro = true;
				id = it->first;
				it->second.posX=it->second.posXAbs - this->avance;
				this->bonusEnPantalla[id] = it->second;
				mainList->push_back(getMensajeBonusNew(it->second,id));
			}
		}
		if (encontro)
			this->bonusInactivos.erase(id);
	}

	encontro = true;
	while (encontro){
		encontro = false;
		int id;
		for (map<int, bonus>::iterator  it = this->bonusEnPantalla.begin(); it != this->bonusEnPantalla.end(); it++) {
			it->second.posX=it->second.posXAbs - this->avance;
			if (it->second.posX + 70 < 0){
				//Fuera de la pantalla
				encontro = true;
				id = it->first;
				break;
			}else{
				mainList->push_back(getMensajeBonusUpd(it->second,it->first));
			}
		}
		if (encontro){
			this->eliminarBonus(mainList,id);
		}
	}
}

void EscenarioS::eliminarBonus(list<mensajeStruct>* mainList, int idBonus){
	mainList->push_back(getMensajeBonusDel(idBonus));
	this->bonusEnPantalla.erase(idBonus);
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
void EscenarioS::addBala(list<Bala*> bala){
	this->balas.splice(this->balas.end(), bala);
}

void EscenarioS::moverBala(){

	list<Bala*>::iterator it;
	list<Bala*>::iterator itDelete;

	bool afuera = true;
	for (it=balas.begin(); it!=balas.end(); ++it){
	(*it)->mover();
	(*it)->movimientos +=1;
	}

	while(afuera){
		afuera =false;
	for (it=balas.begin(); it!=balas.end(); ++it){

		if((*it)->x>this->ancho || (*it)->x< 0 || (*it)->y < 0 || ( (*it)->tipoDeBala == SHOOTGUN && (*it)->movimientos > 10)){
		afuera = true;
		itDelete = it;
		}

    }
	if(afuera){

	balas.erase(itDelete);
	delete (*itDelete);
	}
	}


}


list<mensajeStruct> EscenarioS::moverJugador(int jugadorId, string mensaje) {
	Jugador* jugador = this->mapJugadores[jugadorId];
	vector<string> result = splitE(mensaje, ';');
	int vecesX = atoi(result[0].c_str());
	string estado = result[1];

	list<mensajeStruct> returnList;
	map<string, Enemigo*>::iterator itEnemigos;
	Enemigo *enemigo = NULL;

	if(estado=="DISPARO"){
		int direccion = atoi(result[2].c_str());
		this->addBala(jugador->disparar(aimDirection(direccion)));
		// PARA PROBAR
		//this->matarEnemigos(&returnList);
	}
	if(estado=="RESET"){
		mensajeStruct msjReset;
		msjReset.tipo = RESET;
		msjReset.objectId = "X0";
		msjReset.message = "RESET";
		returnList.push_back(msjReset);
		this->resetEscenario();
	}else if(estado=="NEXT_LEVEL"){
		if (this->nivel == this->cantNiveles){
			mensajeStruct msjReset;
			msjReset.tipo = RESET;
			msjReset.objectId = "X0";
			msjReset.message = "RESET";
			returnList.push_back(msjReset);
			this->resetEscenario();
		}else{
			mensajeStruct msjReset;
			msjReset.tipo = NEXT_LEVEL;
			msjReset.objectId = "X0";
			msjReset.message = "NEXT_LEVEL";
			returnList.push_back(msjReset);
			this->pasarDeNivel();
		}
	}else{
		jugador->mover(this->ancho,vecesX, estado);

		//ESTO ES PARA PROBAR
		//jugador->puntaje += 1;
		//jugador->vida -= 1;

		//if (jugador->vida == 0) {jugador->vida=100; jugador->municiones = 200;}
		//if (jugador->vida >80 ) jugador->municiones=-1;
		//if (jugador->vida ==80 ) jugador->municiones=300;
		//if (jugador->vida <80 ) jugador->municiones-=2;


		if (!this->avanceBloqueado) {
			moverEscenario(&returnList);
		}
		returnList.push_back(getMensajeJugador(jugador));
		returnList.push_back(getMensajeEscenario());


		activarEnemigos(this->avance + jugador->getPosX(), &returnList);
		moverBonuses(&returnList);

		this->avanceBloqueado = false;
		for (itEnemigos = this->enemigosVivos.begin(); itEnemigos != this->enemigosVivos.end(); itEnemigos++) {
			enemigo = itEnemigos->second;
			enemigo->mover(this->ancho);
			if (enemigo->estaBloqueadoElAvanceDelEscenario(this->ancho)) {
				this->avanceBloqueado = true;
			}
			returnList.push_back(getMensajeEnemigoUpdate(enemigo));
		}
		if(!this->balas.empty()){
			moverBala();
			list<mensajeStruct> balasUpdate = getMensajeBala();
			returnList.splice(returnList.end(), balasUpdate);

		}

		//evaluar colisiones despues del movimiento
		colisionar(&returnList);

		//Siempre false para poder probar
		if(jugador->vida <= 0){
			if (!jugador->gameOver){
				jugador->gameOver=true;
				bool gameOverAll = true;
				for (map<int,Jugador*>::iterator jugador=this->mapJugadores.begin(); jugador!=this->mapJugadores.end(); ++jugador){
					if (!jugador->second->gameOver) gameOverAll = false;
				}

				mensajeStruct msjReset;
				msjReset.tipo = gameOverAll?GAME_OVER_ALL:GAME_OVER_PLAYER;
				msjReset.objectId = jugador->getCodJugador();
				msjReset.message = "GAME OVER";
				returnList.push_back(msjReset);
			}
		}

		//End of the level
		if (this->avance > 2000 && !endOfLevel){
			returnList.push_back(getMensajeEndOfLevel());
			endOfLevel=true;
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
	map<string, Enemigo*>::iterator itEnemigos;
	Enemigo *enemigo = NULL;

	for (map<int,Jugador*>::iterator jugador=this->mapJugadores.begin(); jugador!=this->mapJugadores.end(); ++jugador){
		if (jugador->second->activo()) {
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
			if (!jugador->second->activo() && posActual < 0) {
				jugador->second->setPosX(0);
			}
			else {
				jugador->second->setPosX(posActual);
			}
			mainList->push_back(getMensajeJugador(jugador->second));
		}
		this->avance += minPosX;

		for (itEnemigos = this->enemigosVivos.begin(); itEnemigos != this->enemigosVivos.end(); itEnemigos++) {
			enemigo = itEnemigos->second;
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

string convertirAString(int nro){
	stringstream nroS;
	nroS<<nro;
	return nroS.str();
}

mensajeStruct EscenarioS::getMensajeBonusNew(bonus bonus, int idBonus){
	mensajeStruct msjBonus;
	msjBonus.tipo = BONUS_NEW;
	msjBonus.objectId = convertirAString(idBonus);
	msjBonus.message = convertirAString(bonus.posX)+";"+convertirAString(bonus.posY)+";"+convertirAString(bonus.type);
	return msjBonus;
}
mensajeStruct EscenarioS::getMensajeBonusUpd(bonus bonus, int idBonus){
	mensajeStruct msjBonus;
	msjBonus.tipo = BONUS_UPD;
	msjBonus.objectId = convertirAString(idBonus);
	msjBonus.message = convertirAString(bonus.posX)+";"+convertirAString(bonus.posY)+";"+convertirAString(bonus.type);
	return msjBonus;
}
mensajeStruct EscenarioS::getMensajeBonusDel(int idBonus){
	mensajeStruct msjBonus;
	msjBonus.tipo = BONUS_DEL;
	msjBonus.objectId = convertirAString(idBonus);
	msjBonus.message = "DELETE BONUS";
	return msjBonus;
}
mensajeStruct EscenarioS::getMensajeEnemigoMuerto(Enemigo *enemigo){
	mensajeStruct msjEnemigo;

	msjEnemigo.tipo = ENEMIGO_DELETE;
	msjEnemigo.objectId = enemigo->getCodEnemigo();;
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
list<mensajeStruct> EscenarioS::getMensajeBala(){


	list<mensajeStruct> msjRespuesta;
	string mensaje;
	list<Bala*>::iterator it;

	it=balas.begin();

	while(it!=balas.end()){
		int cantBalas = 0;
		for(int j=0;(j<8 && it!=balas.end());j++){
			stringstream posx;
			stringstream posy;
			posx<<(*it)->x;
			posy<<(*it)->y;
			mensaje+=posx.str()+";"+posy.str()+";";
			cantBalas= j+1;
			++it;

		}

		stringstream cantidadBalas;
		cantidadBalas  << cantBalas;
		mensajeStruct msjBala;
		msjBala.tipo = BALA_UPD;
		msjBala.message = cantidadBalas.str() + ";" + mensaje;
		mensaje="";
		msjRespuesta.push_front(msjBala);

	}

	return msjRespuesta;
}
mensajeStruct EscenarioS::getMensajeEndOfLevel(){
	string mensaje="";

	map<int,string> puntajesJugOrd;
	map<string,int> puntajeEquipos;
	map<int,string> puntajeEquiposOrd;

	//Armo un mapa con los puntajes de los jugadores y acumulo en un mapa los equipos
	for (map<int,Jugador*>::iterator jugador=this->mapJugadores.begin(); jugador!=this->mapJugadores.end(); ++jugador){
		puntajesJugOrd[jugador->second->puntaje] = jugador->second->usuario->getNombre();

		if ( puntajeEquipos.find(jugador->second->equipo) == puntajeEquipos.end() ) {
			puntajeEquipos[jugador->second->equipo] = 0;
		}
		puntajeEquipos[jugador->second->equipo] += jugador->second->puntaje;
	}

	//paso los puntajes de los equipos a un mapa con key del puntaje para que ordene
	for (map<string,int>::iterator equipo=puntajeEquipos.begin(); equipo!=puntajeEquipos.end(); ++equipo){
		puntajeEquiposOrd[equipo->second] = equipo->first;
	}



	bool concat = false;
	for (map<int,string>::reverse_iterator jugador=puntajesJugOrd.rbegin(); jugador!=puntajesJugOrd.rend(); ++jugador){
		if (concat){
			mensaje += ";";
		}else concat = true;
		stringstream puntaje;
		puntaje<<(jugador->first);
		mensaje+= jugador->second+"-"+puntaje.str();
	}

	//separador de puntos de jugador y de equipo
	mensaje += "#";
	concat = false;
	for (map<int,string>::reverse_iterator equipo=puntajeEquiposOrd.rbegin(); equipo!=puntajeEquiposOrd.rend(); ++equipo){
		if (concat){
			mensaje += ";";
		}else concat = true;
		stringstream puntaje;
		puntaje<<(equipo->first);
		mensaje+= equipo->second +"-"+puntaje.str();
	}

	mensajeStruct msjEOL;
	msjEOL.tipo = END_OF_LEVEL;
	msjEOL.objectId=(this->nivel == this->cantNiveles)?"GAME":"LEVEL";
	msjEOL.message = mensaje;
	return msjEOL;
}

void EscenarioS::resetEscenario(){
	this->avance = 0;
	this->nivel=1;
	this->endOfLevel=false;
	for (map<int,Jugador*>::iterator jugador=this->mapJugadores.begin(); jugador!=this->mapJugadores.end(); ++jugador){
		jugador->second->reiniciar();
	}
	for (map<int, bonus>::iterator  itOb = this->bonusEnPantalla.begin(); itOb != this->bonusEnPantalla.end(); itOb++) {
		itOb->second={};
	}
	this->bonusEnPantalla.clear();
	for (map<int, bonus>::iterator  itOb = this->bonusInactivos.begin(); itOb != this->bonusInactivos.end(); itOb++) {
		itOb->second={};
	}
	this->bonusInactivos.clear();
}

void EscenarioS::pasarDeNivel(){
	this->nivel++;
	this->avance = 0;
	this->endOfLevel=false;
	for (map<int,Jugador*>::iterator jugador=this->mapJugadores.begin(); jugador!=this->mapJugadores.end(); ++jugador){
		jugador->second->moverAPosicionInicial();
	}
	for (map<int, bonus>::iterator  itOb = this->bonusEnPantalla.begin(); itOb != this->bonusEnPantalla.end(); itOb++) {
		itOb->second={};
	}
	this->bonusEnPantalla.clear();
	for (map<int, bonus>::iterator  itOb = this->bonusInactivos.begin(); itOb != this->bonusInactivos.end(); itOb++) {
		itOb->second={};
	}
	this->bonusInactivos.clear();
}

void EscenarioS::colisionar(list<mensajeStruct>* mainList) {

	list<Bala*>::iterator itBalas;
	Bala *bala = NULL;

	Jugador *jugador;

	map<string, Enemigo*>::iterator itEnemigos;
	Enemigo *enemigo;

	for (itBalas = balas.begin(); itBalas != balas.end(); itBalas++) {
		bala = (*itBalas);

		for (map<int,Jugador*>::iterator itJugador=mapJugadores.begin(); itJugador!=mapJugadores.end(); itJugador++){
			jugador = itJugador->second;
			if (jugador->conectado()) {
				//si la bala es del enemigo
				if (bala->IdJugador == NULL) {
					if (Colision::colisionSoldadoConBala(jugador->posX, jugador->posY,jugador->ancho/2,jugador->alto,bala->x,bala->y,bala->radio,bala->direccion)) {
						cout<<"Restar vida al jugador"<<endl;
						jugador->restarVida(10);
					}
				}

				for (itEnemigos = enemigosVivos.begin(); itEnemigos != enemigosVivos.end(); itEnemigos++) {
					enemigo = itEnemigos->second;
					//si la bala es del jugador
					if (bala->IdJugador != NULL) {
						if (Colision::colisionSoldadoConBala(enemigo->posX, enemigo->posY,enemigo->ancho/2,enemigo->alto,bala->x,bala->y,bala->radio,bala->direccion)) {
							cout<<"Restar vida al enemigo"<<endl;
							matarEnemigo(mainList, enemigo->getCodEnemigo());
							Jugador *jugadorDisparo = this->mapJugadores[bala->IdJugador];
							jugadorDisparo->sumarPuntos();
						}
					} else if (Colision::colisionSoldadoConSoldado(jugador->posX, jugador->posY,jugador->ancho/2,jugador->alto,enemigo->posX, enemigo->posY,enemigo->ancho/2,enemigo->alto)) {
								//si siguen vivos, si en los pasos anteriores no los mato una bala
								cout<<"cuchillazo del enemigo"<<endl;
								jugador->restarVida(1);
						   }
				}
				findBonus(mainList, jugador);
			}
		}
	}

	if (bala == NULL) {
		for (map<int,Jugador*>::iterator itJugador=mapJugadores.begin(); itJugador!=mapJugadores.end(); ++itJugador){
			jugador = itJugador->second;
			if (jugador->conectado()) {
				for (itEnemigos = enemigosVivos.begin(); itEnemigos != enemigosVivos.end(); itEnemigos++) {
					enemigo = itEnemigos->second;
					if (Colision::colisionSoldadoConSoldado(jugador->posX, jugador->posY,jugador->ancho/2,jugador->alto,enemigo->posX, enemigo->posY,enemigo->ancho/2,enemigo->alto)) {
						cout<<"cuchillazo del enemigo"<<endl;
						jugador->restarVida(1);
					}
				}
				findBonus(mainList, jugador);
			}
		}
	}
}

void EscenarioS::findBonus(list<mensajeStruct>* mainList, Jugador *jugador) {
	int id = 0;
	for (map<int, bonus>::iterator itBonus=bonusEnPantalla.begin(); itBonus!=bonusEnPantalla.end(); itBonus++) {
		if (Colision::colisionSoldadoConBonus(jugador->posX, jugador->posY,jugador->ancho/2,jugador->alto,itBonus->second.posX, itBonus->second.posY,30,30)) {
			weapon armaBonus;
			switch (itBonus->second.type) {
				case MACHINEG:
					cout<<"BONUS: Tipo De Arma: MACHINEGUN"<<endl;
					armaBonus = MACHINEGUN;
					jugador->cambiarTipoDeArma(armaBonus);
				break;
				case SHOTG:
					cout<<"BONUS: Tipo De Arma: SHOOTGUN"<<endl;
					armaBonus = SHOOTGUN;
					jugador->cambiarTipoDeArma(armaBonus);
				break;
				case POWER:
					cout<<"BONUS: Restablece Vida"<<endl;
					jugador->reiniciarVida();
				break;
				case KILL_ALL:
					cout<<"BONUS: Matar A Todos Los Enemigos"<<endl;
					matarEnemigos(mainList);
				break;
			}
			id = itBonus->first;
			break;//salgo del for porq no hay mas de un bonus en la misma posicion(en un mismo movimiento del jugador)
		}
	}

	if (id != 0){
		eliminarBonus(mainList,id);
	}
}

void EscenarioS::matarEnemigo(list<mensajeStruct>* mainList, string id) {
	Enemigo *enemigo = NULL;
	map<string, Enemigo*>::iterator itEnemigos = this->enemigosVivos.find(id);
	// Si el objeto esta en el map
	if ( itEnemigos != this->enemigosVivos.end() ) {
		enemigo = itEnemigos->second;
		mainList->push_back(getMensajeEnemigoMuerto(enemigo));
		delete enemigo;
		this->enemigosVivos.erase(itEnemigos);
	}
}

void EscenarioS::matarEnemigos(list<mensajeStruct>* mainList) {
	Enemigo *enemigo = NULL;
	// Si el objeto esta en el map
	for (map<string, Enemigo*>::iterator it = this->enemigosVivos.begin(); it != this->enemigosVivos.end(); it++) {
		enemigo = it->second;
		mainList->push_back(getMensajeEnemigoMuerto(enemigo));
		delete enemigo;
		this->enemigosVivos.erase(it);
	}
}
