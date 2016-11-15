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
		// si la bala esta completamente adentro al ancho del soldado
		if ((puntoXb + radio  >= puntoXs - ancho / 2) && (puntoXb - radio <= puntoXs + ancho / 2) && (abs(puntoYs - puntoYb) <= radio))
		{
			hayColision = true;
		}
		//Si no, si la bala esta completamente adentro al alto del soldado
		else if ((puntoXb + radio >= puntoYs - alto / 2) && (puntoYb - radio <= puntoYs + alto / 2) && (abs(puntoXs - puntoXb) <= radio))
			 {
				hayColision = true;
			 }
			 else {
				// Esquina arriba-izquierda
				int distX = (puntoXs - ancho / 2) - puntoXb;
				int distY = (puntoYs - alto / 2) - puntoYb;
				int distMin = sqrt((distX*distX) + (distY * distY));

				// Esquina ariba-derecha
				distX = (puntoXs + ancho / 2) - puntoXb;
				distY = (puntoYs - alto / 2) - puntoYb;
				int dist = sqrt((distX*distX) + (distY * distY));

				if (dist < distMin)
				{
					distMin = dist;
				}

				// Esquina abajo-derecha
				distX = (puntoXs + ancho / 2) - puntoXb;
				distY = (puntoYs + alto / 2) - puntoYb;
				dist = sqrt((distX*distX) + (distY * distY));

				if (dist < distMin)
				{
					distMin = dist;
				}

				// Esquina abajo-izquierda
				distX = (puntoXs - ancho / 2) - puntoXb;
				distY = (puntoYs + alto / 2) - puntoYb;
				dist = sqrt((distX*distX) + (distY * distY));

				if (dist < distMin)
				{
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
	    if (((puntoXs1 + ancho1 / 2) >= (puntoXs2 -ancho2 / 2)) && ((puntoXs1 - ancho1 / 2) <= (puntoXs2 + ancho2 / 2)) && ((puntoYs1 + alto1 / 2) >= (puntoYs2 - alto2 / 2)) && ((puntoYs1 - alto1 / 2) <= (puntoYs2 + alto2 / 2)))
	        hayColision = true;

	    return hayColision;
	}


	static bool colisionCirculoConCirculo(int puntoXb1, int puntoYb1, int radio1,int puntoXb2, int puntoYb2, int radio2) {

		bool hayColision = false;

		int distX = puntoXb1 - puntoXb2;
		int distY = puntoYb1 - puntoYb2;
		int dist = sqrt((distX*distX) + (distY * distY));

		// si la suma de los radios es mayor a la distancia, hay colision
		if (radio1 + radio2 > dist)
			hayColision = true;

		return hayColision;
	}
};

#endif /* SRC_COLISION_H_ */
