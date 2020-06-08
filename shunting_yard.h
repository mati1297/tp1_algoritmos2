#ifndef SHUNTING_YARD__H
#define SHUNTING_YARD__H

#define EMPTY_STRING ""
#define DECIMAL_CHAR '.'
#define MSJ_ERROR_PARENTESIS "Error: parentesis no balanceados"
#define MSJ_ERROR_OPERADOR_DESC "Error: funcion o operador desconocido"
#define LEFT_PARENTESIS_OP "("
#define RIGHT_PARENTESIS_OP ")"
#define MSJ_ERROR_NUMEROS_SEG "Error: dos numeros seguidos"
#define MSJ_ERROR_OPERADORES_SEG "Error: dos operadores/funciones seguidos"
#define MSJ_ERROR_OPERADOR_FINAL "Error: la entrada termina con un operador"
#define MSJ_ERROR_FUNC_OPERADOR_SEG "Error: una funcion no puede ir seguida de un operador"
#define MSJ_ERROR_FUNCION_FINAL "Error: la entrada termina con una funcion"
#define MSJ_ERROR_NUMERO_FUNC_SEG "Error: un numero no puede estar seguido de una funcion"
#define MSJ_ERROR_PARENTESIS_VACIOS "Error: parentesis vacios"


lista<string> shuntingYard(string input);
bool izqAsoc(string);
string leerToken(string, string*, size_t);
int precedencia(string);
string leerNumero(string);
string quitarEspaciosInicio_matichotoaprendeaprogramar(string); //ver que hacer con esta


#endif
