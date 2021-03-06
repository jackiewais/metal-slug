#ifndef SRC_SERVIDOR_MODELO_ESCENARIOS_H_
#define SRC_SERVIDOR_MODELO_ESCENARIOS_H_
#include <stdio.h>
#include <iostream>
#include <queue>
#include <map>
#include <list>
#include "Jugador.h"
#include "Enemigo.h"
#include "EnemigoAirbusterRiberts.h"
#include "EnemigoTaniOh.h"
#include "EnemigoHiDo.h"
#include "../../Common/MensajeStruct.h"
#include "../../Common/Mensajeria.h"
#include "Bala.h"
//SILVIA
#include "Plataforma.h"

class EscenarioS {

private:
	int distancia;
	int avance;
	bool avanceBloqueado;
	void colisionar(list<mensajeStruct>* mainList);
	void findBonus(list<mensajeStruct>* mainList, Jugador *jugador);

public:
	//SILVIA
    map<int, Plataforma*> PlataformasActivas;
    map<int, Plataforma*> PlataformasInactivos;

	multimap<int, Enemigo*> enemigosInactivos;
	map<string, Enemigo*> enemigosVivos;

	int cantidadNada = 0;
	int ancho;
	int alto;
	int margen;
	map<int, Jugador*> mapJugadores;
	//BALAS
	//list<Bala> *balas;
	list<Bala*> balas;
	void addBala(list<Bala*> bala);
	void moverBala();
	EscenarioS(int ancho, int alto);
	virtual ~EscenarioS();
	Jugador* getJugadorById(int id);
	void addJugador(Jugador* jugador);
	void addEnemigoInactivo(enemigoStruct enemigoStruct);
	void herirEnemigo(list<mensajeStruct>* mainList, string id, Bala *bala);
	void matarEnemigos(list<mensajeStruct>* mainList);
	void activarEnemigos(int posXAbsolutaJugador, list<mensajeStruct>* mainList);
	list<mensajeStruct>  moverJugador(int idJugador, string mensaje);
	void moverEscenario(list<mensajeStruct>* mainList);
	mensajeStruct getMensajeJugador(Jugador* jugador);
	mensajeStruct getMensajeEscenario();
	mensajeStruct getMensajeEnemigoNuevo(Enemigo *enemigo);
	mensajeStruct getMensajeEnemigoUpdate(Enemigo *enemigo);
	void moverBonuses(list<mensajeStruct>* mainList);
	mensajeStruct getMensajeBonusNew(bonus bonus, int idBonus);
	mensajeStruct getMensajeBonusUpd(bonus bonus, int idBonus);
	mensajeStruct getMensajeBonusDel(int idBonus);
	void eliminarBonus(list<mensajeStruct>* mainList, int idBonus);
	list<mensajeStruct> getMensajeBala();
	mensajeStruct getMensajeEnemigoMuerto(Enemigo *enemigo);
	mensajeStruct getMensajeEndOfLevel();
	void aceptarCambios();
	mensajeStruct getMensajeDesconexion(int jugadorId);
	void limpiarListas();
	void resetEscenario();
	void pasarDeNivel();
	list<mensajeStruct> actualizar();
	bool endOfLevel=false;
	int nivel=1;
	int cantNiveles=3;
	map<int, bonus> bonusInactivos;
	map<int, bonus> bonusEnPantalla;
	int velocidadBala;
	//SILVIA
	void eliminarPlataforma(int id);
	void addPlataformaInactivo(Plataforma* plataforma, int posXAbsolutaDePlataformaParaAparicion);
    Plataforma* activarPlataforma(int posXAbsolutaPlataforma);
	mensajeStruct getMensajePlataformaNuevo(Plataforma *plataforma);
	mensajeStruct getMensajePlataformaUpdate(Plataforma *plataforma);
	mensajeStruct getMensajePlataformaEliminada(Plataforma *plataforma);
	mensajeStruct getMensajeEliminarPlataforma(Plataforma *plataforma);
	int tiempoDisparoEnemigo = 0;
};

#endif /* SRC_SERVIDOR_MODELO_ESCENARIOS_H_ */
