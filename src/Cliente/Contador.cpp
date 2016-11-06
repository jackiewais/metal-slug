#include "Contador.h"

using namespace std;

Contador::Contador(std::string id, int posX, int posY, Numero* numero, Progreso* progreso) {
	this->id = id;
	this->posX = posX;
	this->posY = posY;
	this->numero = numero;
	this->progreso=progreso;
}

Contador::~Contador() {
	// TODO Auto-generated destructor stub
}

void Contador::actualizarPuntaje(int dif){
	puntaje += dif;
}
void Contador::actualizarVida(int dif){
	vida += dif;
	if (vida==0) vida=100;
}
void Contador::renderizar(){
	int x=posX+75;//pos inicial ultimo digito
	for (int i=1;i<=1000;i=i*10){
		int digit = puntaje/i%10;

		this->numero->render(digit,x,posY);
		x-=25;
	}

	progreso->render(vida,posX,posY+40);
}

