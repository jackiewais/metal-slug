#include "ObjetoGraficable.h"

ObjetoGraficable::ObjetoGraficable(std::string id, LTexture *textura, int x, int y) {
	this->id = id;
	this->textura = textura;
	this->x = x;
	this->y = y;
	this->factorParallax = 0;
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
