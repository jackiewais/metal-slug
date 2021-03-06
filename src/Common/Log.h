#ifndef LOG_H_
#define LOG_H_

#include <iostream>
#include <string.h>
#include <fstream>
#include <iomanip>
#include <sstream>

using namespace std;

#define NIVEL 1
#define TAMANIO 100
#define SERVER "Servidor/log.txt"
#define CLIENT "Cliente/log.txt"


class Log {

public:

	static void write_file(const char* file_name,string message) {

	    time_t now = time(0);
	    tm *ltm =localtime(&now);

	    std::stringstream s;
	    s << 1900 + ltm->tm_year << "-" << setfill('0') << setw(2) << 1 + ltm->tm_mon << "-" << setfill('0') << setw(2) << ltm->tm_mday <<" ";
	    s << setfill('0') << setw(2) << 1 + ltm->tm_hour << ":" << setfill('0') << setw(2) << 1 + ltm->tm_min << ":" << setfill('0') << setw(2) << 1 + ltm->tm_sec <<" ";
	    s << message;

		fstream file(file_name,ios::in | ios::out | ios::app);
		if (!file.is_open()){
	        //  perror("Error apertura de archivo");
		}

		file<< s.str() <<endl;
		file.seekg(0);
		file.close();
	}


	static void log(char tipo_arch,int tipo_msg, string mensaje, string chat) {

		string msg;

			   if (NIVEL != 1){
					switch (tipo_msg){
						case 1:
							msg = "INFO  - ";
							break;
						case 2:
							msg = "WARNING  - ";
							break;
						case 3:
							msg = "ERROR  - ";
					        break;

						default:
							break;
					}
					msg = msg + mensaje;
					if ((NIVEL == 3 || NIVEL == 4) && chat.length()>0){
						msg = msg + ": ";
						if (NIVEL==4){
							chat = chat.substr(0,TAMANIO);
						}
						msg = msg + chat;
					}
					if (tipo_arch == 's'){
						write_file(SERVER,msg);
					}else if ('c'){
						write_file(CLIENT,msg);
					}
			   }
	}
	//tipo char -> 'c':indica archivo del cliente,'s': indica archivo del servidor
	//tipo_msg -> 1:INFO,2:WARNNING,3:ERROR
	//mensaje -> mensaje basico del log
	//chat -> mensaje emitido y recibido por el cliente
};
#endif /* LOG_H_ */
