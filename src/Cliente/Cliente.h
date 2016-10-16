#ifndef CLIENTE_H_
#define CLIENTE_H_

#include "ConexionCli.h"
#include "../Common/Mensajeria.h"
#include "../Common/Log.h"
#include <iostream>
#include <string.h>
#include <map>
#include <list>
#include "Escenario.h"
#include "../Common/Util.h"

class Cliente:ConexionCli {
private:
	bool esperarJugadores = false;
    int vecesX = 0;
    string convertirAString(int i);
	 datosConexionStruct datosConexion;
	 ConexionCli conexionCli;
	 bool semaforoReceive = false;
	 map<int, string> mapIdNombreUsuario;
	 bool mainCin = false;
	 int seleccConectar();
	int getIpAndPort();
	int selectFromMenu();
	int seleccDesconectar();
	int salir();
	int enviar();
	int recibir();
	int loremIpsum();
	int getUsuarioYContrasenia(std::string &usuario, std::string &contrasenia);
	static void *recvMessage(void * arg);
	bool handleKeyEvents();
	//void crearEscenario(Escenario escenario);
	static void *crearEscenario(void *arg);
	int printMenu();
	void objetoNuevo(mensajeStruct msg);
	void imprimirConsigna();
	int ingresarUsuarioYMensaje(int* idUsuario, string* mensaje);
	pthread_t threadRecv;
	pthread_t threadEscenario;
	void terminarThreadRecv();
	void setDimensionesVentana(mensajeStruct msg);
	void addSprite(mensajeStruct msg);
	void updateJugador(mensajeStruct msg);
	Escenario escenario;
	void esperarJugador();
	void addEstadoSprite(mensajeStruct msg);
	bool jugando = true;

public:
	bool escenarioOK =false;
	Cliente();
	virtual ~Cliente();
	int runCliente();
	string getNombreUsuarioById(int idUsuario);
	list<int> getIdUsuarios();
};

#endif /* CLIENTE_H_ */
