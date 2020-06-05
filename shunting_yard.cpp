#include <iostream>
#include <string>
#include "lista.h"
#include "shunting_yard.h"


//ATENCION, ESTE CODIGO DEBE PERFECCIONARSE INTERNAMENTE (MATI NO CUELGUES, FIRMA MATI)
using namespace std;

lista<string> shuntingYard(string input){
	lista<string> cola_salida;
	lista<string> pila_operadores;
	string operador;
	while(!(input = quitarEspaciosInicio(input)).empty()){
		if(isdigit(input[0]))
			cola_salida.enqueue(leerNumero(input));
		else if(input[0] == 'z'){
			cola_salida.enqueue("z"); //muy harcodeado
			input = input.substr(1); //sacar estos substr creo O HACER TODO DESDE ACA (VER) //RETOCAR ESTO Y QUE QUEDE TODO EN UN MISMO IF
		}
		else if(input[0] == 'j'){
			cola_salida.enqueue("j"); //muy harcodeado
			input = input.substr(1); //sacar estos substr creo O HACER TODO DESDE ACA (VER)
		}
		else if(!(operador = leerFuncion(input)).empty())
			pila_operadores.push(operador);
		else if(!(operador = leerOperador(input)).empty()){
			while(pila_operadores.llena()){
				const string operador_top = pila_operadores.mirarTop();
				//if(!esOperador(operador_top)) //LO BORRO CREO QUE NO HACE FALTA QUE SEA OPERADOR
				//	break;
				if(precedencia(operador_top) <= precedencia(operador)){
					if((precedencia(operador_top) < precedencia(operador)) || !izqAsoc(operador)) //aclara que aca aunque izqAsoc no anda bien igual funciona
						break;
				}
				if(operador_top == "(")
					break;
				
				cola_salida.enqueue(pila_operadores.pop());
			}
			pila_operadores.push(operador);
		}
		else if(input[0]=='('){
			string operador_insertar(1, input[0]);
			pila_operadores.push(operador_insertar);
			input = input.substr(1);
		}
		else if(input[0]==')'){
			while(1){
				if(pila_operadores.vacia()){
					cout << "Error" << endl;
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
			cout << "Error que termina" << endl;
			exit(1);
		}
	} //fin del while
	while(pila_operadores.llena()){
		operador = pila_operadores.pop();
		if(operador == "("){
			cout << "Error" << endl;
			exit(1);
		}
		cola_salida.enqueue(operador);
	}
	return cola_salida;
}


bool izqAsoc(string input){
	if(input == "^")
		return false;
	return true;
}

string leerOperador(string& input){
	char operadores [] = {'+', '-','*', '/', '^'};
	for(int i = 0; i < 5; i++){
		if(input[0] == operadores[i]){
			input = input.substr(1);
			string operador(1, operadores[i]);
			return operador;
		}
	}
	return "";
}

string leerFuncion(string& input){
	string funcion [] = {"re", "im", "abs", "phase", "exp", "ln"};
	for(int i = 0; i < 6; i++){
		if(input.substr(0, funcion[i].length()) == funcion[i]){
			input = input.substr(funcion[i].length());
			return funcion[i];
		}
	}
	return "";
}

int precedencia(string operador){
	int i;
	string operadores [] = {"+", "-", "*", "/", "^"};
	for(i = 0; i < 5; i++)
		if(operadores[i] == operador)
			break;
	return i / 2;
}


string leerNumero(string& input){
	string numero = "";
	int i = 0;
	while(isdigit(input[i]) || input[i] == '.'){
		numero += input[i];
		i++;
	}
	input = input.substr(i);
	return numero;
}

string quitarEspaciosInicio(string input){
  int i;
  for(i = 0; i < int(input.length()); i++){
    if(!isspace(input[i]))
      break;
  }
  return input.substr(i);
}








