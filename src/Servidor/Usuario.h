#ifndef USUARIO_H_
#define USUARIO_H_

#include <string>

using namespace std;

class Usuario {

private:
	int idUsuario;
	int idSocket;
	string nombre;
	string pass;
	bool conectado;
	int idJugador;

public:
	Usuario(int idUsuario, string nombre, string pass);
	virtual ~Usuario();
	int getIdUsuario();
	void setIdUsuario(int idUsuario);
	int getIdSocket();
	void setIdSocket(int idSocket);
	string getNombre();
	void setNombre(string nombre);
	string getPass();
	void setPass(string pass);
	bool isConectado();
	void iniciarSesion(int idSocket);
	void cerrarSesion();

	int getIdJugador();
	void setIdJugador(int idJugador);
};

#endif /* USUARIO_H_ */
