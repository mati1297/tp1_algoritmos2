#include "shunting_yard.h"
#include "lista.h"
#include <iostream>
#include <string>
#include <cstring>


using namespace std;

lista<string> shuntingYard(string input){
  //Se crean la pila de operadores y la cola de salida. Dos listas
  //del mismo tipo pero utilizadas de maneras diferentes.
  lista<string> cola_salida;
  lista<string> pila_operadores;
  string extraido;

  //Se crean y cargan los vectores con operadores, funciones, etc.
  static string operadores[OPERADORES_CANT];
  cargarVectorOperadores(operadores);
  static string funciones[FUNCIONES_CANT];
  cargarVectorFunciones(funciones);
  static string caracteresEspecial[CARACTERES_ESPECIAL_CANT];
  cargarVectorCaracteresEspecial(caracteresEspecial);

  //Se crea el vector de flags y se setea en true el flag de inicio.
  bool flags[CANT_FLAGS];
  subirFlag(flags, FLAG_INICIO);

  //Mientras haya caracteres para leer.
  while(input.find_first_not_of(SPACE) != std::string::npos){
    input = input.substr(input.find_first_not_of(SPACE));
   
     
    //Si es un numero se guarda en la cola de salida
    if(input.find_first_of(CHARS_NUMBERS) == 0){
      if(flags[FLAG_NUMERO]){
        cerr << MSJ_ERROR_NUMEROS_SEG << endl;
        exit(EXIT_FAILURE);
      }
      subirFlag(flags, FLAG_NUMERO);
      extraido = leerNumero(input);
      cola_salida.enqueue(extraido);
      input = input.substr(extraido.length());
    }
    

    //Si es una funcion se guarda en la pila de operadores
    else if(!(extraido = leerToken(input, funciones, FUNCIONES_CANT)).empty()){
      if(flags[FLAG_NUMERO]){
        cerr << MSJ_ERROR_NUMERO_FUNC_SEG << endl;
        exit(EXIT_FAILURE);
      }
      subirFlag(flags, FLAG_FUNCION);
      pila_operadores.push(extraido);
      input = input.substr(extraido.length());
    }

	//Si es un caracter especial tambien se reconoce como numero y se
    //guarda en la cola de salida.
    else if(!(extraido = leerToken(input, caracteresEspecial, CARACTERES_ESPECIAL_CANT)).empty()){
      if(flags[FLAG_NUMERO]){
        cerr << MSJ_ERROR_NUMEROS_SEG << endl;
        exit(EXIT_FAILURE);
      }
      subirFlag(flags, FLAG_NUMERO);
      cola_salida.enqueue(extraido);
      input = input.substr(extraido.length());
    }


    //Si es un operador se guarda en la pila de operadores una vez que se haya chequeado
    //que no hay otros operadores esperando en la lista que deben ir antes del extraido.
    else if(!(extraido = leerToken(input, operadores, OPERADORES_CANT)).empty()){
      if(flags[FLAG_OPERADOR]){
        cerr << MSJ_ERROR_OPERADORES_SEG << endl;
        exit(EXIT_FAILURE);
      }
      if(flags[FLAG_FUNCION]){
        cerr << MSJ_ERROR_FUNC_OPERADOR_SEG << endl;
        exit(EXIT_FAILURE);
      }
      if(flags[FLAG_INICIO]){
        cerr << MSJ_ERROR_OPERADOR_INICIO << endl;
        exit(EXIT_FAILURE);
      }
      subirFlag(flags, FLAG_OPERADOR);

      while(pila_operadores.llena()){
        const string operador_top = pila_operadores.mirarTop();
        if(precedencia(operador_top, operadores) <= precedencia(extraido, operadores)){
          if((precedencia(operador_top, operadores) < precedencia(extraido, operadores)) || !izqAsoc(extraido))
            break;
        }
        if(operador_top == LEFT_SEPARATOR_OP)
          break;

        cola_salida.enqueue(pila_operadores.pop());
      }
      pila_operadores.push(extraido);
      input = input.substr(extraido.length());
    }
    
    


    //Si es un parentesis izquierdo se guarda en la pila.
    else if(!input.compare(0, 1, LEFT_SEPARATOR_OP)){
      subirFlag(flags, FLAG_PARENTESIS);
      string operador_insertar(1, input[0]);
      pila_operadores.push(operador_insertar);
      input = input.substr(1);
    }
    
    //Si es un operador derecho, se saca todo de la pila hasta
    //encontrar el parentesis izquierdo.
    else if(!input.compare(0, 1, RIGHT_SEPARATOR_OP)){
      if(flags[FLAG_PARENTESIS]){
        cerr << MSJ_ERROR_PARENTESIS_VACIOS << endl;
        exit(EXIT_FAILURE);
      }
      flags[FLAG_PARENTESIS] = false;
      while(1){
        if(pila_operadores.vacia()){
          cerr << MSJ_ERROR_PARENTESIS << endl;
          exit(EXIT_FAILURE);
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
      cerr << MSJ_ERROR_OPERADOR_DESC << endl;
      exit(EXIT_FAILURE);
    }
    
  }

  if(flags[FLAG_OPERADOR]){
    cerr << MSJ_ERROR_OPERADOR_FINAL << endl;
    exit(EXIT_FAILURE);
  }
  if(flags[FLAG_FUNCION]){
    cerr << MSJ_ERROR_FUNCION_FINAL << endl;
    exit(EXIT_FAILURE);
  }

  //Se sacan todos los operadores que hayan quedado en la pila.
  while(pila_operadores.llena()){
    const string operador_top = pila_operadores.pop();
    if(operador_top == LEFT_SEPARATOR_OP){
      cerr << MSJ_ERROR_PARENTESIS << endl;
      exit(EXIT_FAILURE);
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

/*Los operadores deben ir colocados en orden de precedencia, en orden creciente
 * (los de menor precedencia al principio */
void cargarVectorOperadores(string *operadores){
  operadores[0] = "+";
  operadores[1] = "-";
  operadores[2] = "*";
  operadores[3] = "/";
  operadores[4] = "^";
}

/* Si hay funciones cuyo nombre contenga totalmente al de otra, esta debe ir
 * primero en el vector (por ejemplo: sinh contiene a sin. Por lo tanto sinh
 * debe ir antes en el vector que sin).*/
void cargarVectorFunciones(string *funciones){
  funciones[0] = "abs";
  funciones[1] = "phase";
  funciones[2] = "exp";
  funciones[3] = "ln";
  funciones[4] = "re";
  funciones[5] = "im";
  funciones[6] = "sinh";
  funciones[7] = "cosh";
  funciones[8] = "sin";
  funciones[9] = "cos";
  funciones[10] = "conj";
  funciones[11] = "arctan";
  funciones[12] = "~";
}

void cargarVectorCaracteresEspecial(string *caracteresEspecial){
  caracteresEspecial[0] = "j";
  caracteresEspecial[1] = "i";
  caracteresEspecial[2] = "z";
  caracteresEspecial[3] = "-j";
  caracteresEspecial[4] = "-i";
  caracteresEspecial[5] = "-z";
}


void subirFlag(bool* flags, int posicion){
  for(int i = 0; i < CANT_FLAGS; i++){
    flags[i] = false;
    if(i == posicion)
      flags[i] = true;
  }
}
