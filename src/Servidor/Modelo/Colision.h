#ifndef SRC_COLISION_H_
#define SRC_COLISION_H_

#include <iostream>
#include <string.h>

using namespace std;

class Colision {

public:

	static bool colisionSoldadoConBala(int puntoXs, int puntoYs, int ancho, int alto, int puntoXb, int puntoYb, int radio) {
		//logica para transformar la cabeza del soldado en un circulo y colisionar circulo con circulo
		return colisionRectanguloConCirculo(puntoXs, puntoYs, ancho, alto, puntoXb, puntoYb, radio);
	}

	static bool colisionSoldadoConSoldado(int puntoXs1, int puntoYs1, int ancho1, int alto1, int puntoXs2, int puntoYs2, int ancho2, int alto2) {
		//hay que ver si hace falta una colision de circulos o solo son rectangulos
		return colisionRectanguloConRectangulo(puntoXs1, puntoYs1, ancho1, alto1, puntoXs2, puntoYs2, ancho2, alto2);
	}


private:

	static bool colisionRectanguloConCirculo(int puntoXs, int puntoYs, int ancho, int alto, int puntoXb, int puntoYb, int radio) {

		bool hayColision = false;
		// si la bala esta completamente adentro del soldado
		if ((puntoXb + radio  >= puntoXs) && (puntoXb - radio <= puntoXs + ancho) && (puntoYb + radio >= puntoYs) && (puntoYb - radio <= puntoYs + alto)) {
			hayColision = true;
		}
		//Si no, el punto del rectangulo mas cercano al centro del circulo
		else {
			// Esquina arriba-izquierda
			int distX = puntoXs - puntoXb;
			int distY = puntoYs - puntoYb;
			int distMin = sqrt((distX * distX) + (distY * distY));

			// Esquina arriba-derecha
			distX = (puntoXs + ancho) - puntoXb;
			distY = puntoYs - puntoYb;
			int dist = sqrt((distX * distX) + (distY * distY));

			if (dist < distMin) {
				distMin = dist;
			}

			// Esquina abajo-derecha
			distX = (puntoXs + ancho) - puntoXb;
			distY = (puntoYs + alto) - puntoYb;
			dist = sqrt((distX * distX) + (distY * distY));

			if (dist < distMin) {
				distMin = dist;
			}

			// Esquina abajo-izquierda
			distX = puntoXs - puntoXb;
			distY = (puntoYs + alto) - puntoYb;
			dist = sqrt((distX * distX) + (distY * distY));

			if (dist < distMin) {
				distMin = dist;
			}

			//si distMin es menor al radio hay colision
			if (distMin < radio) {
				hayColision = true;
			}
		}
		return hayColision;
	}


	static bool colisionRectanguloConRectangulo(int puntoXs1, int puntoYs1, int ancho1, int alto1, int puntoXs2, int puntoYs2, int ancho2, int alto2) {

		bool hayColision = false;
		//Lado derecho de r1 es mayor que lado izquierdo de r2 && Lado izquierdo de r1 es menor que lado derecho de r2 && Lado superior de r1 es mayor que lado inferior de r2 && Lado inferior de r1 es menor que lado superior de r2
	    if (((puntoXs1 + ancho1) >= puntoXs2) && (puntoXs1 <= (puntoXs2 + ancho2)) && ((puntoYs1 + alto1) >= puntoYs2) && (puntoYs1  <= (puntoYs2 + alto2))) {
	        hayColision = true;
	    }

	    return hayColision;
	}


	static bool colisionCirculoConCirculo(int puntoXb1, int puntoYb1, int radio1,int puntoXb2, int puntoYb2, int radio2) {

		bool hayColision = false;

		int distX = puntoXb1 - puntoXb2;
		int distY = puntoYb1 - puntoYb2;
		int dist = sqrt((distX * distX) + (distY * distY));

		// si la suma de los radios es mayor a la distancia, hay colision
		if ((radio1 + radio2) > dist) {
			hayColision = true;
		}

		return hayColision;
	}
};

#endif /* SRC_COLISION_H_ */
