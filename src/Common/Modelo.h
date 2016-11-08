#ifndef MODELO_H_
#define MODELO_H_


enum estadoJugador{
	PARADO = 01,
	CAMINA_DER = 02,
	CAMINA_IZQ = 03,
	//SALTA = 04,
	SALTA_DER = 04,
	SALTA_IZQ = 05,

	SIN_ESTADO = 50
};

enum aimDirection {
	RIGHT = 01,
	LEFT = 02,
	UP = 03,
	DOWN = 04,
	DIAGRIGHT = 05,
	DIAGLEFT = 06
};
#endif
