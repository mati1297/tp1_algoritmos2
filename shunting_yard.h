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
#define MSJ_ERROR_OPERADOR_INICIO "Error: la función empieza con un operador"

#define FLAG_INICIO 0
#define FLAG_OPERADOR 1
#define FLAG_FUNCION 2
#define FLAG_NUMERO 3
#define FLAG_PARENTESIS 4
#define CANT_FLAGS 5 

#define OPERADORES_CANT 5
#define FUNCIONES_CANT 13
#define CARACTERES_ESPECIAL_CANT 3

/*Metodo principal, se le pasa una cadena con la funcion infix, y devuelve
 * una lista con las funciones, operadores y operandos validados y en 
 * notacion polaca invertida */
lista<string> shuntingYard(string);

bool izqAsoc(const string&); //Devuelve true si el operador es asociado a izquierda

/* Devuelve la precedencia de un operador/funcion, las funciones tienen mayor precedencia
 * que los operadores siempre. Se le debe pasar ademas el vector de operadores.*/
int precedencia(const string&, const string*);

/* Lee el primer token presente en el string que tambien se encuentre en el vector que se le
 * pasa. Ademas se le debe pasar el tamaño del vector de strings con que se va a comparar. 
 * En caso de no encontrar coincidencias se devuelve un string vacio.*/
string leerToken(const string&, const string*, const size_t);

/* Lee el numero que se encuentra en la cadena hasta que encuentre un caracter no
 * numerico (el '.' es conciderado un numero). En caso de no encontrar ninguno devuelve
 * una cadena vacia. */
string leerNumero(const string&);

/*Funciones que se encargan de cargar los vectores de operadores, etc.*/
void cargarVectorOperadores(string *operadores);
void cargarVectorFunciones(string *funciones);
void cargarVectorCaracteresEspecial(string *caracteresEspecial);

/*Pone en "true" el booleano correspondiente a la posicion que se le pase y 
 * todos los demas en false. En caso de pasarse un numero fuera de rango deja
 * todo seteado en false. */
void subirFlag(bool*, int);

#endif
