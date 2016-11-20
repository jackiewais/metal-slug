#ifndef BONUS_H_
#define BONUS_H_


#include "LTextureBasic.h"
#include "GraficableBasic.h"
#include "../Common/Modelo.h"


class Bonus
{
	public:
	void init(GraficableBasic* graficable,bonusTypes bonus, int posX, int posY);
	void render();
	void setPosicion(int posX,int posY);

	~Bonus();

	GraficableBasic* graficable;

	bonusTypes bonus;
	int posX;
	int posY;

};

#endif
