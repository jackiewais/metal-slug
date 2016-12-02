#ifndef MODELO_H_
#define MODELO_H_

#include <string>

enum estadoJugador{
	PARADO_GUN = 01,
	CAMINA_DER_GUN = 02,
	CAMINA_IZQ_GUN = 03,
	//SALTA = 04,
	SALTA_DER_GUN = 04,
	SALTA_IZQ_GUN = 05,

	// CON MACHINE GUN
	PARADO_MACHINE = 01,
	CAMINA_DER_MACHINE = 02,
	CAMINA_IZQ_MACHINE = 03,
	//SALTA = 04,
	SALTA_DER_MACHINE = 04,
	SALTA_IZQ_MACHINE = 05,

	DISPARANDO_DER=06,
	DISPARANDO_IZQ=07,
	SIN_ESTADO = 50
};

enum aimDirection {
	RIGHT = 01,
	LEFT = 02,
	UP = 03,
	DOWN = 04,
	DIAGRIGHT = 05,
	DIAGLEFT = 06,
	DIAGLEFTDOWN = 07,
	DIAGRIGHTDOWN = 8
};

enum weapon {
	GUN = 01,
	MACHINEGUN = 02,
	SHOOTGUN = 03,
	TANIOHGUN = 04,
	BOMB = 05
	};
enum balaMachineGun{
	up = 01,
	middle = 02,
	down = 03
};

struct enemigoStruct {
	int ancho;
	int alto;
	std::string tipo;
	int velocidad;
	int posXAbsolutaDeJugadorParaAparicion;
	int bloquearAvanceEscenario;
	int aparecePorIzq;
	std::string sprite;
};

enum modoDeJuego {
	INDIVIDUAL = 01,
	COLABORATIVO = 02,
	GRUPAL = 03
};

enum bonusTypes{
	MACHINEG=01,
	SHOTG=02,
	POWER=03,
	KILL_ALL=04
};


struct bonus {
	bonusTypes type;
	int posXAbs;
	int posX;
	int posY;
};
#endif
