#include "ImportarCSV.h"
#include "../Common/Log.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>

using namespace std;

ImportarCSV::ImportarCSV() {
	this->cantidadUsuarios = 15;
	this->datos = 2;

	this->tablaUsuarios = new string*[this->cantidadUsuarios];

	for(int i=0; i < this->cantidadUsuarios ;i++)
		this->tablaUsuarios[i] = new string[this->datos];
}

ImportarCSV::~ImportarCSV() {
	for(int i=0; i < this->cantidadUsuarios ;i++)
	   delete[] this->tablaUsuarios[i];

    delete[] this->tablaUsuarios;
}


string** ImportarCSV::importar(string csv) {

	ifstream archivo(csv.c_str());
	string  nombre, pass;
	stringstream lineaError, cantUsuarios;

	if(archivo.fail()) {
		cerr << "Error al abrir el archivo " + string(csv) << endl;
        Log::log('s',3,"Al abrir el archivo " + string(csv),"");
        return NULL;
	}else{
		int i = 0;

	    while(!archivo.eof()) {

	    	getline(archivo, nombre, ';');
	    	getline(archivo, pass, '\n');

	    	if ( (pass.find(';') != string::npos) ||
	    			(nombre.find('|') != string::npos) || (pass.find('|') != string::npos) ||
					(nombre.find('%') != string::npos) || (pass.find('%') != string::npos) ||
					(nombre.find('#') != string::npos) || (pass.find('#') != string::npos) ) {

	    		printf("ERROR al leer archivo CSV, se cargaron %d usuarios\n", i);
	    		lineaError << (i + 1);
	    		Log::log('s', 3, "Caracter invalido al leer archivo CSV. Linea: " + lineaError.str(), "");
	    		break;
	    	}

	    	if (nombre != "" && pass != "") {
	        	this->tablaUsuarios[i][this->datos-2] = nombre;
	        	this->tablaUsuarios[i][this->datos-1] = pass;
	        	i++;
	        }
	    	nombre = "";
	    	pass = "";
	    }
	    this->cantidadUsuarios = i;

	    if(i == 0) printf("No se cargo ningun usuario\n");
	    cantUsuarios << (i);
	    Log::log('s', 1, "Se cargaron " + cantUsuarios.str() + " usuarios", "");
	 }
	 archivo.close();

	 return this->tablaUsuarios;
}


int ImportarCSV::getCantidadUsuarios() {

	return this->cantidadUsuarios;
}







