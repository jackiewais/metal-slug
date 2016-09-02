
#include <iostream>

class Mensajeria {

public:
	enum tipoMensajeEnum {LOG_OK = 001, LOG_NOTOK = 002};

	struct mensajeStruct {
		int longit;
		tipoMensajeEnum tipo;
		std::string message;

	};
};


