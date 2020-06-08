#include <iostream>
#include <string>
#include <cstring>
#include "lista.h"
#include "shunting_yard.h"
#include "imagen.h" // esto hay que sacarlo, solo esa de las pruebas cuando esto era un main

//ATENCION, ESTE CODIGO DEBE PERFECCIONARSE INTERNAMENTE (MATI NO CUELGUES, FIRMA MATI)
//FALTA RETOCAR PRECEDENCIA
//RETOCAR LO DE LOS PARENTESIS Y LAS STRING
//VER SI HAY MEJOR MANERA DE CHEQUEAR QUE NO ()
using namespace std;

int main(int argc, char ** argv){
	if(argc < 2)
		return 0;

	lista<string> argumentos = shuntingYard(argv[1]);

	cout << argumentos << endl;
	Imagen prueba = Imagen(10,10,5,1),prueba_transf;
	prueba_transf = prueba.transformar(argumentos);

	return 0;
}


lista<string> shuntingYard(string input){
	lista<string> cola_salida;
	lista<string> pila_operadores;
	string extraido;

	//Por ahora defino los vectores aca hasta que nos entreguen el tp0 para ver si hay que cambiar algo.
	static string operadores[] = {"+", "-","*", "/", "^"};
	static size_t operadores_size = 5;
	static string funciones[] = {"re", "im", "abs", "phase", "exp", "ln", "sin", "cos"};
	static size_t funciones_size = 8;
	static string caracteresEspecial[] = {"z", "j"};
	static size_t caracteresEspecial_size = 2;

	bool flagNumero = false;
	bool flagOperador = false;
	bool flagFuncion = false;
	bool flagParentesis = false;


	while(!(input = quitarEspaciosInicio_matichotoaprendeaprogramar(input)).empty()){
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

		else if(!(extraido = leerToken(input, caracteresEspecial, caracteresEspecial_size)).empty()){
			if(flagNumero){
				cout << MSJ_ERROR_NUMEROS_SEG << endl;
				exit(1);
			}
			flagOperador = false;
			flagFuncion = false;
			flagNumero = true;
			flagParentesis = false;
			pila_operadores.push(extraido);
			input = input.substr(extraido.length());
		}
		else if(!(extraido = leerToken(input, funciones, funciones_size)).empty()){
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

		else if(!(extraido = leerToken(input, operadores, operadores_size)).empty()){
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
				//if(!esOperador(operador_top)) //LO BORRO CREO QUE NO HACE FALTA QUE SEA OPERADOR
				//	break;
				if(precedencia(operador_top) <= precedencia(extraido)){
					if((precedencia(operador_top) < precedencia(extraido)) || !izqAsoc(extraido)) //aclara que aca aunque izqAsoc no anda bien igual funciona
						break;
				}
				if(operador_top == "(")
					break;

				cola_salida.enqueue(pila_operadores.pop());
			}
			pila_operadores.push(extraido);
			input = input.substr(extraido.length());
		}

		else if(input[0] == '('){
			flagParentesis = true;
			string operador_insertar(1, input[0]);
			pila_operadores.push(operador_insertar);
			input = input.substr(1);
		}
		else if(input[0] == ')'){
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
				if(operador_top == "("){
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
		if(operador_top == "("){
			cout << MSJ_ERROR_PARENTESIS << endl;
			exit(1);
		}
		cola_salida.enqueue(operador_top);
	}
	return cola_salida;
}


bool izqAsoc(string input){
	if(input == "^")
		return false;
	return true;
}


string leerToken(string input, string* vector, size_t vector_size){
	for(size_t i = 0; i < vector_size; i++){
		if(!input.compare(0, vector[i].length(), vector[i])){
			return vector[i];
		}
	}
	return EMPTY_STRING;
}

int precedencia(string operador){
	int i;
	string operadores [] = {"+", "-", "*", "/", "^"};
	for(i = 0; i < 5; i++)
		if(operadores[i] == operador)
			break;
	return i / 2;
}


string leerNumero(string input){
	string numero = "";
	int i = 0;
	while(isdigit(input[i]) || input[i] == DECIMAL_CHAR){
		numero += input[i];
		i++;
	}
	return numero;
}

string quitarEspaciosInicio_matichotoaprendeaprogramar(string input){
  int i;
  for(i = 0; i < int(input.length()); i++){
    if(!isspace(input[i]))
      break;
  }
  return input.substr(i);
}
