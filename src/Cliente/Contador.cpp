#include "Contador.h"

using namespace std;

Contador::Contador(std::string id, int posX, int posY, Numero* numero, Progreso* progreso, Label* lbalas) {
	this->id = id;
	this->posX = posX;
	this->posY = posY;
	this->numero = numero;
	this->progreso=progreso;
	this->lbalas = lbalas;
}

Contador::~Contador() {
	lbalas->close();
	delete(lbalas);
}

void Contador::actualizarPuntaje(int dif){
	puntaje += dif;
}
void Contador::actualizarVida(int dif){
	vida += dif;
	if (vida==0) vida=100;
	//borrar, es para probar como queda
	if (vida == 50) balas = 200;
	if (vida < 50) balas -= 2;
	if (vida > 50) balas = -1;
}
void Contador::renderizar(){
	int x=posX+75;//pos inicial ultimo digito
	for (int i=1;i<=1000;i=i*10){
		int digit = puntaje/i%10;

		this->numero->render(digit,x,posY);
		x-=25;
	}

	progreso->render(vida,posX,posY+40);
	renderizarCantBalas();
}

void Contador::renderizarCantBalas(){

	int x = posX+120;
	int y = posY+40;

	lbalas->render(x,posY);

	if (balas == -1){
		//Render infinito
		this->numero->render(-1,x,y);
	}else{
		x+=50;//pos inicial ultimo digito
		for (int i=1;i<=100;i=i*10){
			int digit = balas/i%10;
			this->numero->render(digit,x,y);
			x-=25;
		}
	}
}
