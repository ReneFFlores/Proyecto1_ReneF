#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdio.h>
#include <cstdlib>
#include <string.h>
#include <cmath>
#include <ctime>

using std::cin;
using std::endl;
using std::cout;
using std::ifstream;

int main(int argc, char*argv[]){
	char resp_usuario;
	char jugador[20] = {' '};
	cout << "Ingrese su nombre" << endl;
	cin >> jugador;

	for(int i = 0; i < 20; i++){
		if(jugador[i]==' '){
			break;
		}else{
			cout << jugador[i];
		}
	}

	while(true){
		char resp;
		cout << ", desea ver las reglas antes de comenzar? [1=si/2=no]" << endl;
		cin >> resp;
		if(resp=='1'){
			cout << "Ahorcado consiste en adivinar una palabra que la " << endl
				 << "computadora mágicamente adquirío, el método de   " << endl
				 << "adivinanza puede ser la palabra completa en sí, o" << endl
				 << "letra por letra, solo puede cometer 9 errores.  " << endl
				 << "Suerte!" << endl;
				 break;
		}else if(resp=='2'){
				break;
		}else{
			cout << jugador << ", ingrese numero 1 o numero 2" << endl;
			continue;
		}
	}//Reglas del juego

	while(true){
		bool salida_final = false;
		bool ciclo_fuera = false;
		srand(time(0));
		int tamanio;
		const int CANTIDAD_PALABRAS = 50;
		int locacion_palabra;
		char palabra[11];

		srand(time(0));
		locacion_palabra = rand() % CANTIDAD_PALABRAS;
		ifstream fin("diccionario.txt");
		int tam_palabra;

		for(int i = 0; i < CANTIDAD_PALABRAS; i++){
			fin >> palabra;
			if(i == locacion_palabra){
				break;
			}
		}

		tamanio = strlen(palabra);

		char ahorcado [6][12];//muestra gráficamente como está el jugador
		char* avances_juego = new char[tamanio];//Esto muestra que lleva el usuario en cada intento;
		char ecrit[100] = {' '};

		for(int i = 0; i < 6;i++){
			for(int j = 0; j < 12; j++){
				if(i==5){
					ahorcado[i][j] = 'v';
				}else{
					if(j==0){
						ahorcado[i][j] = 'I';
					}else{
						ahorcado[i][j] = ' ';
					}
				}
			}
		}//Valida que el jugador ha empezado/casillas vacías

		for(int i = 0; i < tamanio; i++){
			avances_juego[i] = '_';
		}//Enseña que lleva el jugador del total de la palabra

		cout << "Comenza el juego!" << endl;
		for(int i = 0; i < 6; i++){
			for(int j = 0; j < 12; j++){
				cout << ahorcado[i][j];
			}
			cout << endl;
		}//Imprime el tablero en seco

		int aciertos = 0, errores = 0, cadena_error = 0, turno = 1;
		char intento[11];

		while(true){

			cout << endl << "Palabra: ";
			for(int i = 0; i < tamanio; i++){
				cout << avances_juego[i];
			}

			cout << endl;
			cout << "Vidas: " << (9-errores) << "/9" << endl;
			cout << "Aciertos: " << aciertos << endl;
			cout << "Ingrese turno #" << turno << endl;
			cin >> intento;
			bool existe = false;
			turno++;

			if(strlen(intento) > 1){
				if(strlen(intento) > tamanio || strlen(intento) < tamanio){
					cout << "No puede ser su palabra ya que es mayor o menor" << endl;
					for(int k = 0; k < strlen(intento); k++){
						ecrit[cadena_error] = intento[k];
						cadena_error++;
					}
					ecrit[cadena_error] = '-';
					cadena_error++;
					errores++;
				}else{
					for(int i = 0; i < tamanio; i++){
						if(intento[i] != palabra[i]){
							cout << "Una letra mala, no puede ser la palabra correcta" << endl;
							for(int k = 0; k < tamanio; k++){
								ecrit[cadena_error] = intento[k];
								cadena_error++;
							}
							ecrit[cadena_error] = '-';
							cadena_error++;
							errores++;
							break;
						}else{
							if(i == tamanio-1){
								cout << "Ha ganado!" << endl;
								ciclo_fuera = true;
								break;
							}
						}
					}//Verifica letra por letra
				}
			}else{
				for(int i = 0; i < tamanio; i++){
					if(intento[0]==palabra[i]){
						if(intento[0]==avances_juego[i]){
							cout << "Ya tenia esta letra" << endl;//no pierde puntos si repita palabra
							break;
						}else{
							avances_juego[i] = intento[0];
							cout << "Acerto!" << endl;
							existe = true;
							aciertos++;	
						}
					}else{
						if(intento[0]!=palabra[i-1] && existe==false && i==tamanio-1){
							cout << "Intento fallido!" << endl;
							ecrit[cadena_error] = intento[0];
							cadena_error++;
							ecrit[cadena_error] = '-';
							cadena_error++;
							errores++;
						}
					}
				}//Evalua si la letra que se ingresa estaba ya incluida o no
			}

			if(ciclo_fuera){
				salida_final = true;
				break;
			}else{
				if(errores==1){
					ahorcado[5][5] = 'M';
					ahorcado[5][6] = 'M';
					ahorcado[5][7] = 'M';
				}else if(errores==2){
					for(int i = 0; i <= 4; i++){
						ahorcado[i][6] = 'I';
					}
				}else if(errores==3){
					ahorcado[0][7] = '=';
					ahorcado[0][8] = '=';
					ahorcado[0][9] = '=';
				}else if(errores==4){
					ahorcado[0][9] = 'T';
				}else if(errores==5){
					ahorcado[1][9] = 'O';
				}else if(errores==6){
					ahorcado[2][9] = 'I';
					ahorcado[3][9] = 'I';
				}else if(errores==7){
					ahorcado[2][10] = '_';
					ahorcado[2][8] = '_';
				}else if(errores==8){
					ahorcado[4][10] = 'L';
					ahorcado[4][8] = 'J';
				}else if(errores==9){
					ahorcado[1][9] = 'X';
				}

				for(int i = 0; i < 6; i++){
					for(int j = 0; j < 12; j++){
						cout << ahorcado[i][j];
					}
					cout << endl;
				}//Imprime dibujo del ahorcado

				cout << "Ha hecho estos intentos: ";
				for(int i = 0; i < 23; i++){
					cout << ecrit[i];
				}

				cout << endl;

				if(errores == 9){
					cout << "PERDIO! :P" << endl;
					for(int i = 0; i < tamanio; i++){
						cout << palabra[i];
					}
					cout << " era la palabra" << endl;
					break;
				}//Evualoa FIN del juego si perdio

				for(int i = 0; i < tamanio; i++){
					if(avances_juego[i] == '_'){
						break;
					}else{
						if(i==tamanio-1){
							cout << "FELICIDADES! :D  " << jugador << ", HA GANADO!" << endl;
							salida_final = true;
						}
					}
				}
			}//else del out

			if(salida_final){
				break;
			}
		}//el juego en si

		cout << "Desea otra partida? 1 si, 2 no" << endl;
		cin >> resp_usuario;

		while(resp_usuario != '1' || resp_usuario != '2'){
			if(resp_usuario == '1'){
				break;
			}else if(resp_usuario == '2'){
				cout << "ADIOS" << endl;
				delete[] avances_juego;
				exit(0);
			}else{
				cout << "Ingrese numero del 1 al 2" << endl;
				cin >> resp_usuario;
			}			
		}//while final

	}//fin while usuario

	return 0;
}