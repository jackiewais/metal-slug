#include "SoldadoS.h"


void SoldadoS::moverDerecha(){
	posX += velocidad;
	if (posX + anchoSold > anchoEscenario){
		posX = anchoEscenario - anchoSold;
	}
}
void SoldadoS::moverIzquierda(){
	posX -= velocidad;
	if(posX < 0){
		posX = 0;
	}
}
