#include "ObjetoGraficable.h"

ObjetoGraficable::ObjetoGraficable(std::string id, LTexture *textura, int x, int y) {
	this->id = id;
	this->textura = textura;
	this->x = x;
	this->y = y;
	this->factorParallax = 0;
	this->grisado = false;
}

ObjetoGraficable::~ObjetoGraficable() {
	// TODO Auto-generated destructor stub
}

void ObjetoGraficable::actualizarPosicion(int x, int y) {
	this->x = x;
	this->y = y;
}

void ObjetoGraficable::render() {
	this->textura->render(this->x, this->y);
	if ( (this->factorParallax != 0) ) {
		this->textura->render(this->x + this->textura->getWidth(), this->y);
		if (this->x <= -this->textura->getWidth()) {
			this->actualizarPosicion(this->x + this->textura->getWidth(), this->y);
		}
	}
}

int ObjetoGraficable::getAncho() {
	return this->textura->getWidth();
}

void ObjetoGraficable::setFactorParallax(int despA, int anchoVentana) {
	int desp = this->textura->getWidth() - anchoVentana;
	this->factorParallax = desp / despA;
}

void ObjetoGraficable::actualizarPosicionFondo(int despA) {
	this->actualizarPosicion(despA*this->factorParallax, this->y);
}

void ObjetoGraficable::grisar(bool grisa){
	if (true || this->grisado != grisa){
		this->grisado = grisa;
		int alpha = (grisa)?128:255;
		this->textura->setAlpha(alpha);
	}
}

void ObjetoGraficable::actualizarEstado(estadoJugador estado) {
	this->textura->actualizarEstado(estado);
}
