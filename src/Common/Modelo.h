#ifndef MODELO_H_
#define MODELO_H_


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

	SIN_ESTADO = 50,
};

enum aimDirection {
	RIGHT = 01,
	LEFT = 02,
	UP = 03,
	DOWN = 04,
	DIAGRIGHT = 05,
	DIAGLEFT = 06
};

enum weapon {
	GUN = 01,
	MACHINEGUN = 02,
	SHOOTGUN = 03,
	};
enum balaMachineGun{
	up = 01,
	middle = 02,
	down = 03
};
#endif
