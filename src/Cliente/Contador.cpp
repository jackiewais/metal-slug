#include "Contador.h"

using namespace std;

Contador::Contador(std::string id, int posX, int posY, Numero* numero, Progreso* progreso, Label* lbalas, int puntaje,int vida,int municion) {
	this->id = id;
	this->posX = posX;
	this->posY = posY;
	this->numero = numero;
	this->progreso=progreso;
	this->lbalas = lbalas;
	this->puntaje = puntaje;
	this->vida = vida;
	this->balas = municion;
}

Contador::~Contador() {
}

void Contador::actualizarDatos(int puntaje, int vida, int municiones){
	this->puntaje = puntaje;
	this->vida = vida;
	this->balas = municiones;
}

void Contador::actualizarPuntaje(int nuevopunt){
	puntaje = nuevopunt;
}
void Contador::actualizarVida(int nuevo_valor){
	vida = nuevo_valor;
}

void Contador::actualizarMunicion(int nuevo_valor){
	balas = nuevo_valor;
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

	int x = posX+105;
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
