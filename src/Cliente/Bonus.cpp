#include "Bonus.h"
#include <iostream>

using namespace std;

void Bonus::init(GraficableBasic* graficable,bonusTypes bonus, int posX, int posY){
	this->graficable = graficable;
	this->posX = posX;
	this->posY=posY;
	this->bonus=bonus;
}

void Bonus::setPosicion(int posX,int posY){
	this->posX = posX;
	this->posY=posY;

}


void Bonus::render()
{
	graficable->render(posX,posY,bonus);
}


Bonus::~Bonus()
{
}
