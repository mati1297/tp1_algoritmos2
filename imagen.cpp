#include "imagen.h"
#include "lista.h"
#include "complejo.h"

#include <cmath>
#include <fstream>
#include <string>

#include "vector.h"

Imagen::Imagen(){
  columnas = COLUMNAS_DEF;
  filas = FILAS_DEF;
  intensidad = INTENSIDAD_DEF;
  matriz.resize(FILAS_DEF);
  for(int i = 0; i < filas; i++)
    matriz[i].resize(COLUMNAS_DEF, VALOR_DEF);
}

Imagen::Imagen(int filas_, int columnas_, int intensidad_, int valor_){
  filas = filas_;
  columnas = columnas_;
  intensidad = intensidad_;
  if(valor_ > intensidad)
    valor_ = VALOR_DEF;
  try{
    matriz.resize(filas_);
  }
  catch(std::bad_alloc &err){
    matriz.resize(FILAS_DEF);
  }
  for(int i = 0; i < filas_; i++){
    try{
      matriz[i].resize(columnas_, valor_);
    }
    catch(std::bad_alloc &err){
      matriz[i].resize(COLUMNAS_DEF, valor_);
    }
  }
}

Imagen::Imagen(const Imagen& original){
  filas = original.filas;
  columnas = original.columnas;
  intensidad = original.intensidad;
  matriz = original.matriz;
}

Imagen::~Imagen(){
}

Imagen& Imagen::operator=(const Imagen& right){
  if(*this == right)
    return *this;
  filas = right.filas;
  columnas = right.columnas;
  intensidad = right.intensidad;
  matriz = right.matriz;
  return *this;
}

bool Imagen::operator==(const Imagen& right) const{
  if(right.matriz == matriz && right.intensidad == intensidad)
    return true;
  return false;
}

bool Imagen::operator!=(const Imagen & right) const{
  if(right.matriz != matriz || right.intensidad != intensidad)
    return true;
  return false;
}

int Imagen::getFilas() const{
  return filas;
}

int Imagen::getColumnas() const{
  return columnas;
}

int Imagen::getIntensidad() const{
  return intensidad;
}

Imagen Imagen::transformar(const lista<string> funcion) const{
  Imagen im_aux = Imagen(filas, columnas, intensidad, VALOR_DEF);
  double x, y, x_0 = columnas/2, y_0 = filas/2;
  // Inicializo el iterador al principio de la lista (sabiendo que ya es correcta y fue validada antes)
  lista<string>::iterador it = lista<string>::iterador(funcion);
  lista<complejo> l_aux;
  string s_aux;
  complejo c_aux;

  for(int i = 0; i < filas;i++) {
    for(int j=0;j<columnas;j++){
      // aplico la transformacion lineal para mapear al rectangulo de lado 2
      x = j/x_0-1;
      y = 1-i/y_0;

      // inicializo el iterador
      it = funcion.primero();

      // realizo el algoritmo de evaluacion con la funcion dada por la lista
      // El dato puede ser 'z' 'j' 'numero' 'operador' 'funcion'
      while (it.extremo() != true) {
        s_aux = it.dato();

        if (isdigit(s_aux[0]) || (s_aux[0] == '.')) {
          l_aux.push(complejo(stod(s_aux),0));
        }
        else if (s_aux == "z") {
          l_aux.push(complejo(x,y));
        }
        else if ((s_aux == "j")||(s_aux == "i")) {
          l_aux.push(complejo(0,1));
        } // Veo si es un operador (largo 1)
        else if (s_aux.length() == 1){
          evaluar_operador(s_aux, l_aux);
        } // Realizo las funciones
        else {
          evaluar_funcion(s_aux, l_aux);
        }
        // Avanzo al iterador
        it = it.avanzar();
      } // fin del while

      if (l_aux.getTamano() != 1){
        std::cout<<"(✿╹◡╹) <(Error de la re concha de tu madre)"<<endl;
      }
      // El ultimo elemento que quedo en la lista aux. es el complejo resultado
      c_aux = l_aux.pop();
      //std::cout<<c_aux<<std::endl;

      // realizo la transformacion lineal inversa"ln"){
      x = (int) (x_0 * (1 + c_aux.re()));
      y = (int) (y_0 * (1 - c_aux.im()));

      if ((x < 0) || (x >= columnas) || (y < 0) || (y >= filas)){
				im_aux.matriz[i][j] = 0;  // Si cae fuera del rango la pongo en 0 (negro.)
			} else {
				im_aux.matriz[i][j] = this->matriz[y][x];
      }
    }
  }
  return im_aux;
}

void Imagen::evaluar_operador(const string & string_aux, lista<complejo> & pila_complejos) const {
  if (string_aux == "+") {
    pila_complejos.push(pila_complejos.pop()+pila_complejos.pop());
  } else if (string_aux == "-") {
    pila_complejos.push(pila_complejos.pop()-pila_complejos.pop());
  } else if (string_aux == "*") {
    pila_complejos.push(pila_complejos.pop()*pila_complejos.pop());
  } else if (string_aux == "/") {
    pila_complejos.push(pila_complejos.pop()/pila_complejos.pop());
  } else if (string_aux == "^") {
    pila_complejos.push(pila_complejos.pop()^pila_complejos.pop());
  }
}

void Imagen::evaluar_funcion(const string & string_aux, lista<complejo> & pila_complejos) const {
  if (string_aux == "abs") {
    pila_complejos.push(pila_complejos.pop().modulo());
  }
  else if (string_aux == "re"){
    pila_complejos.push(pila_complejos.pop().re());
  }
  else if (string_aux == "im"){
    pila_complejos.push(pila_complejos.pop().im());
  }
  else if (string_aux == "phase"){
    pila_complejos.push(pila_complejos.pop().fase());
  }
  else if (string_aux == "exp"){
    pila_complejos.push(pila_complejos.pop().expc());
  }
  else if (string_aux == "ln"){
    pila_complejos.push(pila_complejos.pop().logc());
  }
  else if (string_aux == "sin"){
    pila_complejos.push(pila_complejos.pop().seno());
  }
  else if (string_aux == "cos"){
    pila_complejos.push(pila_complejos.pop().coseno());
  }
  else if (string_aux == "sinh"){
    pila_complejos.push(pila_complejos.pop().senoh());
  }
  else if (string_aux == "cosh"){
    pila_complejos.push(pila_complejos.pop().cosenoh());
  }
}

int Imagen::setIntensidad(std::string& input) {
  size_t lectura;
  try{
    intensidad = stoi(input, &lectura);
  }
  catch(std::invalid_argument& err){
	std::cerr << MSJ_ERROR_INTENSIDAD<< std::endl;
	return 1;
  }
  if(intensidad <= 0){
	std::cerr << MSJ_ERROR_INTENSIDAD_INVALIDA << std::endl;
	return 1;
  }
  input = input.substr(lectura);
  return 0;
}

int Imagen::setColumnas(std::string& input){
  size_t lectura;
  try{
    columnas = stoi(input, &lectura);
  }
  catch(std::invalid_argument& err){
	std::cerr << MSJ_ERROR_COLUMNAS << std::endl;
	return 1;
  }
  if(columnas <= 0){
	std::cerr << MSJ_ERROR_TAMANO_INVALIDO << std::endl;
	return 1;
  }
  input = input.substr(lectura);
  return 0;
}

int Imagen::setFilas(std::string& input){
  size_t lectura;
  try{
    filas = stoi(input, &lectura);
  }
  catch(std::invalid_argument& err){
	std::cerr << MSJ_ERROR_FILAS << std::endl;
	return 1;
  }
  if(filas<=0){
	std::cerr << MSJ_ERROR_TAMANO_INVALIDO << std::endl;
	return 1;
  }
  input = input.substr(lectura);
  return 0;
}

int Imagen::setMatriz(std::istream& input){
	/*Se leen los datos de cada pixel de la imagen del archivo .pgm. No permite
   * comentarios entre lineas. No importa la cantidad de pixeles que
   * haya por linea, se leen de corrido hasta que se complete la fila.
   * Si hay menos pixeles de los indicados, el programa termina con
   * un error, si hay mas, los ignora. */

   size_t lectura;
   std::string line;

  while(getline(input, line)){
    if(line.find_first_not_of(SPACE) == std::string::npos){
      std::cerr << MSJ_ERROR_LINEA_VACIA << std::endl;
	  return 1;
	}
    line = line.substr(line.find_first_not_of(SPACE));
    if(line[0] != PGM_COMENTARIO)
      break;
  }

  for(int i = 0; i < filas; i++){
	for(int j = 0; j < columnas; j++){
	  if(line.find_first_not_of(SPACE) == std::string::npos){
	    if(!getline(input, line)){
		  std::cerr << MSJ_ERROR_TAMANO << std::endl;
          return 1;
	    }
        if(line.find_first_not_of(SPACE) == std::string::npos){ //Hay una linea vacia
		  std::cerr << MSJ_ERROR_LINEA_VACIA << std::endl;
		  return 1;
		}
	  }
	  try{
        matriz[i][j] = std::stoi(line, &lectura);
      }
      catch(std::invalid_argument &err){
        std::cerr << MSJ_ERROR_PIXELES << std::endl;
        return 1;
      }
      if(matriz[i][j] > intensidad){
        std::cerr << MSJ_ERROR_INTENSIDAD_MAX << std::endl;
        return 1;
      }
      if(matriz[i][j] < 0){
        std::cerr << MSJ_ERROR_INTENSIDAD_MIN << std::endl;
        return 1;
      }
      line = line.substr(lectura);
    }
  }

  return 0;

}

int Imagen::resizeMatriz(){
  try{
    matriz.resize(filas);
  }
  catch(std::bad_alloc &err){
    std::cerr << MSJ_ERROR_MEMORIA << std::endl;
    return 1;
  }

  for(int i = 0; i < filas; i++){
    try{
      matriz[i].resize(columnas);
    }
    catch(std::bad_alloc &err){
      std::cerr << MSJ_ERROR_MEMORIA << std::endl;
      return 1;
    }
  }
  return 0;
}





int Imagen::readPGM(std::istream& input){
  std::string line;

  /*Verificación de que el archivo tiene el header
   * "P2", que es el formato que se desea leer.*/
  while(getline(input, line)){
    if(line.find_first_not_of(SPACE) == std::string::npos){
      std::cerr << MSJ_ERROR_LINEA_VACIA << std::endl;
	  return EXIT_FAILURE;
	}
    line = line.substr(line.find_first_not_of(SPACE));
    if(line[0] != PGM_COMENTARIO)
      break;
  }

  if((line != PGM_INDICADOR) && (line != PGM_INDICADOR_WIN)){
      std::cerr<<MSJ_ERROR_PGM_INDICADOR<<std::endl;
      return(EXIT_FAILURE);
  }

  /* Se leen datos de cantidad de filas y columnas (ambos en
   * una misma linea en el archivo .pgm), luego se cambia el
   * tamaño de la matriz del objeto Imagen para poder alojar
   * la imagen correctamente.*/
  while(getline(input, line)){
    if(line.find_first_not_of(SPACE) == std::string::npos){
      std::cerr << MSJ_ERROR_LINEA_VACIA << std::endl;
	  return EXIT_FAILURE;
	}
    line = line.substr(line.find_first_not_of(SPACE));
    if(line[0] != PGM_COMENTARIO)
      break;
  }

  if(setColumnas(line))
	return EXIT_FAILURE;

  if(setFilas(line))
	return EXIT_FAILURE;

  if(resizeMatriz())
	return EXIT_FAILURE;


  /*Lee el valor de intensidad dado en el archivo .pgm*/
  while(getline(input, line)){
    if(line.find_first_not_of(SPACE) == std::string::npos){
      std::cerr << MSJ_ERROR_LINEA_VACIA << std::endl;
	  return EXIT_FAILURE;
	}
    line = line.substr(line.find_first_not_of(SPACE));
    if(line[0] != PGM_COMENTARIO)
      break;
  }

  if(setIntensidad(line))
    return EXIT_FAILURE;


  /* Se lee la matriz, se le pasa directamente el puntero istream ya que debe leer
   * varias lineas */
  if(setMatriz(input)){
	  return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

void Imagen::savePGM(std::ostream& output){
  output << PGM_INDICADOR << std::endl
       << PGM_COMENTARIO << COMENTARIO << std::endl
       << columnas << ' ' << filas << std::endl
       << intensidad << std::endl;
  int contador_linea = 0;
  for(int i = 0; i < filas; i++){
    for(int j = 0; j < columnas; j++){
      output << matriz[i][j] << " ";
      contador_linea++;
      if (contador_linea == NUMEROS_LINEA_SALIDA){
        output << std::endl;
        contador_linea = 0;
      }
    }
  }
}
