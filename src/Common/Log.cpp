#include <iostream>
#include <string.h>
#include <fstream>
#include <iomanip>
#include <sstream>

using namespace std;

void write_file(char* file_name,char* message){

    time_t now = time(0);
    tm *ltm =localtime(&now);

    std::stringstream s;
    s << 1900 + ltm->tm_year << "-" << setfill('0') << setw(2) << 1 + ltm->tm_mon << "-" << setfill('0') << setw(2) << ltm->tm_mday <<" ";
    s << setfill('0') << setw(2) << 1 + ltm->tm_hour << ":" << setfill('0') << setw(2) << 1 + ltm->tm_min << ":" << setfill('0') << setw(2) << 1 + ltm->tm_sec <<" ";
    s << message;

	fstream file(file_name,ios::in | ios::out | ios::app);
	if (!file.is_open()){
          perror("Error apertura de archivo");
	}

	file<< s.str() <<endl;
	file.seekg(0);
	file.close();
}

void log_servidor(int nivel, int tipo, char msg[],char* usuario){
char message[128];

   if (nivel != 1){
		switch (tipo){
			case 1:case 2:case 3:
				strcpy(message,"INFO  - El usuario ");
				strcat(message, usuario);
				if (tipo == 1){
					strcat(message, " envia un mensaje");
				}else if (tipo == 2){
					strcat(message, " recibe un mensaje");
				}else if (tipo == 3){
					strcat(message, " envia un Lorem Ipsum");
				}
                if (nivel == 3){
                	strcat(message, ": ");
                	strcat(message, msg);
                }
				break;
			case 4:
                strcpy(message,"INFO  - Se conecto el usuario ");
                strcat(message, usuario);
				break;
			case 5:
				strcpy(message,"INFO  - Se desconecto el usuario ");
				strcat(message, usuario);
				break;
			case 6:
				strcpy(message,"ERROR - Password del usuario " );
				strcat(message, usuario);
				strcat(message, " incorrecta");
				break;
			case 7:
				strcpy(message,"ERROR - Password del usuario");
				strcat(message, usuario);
				strcat(message, "no cumple con las condiciones");
				break;
			case 8:
				strcpy(message,"ERROR - Salida forzada del usuario");
				strcat(message, usuario);
				break;
			default:
				break;
		}
		write_file("src/Servidor/log.txt",message);
   }
}

void log_cliente(int nivel, int tipo){
char message[128];

   if (nivel != 1){
		switch (tipo){
			case 1:
				break;
			case 2:
                strcpy(message,"INFO  - Se conecto el usuario ");
				break;
			case 3:
				strcpy(message,"INFO  - Se desconecto el usuario ");
				break;
			case 4:
				strcpy(message,"ERROR - Password del usuario " );
				break;
			case 5:
				strcpy(message,"ERROR - Password del usuario");
				break;
			case 6:
				strcpy(message,"ERROR - Salida forzada del usuario");
				break;
			default:
				break;
		}
		write_file("src/Cliente/log.txt",message);
   }
}

