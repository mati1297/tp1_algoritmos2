#ifndef SHUNTING_YARD__H
#define SHUNTING_YARD__H


lista<string> shuntingYard(string input);
bool izqAsoc(string);
string leerOperador(string&);
string leerFuncion(string&);
int precedencia(string);
string leerNumero(string&);
string quitarEspaciosInicio(string); //ver que hacer con esta


#endif
