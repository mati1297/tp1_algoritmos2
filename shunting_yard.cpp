#include "shunting_yard.h"
#include "lista.h"
#include <iostream>
#include <string>
#include <cstring>


//ATENCION, ESTE CODIGO DEBE PERFECCIONARSE INTERNAMENTE (MATI NO CUELGUES, FIRMA MATI)
//RETOCAR LO DE LOS PARENTESIS Y LAS STRING
using namespace std;

lista<string> shuntingYard(string input){
	lista<string> cola_salida;
	lista<string> pila_operadores;
	string extraido;

	//Por ahora defino los vectores aca hasta que nos entreguen el tp0 para ver si hay que cambiar algo.
	static string operadores[OPERADORES_CANT];
	cargarVectorOperadores(operadores);
	static string funciones[FUNCIONES_CANT];
	cargarVectorFunciones(funciones);
	static string caracteresEspecial[CARACTERES_ESPECIAL_CANT];
	cargarVectorCaracteresEspecial(caracteresEspecial);

	bool flagNumero = false;
	bool flagOperador = false;
	bool flagFuncion = false;
	bool flagParentesis = false;


	while(input.find_first_not_of(SPACE) != std::string::npos){
		input = input.substr(input.find_first_not_of(SPACE));
		if(isdigit(input[0])){
			if(flagNumero){
				cout << MSJ_ERROR_NUMEROS_SEG << endl;
				exit(1);
			}
			flagOperador = false;
			flagFuncion = false;
			flagParentesis = false;
			flagNumero = true;
			extraido = leerNumero(input);
			cola_salida.enqueue(extraido);
			input = input.substr(extraido.length());
		}

		else if(!(extraido = leerToken(input, caracteresEspecial, CARACTERES_ESPECIAL_CANT)).empty()){
			if(flagNumero){
				cout << MSJ_ERROR_NUMEROS_SEG << endl;
				exit(1);
			}
			flagOperador = false;
			flagFuncion = false;
			flagNumero = true;
			flagParentesis = false;
			cola_salida.enqueue(extraido);
			input = input.substr(extraido.length());
		}


		else if(!(extraido = leerToken(input, funciones, FUNCIONES_CANT)).empty()){
			if(flagNumero){
				cout << MSJ_ERROR_NUMERO_FUNC_SEG << endl;
				exit(1);
			}
			flagFuncion = true;
			flagOperador = false;
			flagNumero = false;
			flagParentesis = false;
			pila_operadores.push(extraido);
			input = input.substr(extraido.length());
		}


		else if(!(extraido = leerToken(input, operadores, OPERADORES_CANT)).empty()){
			if(flagOperador){
				cout << MSJ_ERROR_OPERADORES_SEG << endl;
				exit(1);
			}
			if(flagFuncion){
				cout << MSJ_ERROR_FUNC_OPERADOR_SEG << endl;
				exit(1);
			}
			flagOperador = true;
			flagNumero = false;
			flagParentesis = false;

			while(pila_operadores.llena()){
				const string operador_top = pila_operadores.mirarTop();
				if(precedencia(operador_top, operadores) <= precedencia(extraido, operadores)){
					if((precedencia(operador_top, operadores) < precedencia(extraido, operadores)) || !izqAsoc(extraido))
						break;
				}
				if(operador_top == "(")
					break;

				cola_salida.enqueue(pila_operadores.pop());
			}
			pila_operadores.push(extraido);
			input = input.substr(extraido.length());
		}

		else if(!input.compare(0, 1, LEFT_SEPARATOR_OP)){
			flagParentesis = true;
			string operador_insertar(1, input[0]);
			pila_operadores.push(operador_insertar);
			input = input.substr(1);
		}
		else if(!input.compare(0, 1, RIGHT_SEPARATOR_OP)){
			if(flagParentesis){
				cout << MSJ_ERROR_PARENTESIS_VACIOS << endl;
				exit(1);
			}
			flagParentesis = false;
			while(1){
				if(pila_operadores.vacia()){
					cout << MSJ_ERROR_PARENTESIS << endl;
					exit(1);
				}
				const string operador_top = pila_operadores.mirarTop();
				if(operador_top == LEFT_SEPARATOR_OP){
					pila_operadores.pop();
					break;
				}
				cola_salida.enqueue(pila_operadores.pop());
			}
			input = input.substr(1);
		}
		else{
			cout << MSJ_ERROR_OPERADOR_DESC << endl;
			exit(1);
		}
	} //fin del while

	if(flagOperador){
		cout << MSJ_ERROR_OPERADOR_FINAL << endl;
		exit(1);
	}
	if(flagFuncion){
		cout << MSJ_ERROR_FUNCION_FINAL << endl;
		exit(1);
	}

	while(pila_operadores.llena()){
		const string operador_top = pila_operadores.pop();
		if(operador_top == LEFT_SEPARATOR_OP){
			cout << MSJ_ERROR_PARENTESIS << endl;
			exit(1);
		}
		cola_salida.enqueue(operador_top);
	}

	return cola_salida;
}


bool izqAsoc(const string& input){
	if(input == "^")
		return false;
	return true;
}

int precedencia(const string& operador, const string* operadores){
	int i;
	for(i = 0; i < 5; i++)
		if(operadores[i] == operador)
			break;
	return i / 2;
}

string leerToken(const string& input, const string* vector, const size_t vector_size){
	for(size_t i = 0; i < vector_size; i++){
		if(!input.compare(0, vector[i].length(), vector[i])){
			return vector[i];
		}
	}
	return string();
}


string leerNumero(const string& input){
	string numero = input.substr(0, input.find_first_not_of(CHARS_NUMBERS));
	return numero;
}

//Aclarar operadores en orden de precedencia creciente
void cargarVectorOperadores(string *operadores){
	operadores[0] = "+";
	operadores[1] = "-";
	operadores[2] = "*";
	operadores[3] = "/";
	operadores[4] = "^";
}

void cargarVectorFunciones(string *funciones){
	funciones[0] = "abs";
	funciones[1] = "phase";
	funciones[2] = "exp";
	funciones[3] = "ln";
	funciones[4] = "re";
	funciones[5] = "im";
	funciones[6] = "sin";
	funciones[7] = "cos";
}

void cargarVectorCaracteresEspecial(string *caracteresEspecial){
	caracteresEspecial[0] = "j";
	caracteresEspecial[1] = "z";
}
