#include "Cliente.h"
#include <limits>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <iostream>
#include <string.h>

#include <fstream>
#include <iomanip>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <exception>
#include <sstream>
#include <sys/socket.h>
#include <pthread.h>

using namespace std;

#define MAXDATASIZE 100 // máximo número de bytes que se pueden leer de una vez
#define LOREMIPSUM "src/Cliente/loremIpsum.txt"

Cliente::Cliente() {

}

Cliente::~Cliente() {
	// TODO Auto-generated destructor stub
}


int Cliente::seleccConectar(){
	int respuesta = 1;
	string usuario, contrasenia;

	if (this->datosConexion.conectado){
		cout << "El usuario ya está conectado" << endl;
		respuesta = 0;
	}else{

		getUsuarioYContrasenia(usuario, contrasenia);
		respuesta = 0;

		this->mapIdNombreUsuario = conectar(&this->datosConexion, usuario, contrasenia);

		if (!this->mapIdNombreUsuario.empty()){
		//	this->datosConexion.idUsuario = idUsuario;
			printf("Logueado correctamente");
			this->datosConexion.conectado = true;
			//EVENTUALMENTE EL HILO SE CREA CON EL METODO RECV&DECODE
			pthread_t threadRecv;
			int rc = pthread_create(&threadRecv, NULL,&recvMessage,(void*)this);
			if (rc){
				printf("ERROR creando el thread  %i \n",rc);
			}

			respuesta = 0;
			//Crear hilo rcv
		}else{
			cerrarSocket(this->datosConexion.sockfd);
			respuesta = 1;
		}

	}

	return respuesta;
}

void *Cliente::recvMessage(void * arg){

	bool finish = false;
	Cliente* context = (Cliente*)arg;
	mensajeStruct mensajeRta;
	string nombre;

	while(!finish){
		finish = context->conexionCli.recibirMensaje(&context->datosConexion, &mensajeRta);
		switch (mensajeRta.tipo){
			case RECIBIR_CHATS:
				//nombre = mapa_usuarios[mensajeRta.otherCli];
				nombre = "PEPE";
				printf((nombre + " escribió: " + mensajeRta.message + "\n").c_str());
				break;
			case FIN_RECIBIR_CHATS:
				context->semaforoReceive = false;
				break;
			case DISCONNECTED:
				context->datosConexion.conectado = false;
				context->conexionCli.cerrarSocket(context->datosConexion.sockfd);
				context->imprimirConsigna();
				break;
		}
    }
	return 0;
};

int Cliente::getUsuarioYContrasenia(string &usuario, string &contrasenia){
	string inputUsuario, inputContrasenia;
	bool ok = false;

	while (!ok){
		cout << "Ingrese el nombre de usuario:" << endl;
		cin >> usuario;
		if (usuario.find(";") == string::npos)
			ok = true;
	}

	ok = false;
	while (!ok){
		cout << "Ingrese la contraseña:" << endl;
		cin >> contrasenia;
		if (contrasenia.find(";") == string::npos)
			ok = true;
	}

	return 0;
}

int Cliente::seleccDesconectar(){
	int respuesta = 0;

	if (!this->datosConexion.conectado){
		cout << "El usuario no está conectado" << endl;
	}else{
		respuesta = desconectar(&this->datosConexion);
		if (respuesta == 0)
			this->datosConexion.conectado = false;
	}

	return respuesta;
}

int Cliente::salir(){
	seleccDesconectar();
	return -1;
}

int Cliente::enviar(){

	if (!this->datosConexion.conectado){
		cout << "El usuario no está conectado" << endl;
	}else{
		enviarMensajes(&this->datosConexion);
	}
	return 0;
}

int Cliente::recibir(){
	conexionCli.pedirMensajes(&datosConexion);
	semaforoReceive = true;
	while (semaforoReceive){}
	return 0;
}

int Cliente::loremIpsum(){

	int tamanio;
	srand(unsigned(time(0)));
	tamanio = rand()%200+1;

	int frecuencia;
	int cantMax;
	int milisegundos;
    string linea;
    string linea_aux;
    string linea_aux2;
    string linea_final;
    int tamanio_aux=0;
    int pos;
    cout << "Frecuencia de envio:";
    cin >> frecuencia;
    cout << "Cantidad maxima de mensajes:";
    cin >> cantMax;
    milisegundos= 1000/frecuencia;
    int cont = 1;
    clock_t t = clock();
    int actual = (t*1000)/double(CLOCKS_PER_SEC);
    int cada = actual + milisegundos;

   while(cont <= cantMax){
	fstream file2(LOREMIPSUM,ios::in | ios::out | ios::app);
	if (!file2.is_open()){
          perror("Error apertura de archivo");
	}
	while (!file2.eof() && (cont <= cantMax) ){
	    getline(file2, linea);
	    pos=0;

	    while(((pos+tamanio)<= linea.length()) && (cont <= cantMax)){
           linea_aux2 = linea.substr(pos,tamanio - tamanio_aux);
           linea_final = linea_aux + linea_aux2;

           linea_aux = "";
           linea_aux2 = "";

           do{

           	if (actual == cada){
                cout << linea_final << endl;
           		cada = actual + milisegundos;
           	    cont++;
           	    break;
           	}

           	t = clock();
           	actual = (t*1000)/double(CLOCKS_PER_SEC);

           }while(cont <= cantMax);

           pos = (pos + tamanio)-tamanio_aux;
           tamanio_aux = 0;
	   }

       if ((pos == 0) && ((tamanio_aux+linea.length()) < tamanio)){
    		   linea_aux = linea_aux + linea;
    		   tamanio_aux = tamanio_aux + linea.length();
       }else{
	         tamanio_aux = linea.length()- pos;
             linea_aux = linea.substr(pos,tamanio_aux);
       }
	}
	file2.seekg(0);
	file2.close();

}
	return 0;
}


int Cliente::getIpAndPort(){
	string inputIp;
	int inputPuerto;
	bool ok = false;

	cout << "Ingrese la ip del servidor ('l' para localhost):" << endl;
	cin >> inputIp;

	if (inputIp == "l"){
		strcpy(this->datosConexion.ip,"127.0.0.1");
	}else{
		strcpy(this->datosConexion.ip,inputIp.c_str());
	}

	cout << "Ingrese el puerto del servidor:" << endl;
	while (!ok){
		cin >> inputPuerto;
		if (!cin){ //Validates if its a number
			cout << "Error: Debe ingresar un número" << endl;
		}else{
			this->datosConexion.puerto = inputPuerto;
			ok = true;
		}
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	return 0;
}


int printMenu(){

	cout << "-----   MENÚ   -----------------------" << endl;
	cout << "1 - Conectar" << endl;
	cout << "2 - Desconectar" << endl;
	cout << "3 - Salir" << endl;
	cout << "4 - Enviar" << endl;
	cout << "5 - Recibir" << endl;
	cout << "6 - Lorem Ipsum" << endl;
	cout << "7 - Reingresar ip y puerto" << endl;
	cout << "---------------------------------------" << endl;

	return 0;
}
void Cliente::imprimirConsigna(){
	cout << endl;
	cout << "---------------" << endl;
	cout << "Seleccione una opción del menú:" << endl;
}

int Cliente::selectFromMenu(){
	int input;
	bool ok = false;
	int status;

	imprimirConsigna();

	while (!ok){
		cin >> input;
		if (!cin){ //Validates if its a number
			cout << "Error: Debe ingresar un número" << endl;
		}else if(input<1 || input > 6){
			cout << "Error: Ingrese una de las opciones dadas" << endl;
		}else
			ok = true;

		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	//--------------------------------------------

	switch (input){
		case 1:
			status = seleccConectar();
			break;
		case 2:
			status = seleccDesconectar();
			break;
		case 3:
			status = salir();
			break;
		case 4:
			status = enviar();
			break;
		case 5:
			status = recibir();
			break;
		case 6:
			status = loremIpsum();
			break;
		case 7:
			status = getIpAndPort();
			break;
	}

	return status;


}


int Cliente::runCliente(){
	cout << "Starting client app" << endl;

	int status = 0;

	getIpAndPort();
	printMenu();

	while (status >= 0){
		status = selectFromMenu();
	}

	return 0;

};


string Cliente::getNombreUsuarioById(int idUsuario) {

	string nombre = "";

	map<int, string>::iterator it;

	if((it = this->mapIdNombreUsuario.find(idUsuario)) != this->mapIdNombreUsuario.end())
		nombre = this->mapIdNombreUsuario[idUsuario];

	return nombre;
}


list<int> Cliente::getIdUsuarios() {

	list<int> idUsuarios;
	map<int, string>::iterator it;

	for(it = this->mapIdNombreUsuario.begin(); it != this->mapIdNombreUsuario.end(); it++) {

		    idUsuarios.push_back(it->first);
	}

	return idUsuarios;
}
