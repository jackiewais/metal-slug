#include "ObjetoGraficable.h"

ObjetoGraficable::ObjetoGraficable(std::string id, LTexture *textura, int x, int y) {
	this->id = id;
	this->textura = textura;
	this->x = x;
	this->y = y;
	this->factorParallax = 0;
	this->grisado = false;
	this->estadoActual = SIN_ESTADO;
	this->iteradorDeItEstado = 0;
	//this->posMozaico = this->getAncho();
}

ObjetoGraficable::~ObjetoGraficable() {
	// TODO Auto-generated destructor stub
}

void ObjetoGraficable::actualizarPosicion(int x, int y) {
	this->x = x;
	this->y = y;
}

void ObjetoGraficable::render(){

	if ( (this->factorParallax == 0) ) {
		if (this->estadoActual == SIN_ESTADO) {
			this->textura->render(this->x, this->y);
		} else {
			this->textura->render(this->x, this->y, &*(this->itEstado));
		}
	}else{
		if(this->x + posMozaico <-this->textura->getWidth()){
			posMozaico+=this->textura->getWidth();

		}

		this->textura->render(this->x + posMozaico, this->y);
		this->textura->render(this->x + posMozaico + this->textura->getWidth(), this->y);
	}




}

int ObjetoGraficable::getAncho() {
	return this->textura->getWidth();
}

void ObjetoGraficable::setFactorParallax(int despA, int anchoVentana) {
	int desp = this->textura->getWidth() - anchoVentana;
	double desp1 = double(desp);
	double desp2 = double(despA);
	double factorP =round(desp1 / desp2);

	this->factorParallax = factorP;
}

void ObjetoGraficable::actualizarPosicionFondo(int despA) {
	this->actualizarPosicion(despA*this->factorParallax, this->y);
}


void ObjetoGraficable::actualizarGrisado(){
	if (flagGrisado != this->grisado){
		int alpha = (this->grisado)?128:255;
		this->textura->setAlpha(alpha);
		flagGrisado = this->grisado;
	}
}
void ObjetoGraficable::setGrisado(bool grisa){
	if (grisa && !this->grisado){
		std::cout << "Jugador " << this->id << " desconectado" << endl;
	}
	this->grisado = grisa;
}

void ObjetoGraficable::actualizarEstado(estadoJugador estado) {
	if (this->estadoActual == estado) {
		this->iteradorDeItEstado++;
		if (this->iteradorDeItEstado >= 2) {
			this->iteradorDeItEstado = 0;
			this->itEstado++;
			if (this->itEstado == this->textura->mapFrames[estado]->end()) {
				this->itEstado = this->textura->mapFrames[estado]->begin();
			}
		}
	} else {
		this->estadoActual = estado;
		this->itEstado = this->textura->mapFrames[estado]->begin();
		this->iteradorDeItEstado = 0;
	}
}
