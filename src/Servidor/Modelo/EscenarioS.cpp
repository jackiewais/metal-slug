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

	//enemigo = new EnemigoTaniOh(id+1,5,508,252,this->alto,&this->mapJugadores);
	//this->enemigosInactivos.insert(pair<int, Enemigo*>(600,enemigo));
}

void EscenarioS::activarEnemigos(int posXAbsolutaJugador, list<mensajeStruct>* mainList) {
	Enemigo *enemigo = NULL;
	std::multimap<int,Enemigo*>::iterator it, itLow, itUp;

	itLow = this->enemigosInactivos.lower_bound(0);
	itUp = this->enemigosInactivos.upper_bound(posXAbsolutaJugador);
	for (it = itLow; it != itUp; it++) {
		enemigo = it->second;
		this->enemigosVivos[enemigo->getCodEnemigo()] = enemigo;
		mainList->push_back(getMensajeEnemigoNuevo(enemigo));
		this->enemigosInactivos.erase(it);
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
			if (it->second.posX!=it->second.posXAbs - this->avance){
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
		delete (*itDelete);
		balas.erase(itDelete);
	}
	}


}


list<mensajeStruct> EscenarioS::moverJugador(int jugadorId, string mensaje) {
	cout << "mover Jug " << jugadorId << " - " << mensaje << endl;
	Jugador* jugador = this->mapJugadores[jugadorId];
	list<mensajeStruct> returnList;

	if(mensaje == "0;NADA" && cantidadNada < 1 && !jugador->estaSaltando()){
		cantidadNada += 1;

	}else {
		cantidadNada = 0;


	vector<string> result = splitE(mensaje, ';');
	int vecesX = atoi(result[0].c_str());
	string estado = result[1];
/*
	map<string, Enemigo*>::iterator itEnemigos;
	Enemigo *enemigo = NULL;
*/
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

//INICIO SILVIA
				int posInicialP=0;
				int posFinalP=0;
				int posPiso=0;  //alto del escenario
				int medioJugador = jugador->getPosX() + (jugador->getAncho()/2);
				int medioPlataforma;
				int resultado = 800;
				//Obtengo la plataforma màs cercana al jugador
				map<int, Plataforma*>::iterator itP;
	            for (itP = this->PlataformasActivas.begin(); itP != this->PlataformasActivas.end(); itP++) {
					medioPlataforma = (*itP).second->getPosX() + ((*itP).second->getAncho()/2);
			        if ( abs(medioPlataforma - medioJugador) < resultado) {
				        posInicialP=(*itP).second->getPosX();
				        posFinalP=(*itP).second->getPosX()+(*itP).second->getAncho();
				        posPiso=(*itP).second->getPiso();
				        resultado = abs(medioPlataforma - medioJugador);
					}
				}

				jugador->setCoordPlataformaMasCercanaAlJugador(posInicialP,posFinalP,posPiso );
//FIN SILVIA

		jugador->mover(this->ancho,vecesX, estado);

		//ESTO ES PARA PROBAR
		//jugador->puntaje += 1;
		//jugador->vida -= 1;

		//if (jugador->vida == 0) {jugador->vida=100; jugador->municiones = 200;}
		//if (jugador->vida >80 ) jugador->municiones=-1;
		//if (jugador->vida ==80 ) jugador->municiones=300;
		//if (jugador->vida <80 ) jugador->municiones-=2;

		/*if(!this->balas.empty()){
						moverBala();
						list<mensajeStruct> balasUpdate = getMensajeBala();
						returnList.splice(returnList.end(), balasUpdate);

		}*/
		if (!this->avanceBloqueado) {
			moverEscenario(&returnList);
		}

		returnList.push_back(getMensajeJugador(jugador));
		returnList.push_back(getMensajeEscenario());


		activarEnemigos(this->avance + jugador->getPosX(), &returnList);
/*		moverBonuses(&returnList);

		this->avanceBloqueado = false;
		for (itEnemigos = this->enemigosVivos.begin(); itEnemigos != this->enemigosVivos.end(); itEnemigos++) {
			enemigo = itEnemigos->second;
			enemigo->mover(this->ancho);
			if (enemigo->estaBloqueadoElAvanceDelEscenario(this->ancho)) {
				this->avanceBloqueado = true;
			}
			returnList.push_back(getMensajeEnemigoUpdate(enemigo));
		}
*/
//SILVIA INICIO
		//Activa Nuevas Plataformas si se encuentran dentro de la ventana
		Plataforma *plataforma = NULL;
		plataforma = activarPlataforma(this->avance + jugador->getPosX());

		if (plataforma != NULL) {
			returnList.push_back(getMensajePlataformaNuevo(plataforma));
		}
		/*		//Nueva posiciòn de la plataforma activa en X enviado al cliente
		map<int, Plataforma*>::iterator it;
	    for (it = this->PlataformasActivas.begin(); it != this->PlataformasActivas.end(); it++) {
            plataforma = it->second;
	    	returnList.push_back(getMensajePlataformaUpdate(plataforma));
	    	//Si la plataforma se encuentra fuera de la ventana del lado izquierdo, se elimina y se elimina en el cliente
			if ((plataforma->getPosX() + plataforma->getAncho()) < 0){
				//eliminarPlataforma(it->first);
				returnList.push_back(getMensajeEliminarPlataforma(plataforma));
				this->PlataformasActivas.erase(it);
			}
		}*/
//FIN SILVIA

		//evaluar colisiones despues del movimiento
		//colisionar(&returnList);

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
/*
		//End of the level
		if (this->avance > 2000 && !endOfLevel){
			returnList.push_back(getMensajeEndOfLevel());
			endOfLevel=true;
		}*/


	}
	}
	return returnList;
}

list<mensajeStruct> EscenarioS::actualizar(){

	list<mensajeStruct> returnList;
	map<string, Enemigo*>::iterator itEnemigos;
	Enemigo *enemigo = NULL;


	if(!this->balas.empty()){
	moverBala();
	list<mensajeStruct> balasUpdate = getMensajeBala();
	returnList.splice(returnList.end(), balasUpdate);
	}

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
		Plataforma *plataforma = NULL;
			//Nueva posiciòn de la plataforma activa en X enviado al cliente
			map<int, Plataforma*>::iterator it;
		    for (it = this->PlataformasActivas.begin(); it != this->PlataformasActivas.end(); it++) {
	            plataforma = it->second;
		    	returnList.push_back(getMensajePlataformaUpdate(plataforma));
		    	//Si la plataforma se encuentra fuera de la ventana del lado izquierdo, se elimina y se elimina en el cliente
				if ((plataforma->getPosX() + plataforma->getAncho()) < 0){
					//eliminarPlataforma(it->first);
					returnList.push_back(getMensajeEliminarPlataforma(plataforma));
					this->PlataformasActivas.erase(it);
				}
			}
	colisionar(&returnList);
SDL_Delay(20);
return returnList;
};


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
//INICIO SILVIA
		//Se mueve la posiciòn de la plataforma
		map<int,Plataforma*>::iterator it;
		Plataforma *plataforma = NULL;
        for (it = this->PlataformasActivas.begin(); it != this->PlataformasActivas.end(); it++) {
			plataforma = (*it).second;
			plataforma->retrocederSegunAvanceEscenario(this->distancia);
		}
//FIN SILVIA
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
		for(int j=0;(j<5 && it!=balas.end());j++){
			stringstream posx;
			stringstream posy;
			stringstream tipo;
			stringstream direccion;
			posx<<(*it)->x;
			posy<<(*it)->y;
			tipo<<(*it)->tipoDeBala;
			direccion<<(*it)->direccion;
		    mensaje+=posx.str()+";"+posy.str()+";"+tipo.str()+";"+direccion.str()+";";
		   // mensaje+=posx.str()+";"+posy.str()+";";
			cantBalas= j+1;
			++it;

		}

		stringstream cantidadBalas;
		cantidadBalas  << cantBalas;
		mensajeStruct msjBala;
		msjBala.tipo = BALA_UPD;
		msjBala.objectId="B0";
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

void EscenarioS::limpiarListas(){
	for (map<int, bonus>::iterator  itOb = this->bonusEnPantalla.begin(); itOb != this->bonusEnPantalla.end(); itOb++) {
		itOb->second={};
	}
	this->bonusEnPantalla.clear();
	for (map<int, bonus>::iterator  itOb = this->bonusInactivos.begin(); itOb != this->bonusInactivos.end(); itOb++) {
		itOb->second={};
	}
	this->bonusInactivos.clear();
	for (multimap<int, Enemigo*>::iterator  itOb = this->enemigosInactivos.begin(); itOb != this->enemigosInactivos.end(); itOb++) {
		delete itOb->second;
	}
	this->enemigosInactivos.clear();
	for (multimap<string, Enemigo*>::iterator  itOb = this->enemigosVivos.begin(); itOb != this->enemigosVivos.end(); itOb++) {
		delete itOb->second;
	}
	this->enemigosVivos.clear();
	list<Bala*>::iterator it;
	for(it=this->balas.begin();it!=this->balas.end();++it){
		delete (*it);
	}
	this->balas.clear();

	for (map<int, Plataforma*>::iterator  itOb = this->PlataformasActivas.begin(); itOb != this->PlataformasActivas.end(); itOb++) {
		delete itOb->second;
	}
	this->PlataformasActivas.clear();

	for (map<int, Plataforma*>::iterator  itOb = this->PlataformasInactivos.begin(); itOb != this->PlataformasInactivos.end(); itOb++) {
		delete itOb->second;
	}
	this->PlataformasInactivos.clear();

}


void EscenarioS::resetEscenario(){
	this->avance = 0;
	this->nivel=1;
	this->endOfLevel=false;
	for (map<int,Jugador*>::iterator jugador=this->mapJugadores.begin(); jugador!=this->mapJugadores.end(); ++jugador){
		jugador->second->reiniciar();
	}
	limpiarListas();
}

void EscenarioS::pasarDeNivel(){
	this->nivel++;
	this->avance = 0;
	this->endOfLevel=false;
	for (map<int,Jugador*>::iterator jugador=this->mapJugadores.begin(); jugador!=this->mapJugadores.end(); ++jugador){
		jugador->second->moverAPosicionInicial();
	}
	limpiarListas();
}

void EscenarioS::colisionar(list<mensajeStruct>* mainList) {

	list<Bala*>::iterator itBalas;
	Bala *bala = NULL;

	Jugador *jugador;

	map<string, Enemigo*>::iterator itEnemigos;
	Enemigo *enemigo;

	list<Bala*>balasEliminadas;
	bool eliminarBala;

	for (itBalas = balas.begin(); itBalas != balas.end(); itBalas++) {
		bala = (*itBalas);

		eliminarBala = false;

		for (map<int,Jugador*>::iterator itJugador=mapJugadores.begin(); itJugador!=mapJugadores.end(); itJugador++){
			jugador = itJugador->second;
			if (jugador->conectado()) {
				if(!eliminarBala) {
					//si la bala es del enemigo
					if (bala->IdJugador == NULL) {
						if (Colision::colisionSoldadoConBala(jugador->posX, jugador->posY,jugador->ancho,jugador->alto,bala->x,bala->y,bala->radio,bala->direccion)) {
							cout<<"Restar vida al jugador"<<endl;
							jugador->restarVida(10);
							balasEliminadas.push_back(bala);
							eliminarBala = true;
						}
					}
				}


				for (itEnemigos = enemigosVivos.begin(); itEnemigos != enemigosVivos.end(); itEnemigos++) {
					enemigo = itEnemigos->second;
					if(!eliminarBala) {
						//si la bala es del jugador
						if (bala->IdJugador != NULL) {
							if(!enemigo->esEnemigoFinal()) {
								if (Colision::colisionSoldadoConBala(enemigo->posX, enemigo->posY,enemigo->ancho,enemigo->alto,bala->x,bala->y,bala->radio,bala->direccion)) {
									herirEnemigo(mainList, enemigo->getCodEnemigo(), bala);
									Jugador *jugadorDisparo = this->mapJugadores[bala->IdJugador];
									jugadorDisparo->sumarPuntos();
									balasEliminadas.push_back(bala);
									eliminarBala = true;
								}
							}else {
								if (Colision::colisionAirbusterRibertsConBala(enemigo->posX, enemigo->posY,enemigo->ancho,enemigo->alto,bala->x,bala->y,bala->radio)) {
									herirEnemigo(mainList, enemigo->getCodEnemigo(), bala);
									Jugador *jugadorDisparo = this->mapJugadores[bala->IdJugador];
									jugadorDisparo->sumarPuntos();
									balasEliminadas.push_back(bala);
									eliminarBala = true;
								}
							}
						}

					} else if (Colision::colisionSoldadoConSoldado(jugador->posX, jugador->posY,jugador->ancho,jugador->alto,enemigo->posX, enemigo->posY,enemigo->ancho,enemigo->alto)) {
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
					if (Colision::colisionSoldadoConSoldado(jugador->posX, jugador->posY,jugador->ancho,jugador->alto,enemigo->posX, enemigo->posY,enemigo->ancho,enemigo->alto)) {
						cout<<"cuchillazo del enemigo"<<endl;
						jugador->restarVida(1);
					}
				}
				findBonus(mainList, jugador);
			}
		}
	}else {
		//elimino las balas
		list<Bala*>::iterator itBalasEliminadas;
		list<Bala*>::iterator itDelete;

		while(!balasEliminadas.empty()) {

			for (itBalasEliminadas = balasEliminadas.begin(); itBalasEliminadas != balasEliminadas.end(); itBalasEliminadas++) {
				itDelete = itBalasEliminadas;
				balas.remove(*itBalasEliminadas);
				break;
			}

			delete (*itDelete);
			balasEliminadas.erase(itDelete);
		}
	}
}

void EscenarioS::findBonus(list<mensajeStruct>* mainList, Jugador *jugador) {
	int id = 0;
	for (map<int, bonus>::iterator itBonus=bonusEnPantalla.begin(); itBonus!=bonusEnPantalla.end(); itBonus++) {
		if (Colision::colisionSoldadoConBonus(jugador->posX, jugador->posY,jugador->ancho,jugador->alto,itBonus->second.posX, itBonus->second.posY,30,30)) {
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
			jugador->sumarPuntosBonus();
			id = itBonus->first;
			break;//salgo del for porq no hay mas de un bonus en la misma posicion(en un mismo movimiento del jugador)
		}
	}

	if (id != 0){
		eliminarBonus(mainList,id);
	}
}

void EscenarioS::herirEnemigo(list<mensajeStruct>* mainList, string id, Bala *bala) {
	Enemigo *enemigo = NULL;
	map<string, Enemigo*>::iterator itEnemigos = this->enemigosVivos.find(id);
	// Si el objeto esta en el map
	if ( itEnemigos != this->enemigosVivos.end() ) {
		enemigo = itEnemigos->second;
		if ( enemigo->restarVida(bala->tipoDeBala ) ) {
			mainList->push_back(getMensajeEnemigoMuerto(enemigo));
			if(enemigo->esEnemigoFinal()) {
				mainList->push_back(getMensajeEndOfLevel());
				endOfLevel=true;
			}
			delete enemigo;
			this->enemigosVivos.erase(itEnemigos);
		}
	}
}

void EscenarioS::matarEnemigos(list<mensajeStruct>* mainList) {
	Enemigo *enemigo = NULL;
	// Si el objeto esta en el map
	bool elimina = true;
	string key;
	while(elimina){
		elimina = false;
		for (map<string, Enemigo*>::iterator it = this->enemigosVivos.begin(); it != this->enemigosVivos.end(); it++) {
			enemigo = it->second;
			if(!enemigo->esEnemigoFinal()) {
				mainList->push_back(getMensajeEnemigoMuerto(enemigo));
				//delete enemigo;
				elimina = true;
				key = it->first;
			}
		}
		if (elimina){
			//delete enemigo;
			this->enemigosVivos.erase(key);
		}
	}
}
//SILVIA

mensajeStruct EscenarioS::getMensajePlataformaNuevo(Plataforma *plataforma){
	mensajeStruct msjPlataforma;

	msjPlataforma.tipo = PLATAFORMA_NEW;
	msjPlataforma.objectId = plataforma->getCodPlataforma();
	msjPlataforma.message = plataforma->getStringMensajeNew();
	return msjPlataforma;
}
mensajeStruct EscenarioS::getMensajePlataformaUpdate(Plataforma *plataforma){
	mensajeStruct msjPlataforma;

	msjPlataforma.tipo = PLATAFORMA_UPD;
	msjPlataforma.objectId = plataforma->getCodPlataforma();
	msjPlataforma.message = plataforma->getStringMensajeUpdate();
	return msjPlataforma;
}
mensajeStruct EscenarioS::getMensajeEliminarPlataforma(Plataforma *plataforma){
	mensajeStruct msjPlataforma;

	msjPlataforma.tipo = PLATAFORMA_DEL;
	msjPlataforma.objectId = plataforma->getCodPlataforma();
	msjPlataforma.message="";

	return msjPlataforma;
}
//SILVIA

void EscenarioS::addPlataformaInactivo(Plataforma* plataforma, int posX) {
	if ( this->PlataformasInactivos.find(posX) != this->PlataformasInactivos.end() ) {
		this->PlataformasInactivos[posX] = plataforma;
	} else {
		this->PlataformasInactivos[posX] = plataforma;
    }
}
Plataforma* EscenarioS::activarPlataforma(int posXAbsolutaJugador) {
	Plataforma *plataforma = NULL;
	if ( this->PlataformasInactivos.find(posXAbsolutaJugador) != this->PlataformasInactivos.end() ) {
		plataforma = this->PlataformasInactivos[posXAbsolutaJugador];
		this->PlataformasInactivos.erase(posXAbsolutaJugador);
		this->PlataformasActivas[posXAbsolutaJugador]=plataforma;
	}
	return plataforma;
}
void EscenarioS::eliminarPlataforma(int id) {
	map<int, Plataforma*>::iterator itPlataforma = this->PlataformasActivas.find(id);
	this->PlataformasActivas.erase(itPlataforma);

}
