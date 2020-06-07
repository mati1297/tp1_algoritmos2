#include "imagen.h"

#include <cmath>
#include <vector>
#include <fstream>
#include <string>


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

Imagen Imagen::transformar(funcion_t f) const{
  switch(f) {
    case Z:
      return this->transf_z();
      break;
    case EXPONENCIAL:
      return this->transf_exp();
      break;
    case CUADRADO:
      return this->transf_cuadrado();
      break;
    default:
      return this->transf_z(); //si pasan una funcion que no existe, devuelve la misma imagen
      break;
    break;
      return *this;
  }
}

int Imagen::readPGM(std::istream& input){
  std::string line;
  int pos_space;

  /*Variable que verifica no entrar en un bucle infinito (ver parte
   * de lectura de pixeles de la imagen)*/
  int j_inf = -1;

  /*Verificación de que el archivo tiene el header
   * "P2", que es el formato que se desea leer.
   * Antes de cada lectura, se quitan todos los espacios del inicio
   * de la linea y se verifican que la linea sea un comentario.
   * Todas las lineas que se detectan comentarios son descartadas.*/
  while(getline(input, line))
    if((line = quitarEspaciosInicio(line))[0] != PGM_COMENTARIO)
      break;

  if((line != PGM_INDICADOR) && (line != PGM_INDICADOR_WIN)){
    std::cerr<<MSJ_ERROR_PGM_INDICADOR<<std::endl;
    return(EXIT_FAILURE);
  }




  /* Se leen datos de cantidad de filas y columnas (ambos en
   * una misma linea en el archivo .pgm), luego se cambia el
   * tamaño de la matriz del objeto Imagen para poder alojar
   * la imagen correctamente.*/
  while(getline(input, line))
    if((line = quitarEspaciosInicio(line))[0] != PGM_COMENTARIO)
      break;


  pos_space = encontrarEspacio(line);
  try{
    columnas = std::stoi(line.substr(0, pos_space));
  }
  catch(std::invalid_argument &err){
    std::cerr << MSJ_ERROR_COLUMNAS << std::endl;
    return(EXIT_FAILURE);
  }
  try{
    filas = std::stoi(line.substr(pos_space + 1));
  }
  catch(std::invalid_argument &err){
    std::cerr << MSJ_ERROR_FILAS << std::endl;
    return(EXIT_FAILURE);
  }

  if(filas <= 0 || columnas <= 0){
    std::cerr << MSJ_ERROR_TAMANO_INVALIDO << std::endl;
    return(EXIT_FAILURE);
  }

  //Se hace el resize de las filas y columnas.

  try{
    matriz.resize(filas);
  }
  catch(std::bad_alloc &err){
    std::cerr << MSJ_ERROR_MEMORIA << std::endl;
    return(EXIT_FAILURE);
  }

  for(int i = 0; i < filas; i++){
    try{
      matriz[i].resize(columnas);
    }
    catch(std::bad_alloc &err){
      std::cerr << MSJ_ERROR_MEMORIA << std::endl;
      return(EXIT_FAILURE);
    }
  }




  /*Lee el valor de intensidad dado en el archivo .pgm*/
  while(getline(input, line))
    if((line = quitarEspaciosInicio(line))[0] != PGM_COMENTARIO)
      break;

  try{
    intensidad = stoi(line);
  }
  catch(std::invalid_argument &err){
    std::cerr << MSJ_ERROR_INTENSIDAD << std::endl;
    return(EXIT_FAILURE);
  }

  if(intensidad <= 0){
    std::cerr << MSJ_ERROR_INTENSIDAD_INVALIDA << std::endl;
    return(EXIT_FAILURE);
  }


  while(getline(input, line))
    if((line = quitarEspaciosInicio(line))[0] != PGM_COMENTARIO)
      break;

  /*Se leen los datos de cada pixel de la imagen del archivo .pgm. No permite
   * comentarios entre lineas. No importa la cantidad de pixeles que
   * haya por linea, se leen de corrido hasta que se complete la fila.
   * Si hay menos pixeles de los indicados, el programa termina con
   * un error, si hay mas, los ignora. */
  for(int i = 0; i < filas; i++){
    /*Se setea j_inf = -1 al principio de cada fila*/
    j_inf = -1;
    for(int j = 0; j < columnas; j++){
      line = quitarEspaciosInicio(line); //Se quitan los espacios del principio de la linea.
      pos_space = encontrarEspacio(line); //Se busca el primer espacio, esto indica el fin del numero que se quiera leer.

      /*Si existe un espacio mas adelante del numero se lee y luego se quita el numero leido*/
      if(pos_space!=-1){
        try{
          matriz[i][j] = std::stoi(line.substr(0, pos_space));
        }
        catch(std::invalid_argument &err)
        {
          std::cerr << MSJ_ERROR_PIXELES << std::endl;
          return(EXIT_FAILURE);
        }
        if(matriz[i][j] > intensidad){
          std::cerr << MSJ_ERROR_INTENSIDAD_MAX << std::endl;
          return(EXIT_FAILURE);
        }
        if(matriz[i][j] < 0){
            std::cerr << MSJ_ERROR_INTENSIDAD_MIN << std::endl;
            return(EXIT_FAILURE);
        }
        line = line.substr(pos_space);

      }
      /*Si no hay un espacio mas adelante quiere decir que la linea termina inmediatamente
       * o queda solo un numero por leer. Si es lo primero se retrocede j, ya que esta
       * iteracion del ciclo no pudo guardar nada. La variable j_inf se utiliza para chequear
       * que no falten datos en el archivo, ya que en ese caso se entraria en un bucle infinito
       * al disminuir j. Si es lo segundo se guarda el numero que queda. Luego se lee la siguiente
       *  linea en ambos casos.*/
      else{
        if(line.size()){
          try{
            matriz[i][j] = std::stoi(line);
          }
          catch(std::invalid_argument &err)
          {
            std::cerr << MSJ_ERROR_PIXELES << std::endl;
            return(EXIT_FAILURE);
          }
          if(matriz[i][j] > intensidad){
            std::cerr << MSJ_ERROR_INTENSIDAD_MAX << std::endl;
            return(EXIT_FAILURE);
          }
          if(matriz[i][j] < 0){
            std::cerr << MSJ_ERROR_INTENSIDAD_MIN << std::endl;
            return(EXIT_FAILURE);
          }
        }
        else{

          if(j_inf == j){
            std::cerr << MSJ_ERROR_TAMANO << std::endl;
            return(EXIT_FAILURE);
          }

          j_inf = j;
          j--;


        }
        getline(input, line);

      }
    }
  }
  return(EXIT_SUCCESS);
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

std::string quitarEspaciosInicio(std::string input){
  int i;
  for(i = 0; i < int(input.length()); i++){
    if(!isspace(input[i]))
      break;
  }
  return input.substr(i);
}

int encontrarEspacio(std::string input){
  int i;
  for(i = 0; i < int(input.length()); i++){
    if(isspace(input[i]))
      return i;
  }
  return -1;
}
