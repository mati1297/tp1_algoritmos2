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

/* funcion ordenada es una pila ordenada por shunting yard de f(z)*/
Imagen Imagen::transformar(const lista<string> funcion_ordenada) const{
  Imagen imagen_aux = Imagen(filas, columnas, intensidad, VALOR_DEF);
  double x, y, x_0 = columnas/2, y_0 = filas/2;
  // Inicializo el iterador al principio de la lista (sabiendo que ya es correcta y fue validada antes)
  lista<string>::iterador iter = lista<string>::iterador(funcion_ordenada);
  lista<complejo> pila_aux;
  string str_aux;
  complejo complejo_aux;

  for(int i = 0; i < filas;i++) {
    for(int j=0;j<columnas;j++){
      // Aplico la transformacion lineal para mapear al rectangulo de lado 2
      x = j/x_0-1;
      y = 1-i/y_0;

      // Inicializo el iterador
      iter = funcion_ordenada.primero();

      // realizo el algoritmo de evaluacion con la funcion dada por la lista
      // El dato puede ser 'z' 'j' (o 'i'), '-z', '-j' '-i'
      // 'numero' 'operador' o 'funcion',
      while (iter.extremo() != true) {
        str_aux = iter.dato();

        if (isdigit(str_aux[0]) || (str_aux[0] == '.')) {
          pila_aux.push(complejo(stod(str_aux),0));
        }
        else if (str_aux == "z") {
          pila_aux.push(complejo(x,y));
        } // Se aceptan tanto j como i como variable compleja
        else if ((str_aux == "j")||(str_aux == "i")) {
          pila_aux.push(complejo(0,1));
        } // Veo si es un operador (largo 1) o '~'
        else if (str_aux.length() == 1){
          evaluar_operador(str_aux, pila_aux);
        } // Si no es nada de lo anterior, al ya estar validado, es una funcion
        else {
          evaluar_funcion(str_aux, pila_aux);
        }

        // Avanzo al iterador
        iter = iter.avanzar();
      } // fin del while

      // El ultimo elemento que quedo en la lista aux. es el complejo resultado
      complejo_aux = pila_aux.pop();

      // realizo la transformacion lineal inversa"ln"){
      x = (int) (x_0 * (1 + complejo_aux.re()));
      y = (int) (y_0 * (1 - complejo_aux.im()));

      if ((x < 0) || (x >= columnas) || (y < 0) || (y >= filas)){
        imagen_aux.matriz[i][j] = 0;  // Si cae fuera del rango la pongo en 0 (negro.)
      } else {
        imagen_aux.matriz[i][j] = this->matriz[y][x];
      }
    }
  }
  return imagen_aux;
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
  } else if (string_aux == "~") // Si es '~' se multiplica por menos uno el valor
    pila_complejos.push(pila_complejos.pop() * (-1));
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
  else if (string_aux == "cosh"){
    pila_complejos.push(pila_complejos.pop().cosenoh());
  }
  else if (string_aux == "conj"){
    pila_complejos.push(pila_complejos.pop().conjugado());
  }
  else if (string_aux == "arctan"){
    pila_complejos.push(pila_complejos.pop().arctan());
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
