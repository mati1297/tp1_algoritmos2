#ifndef SHUNTING_YARD__H
#define SHUNTING_YARD__H

#include "lista.h"
#include <iostream>
#include <string>
#include <cstring>

#define SPACE " \t\v\f\r"
#define CHARS_NUMBERS "0123456789."
#define MSJ_ERROR_PARENTESIS "Error: parentesis no balanceados"
#define MSJ_ERROR_OPERADOR_DESC "Error: funcion o operador desconocido"
#define LEFT_SEPARATOR_OP "("
#define RIGHT_SEPARATOR_OP ")"
#define MSJ_ERROR_NUMEROS_SEG "Error: dos numeros seguidos"
#define MSJ_ERROR_OPERADORES_SEG "Error: dos operadores/funciones seguidos"
#define MSJ_ERROR_OPERADOR_FINAL "Error: la entrada termina con un operador"
#define MSJ_ERROR_FUNC_OPERADOR_SEG "Error: una funcion no puede ir seguida de un operador"
#define MSJ_ERROR_FUNCION_FINAL "Error: la entrada termina con una funcion"
#define MSJ_ERROR_NUMERO_FUNC_SEG "Error: un numero no puede estar seguido de una funcion"
#define MSJ_ERROR_PARENTESIS_VACIOS "Error: parentesis vacios"



#define OPERADORES_CANT 5
#define FUNCIONES_CANT 10
#define CARACTERES_ESPECIAL_CANT 3

lista<string> shuntingYard(string);
bool izqAsoc(const string&);
int precedencia(const string&, const string*);
string leerToken(const string&, const string*, const size_t);
string leerNumero(const string&);
void cargarVectorOperadores(string *operadores);
void cargarVectorFunciones(string *funciones);
void cargarVectorCaracteresEspecial(string *caracteresEspecial);


#endif
