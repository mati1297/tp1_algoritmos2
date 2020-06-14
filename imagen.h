#ifndef IMAGEN_H
#define IMAGEN_H

#include "lista.h"
#include "complejo.h"
#include "vector.h"

#include <cmath>
#include <fstream>
#include <string>
#include <iostream>

#define FILAS_DEF 1
#define COLUMNAS_DEF 1
#define INTENSIDAD_DEF 5
#define VALOR_DEF 0
#define NUMEROS_LINEA_SALIDA 19

#define PGM_COMENTARIO '#'
#define PGM_INDICADOR "P2"
#define PGM_INDICADOR_WIN "P2\r"
#define COMENTARIO "TP0 Algoritmos y Programacion 2. Fiuba. 2020"
#define SPACE " \t\v\f\r"

#define MSJ_ERROR_PGM_INDICADOR "Error al leer (indicador distinto de P2)"
#define MSJ_ERROR_FILAS "Error al leer (filas)"
#define MSJ_ERROR_COLUMNAS "Error al leer (columnas)"
#define MSJ_ERROR_INTENSIDAD "Error al leer (intensidad)"
#define MSJ_ERROR_PIXELES "Error al leer (pixeles)"
#define MSJ_ERROR_TAMANO "Error al leer (el tamaño de la imagen es menor que el declarado)"
#define MSJ_ERROR_MEMORIA "Error al cambiar el tamaño de la matriz de la imagen"
#define MSJ_ERROR_INTENSIDAD_MAX "Error al leer lo pixeles, la intensidad supera a la declarada"
#define MSJ_ERROR_INTENSIDAD_MIN "Error al leer los pixeles, la intensidad es menor que 0"
#define MSJ_ERROR_INTENSIDAD_INVALIDA "Error en intensidad máxima, debe ser mayor que 0"
#define MSJ_ERROR_TAMANO_INVALIDO "Error en el tamaño, uno de los ejes es 0 o menor"
#define MSJ_ERROR_LINEA_VACIA "Error, hay una linea vacia"


/* Clase Imagen
 * Clase que reprensenta a una imagen PGM. Con sus atributos:
 * filas, columnas, intensidad, y la propia imagen,
 * un vector de vectores que forman una matriz con los valores de la
 * imagen para cada pixel.
*/
class Imagen{
private:
  int filas;
  int columnas;
  int intensidad;
  Vector<Vector<int>> matriz;
  
  /*Recibe una cadena, la valida, guarda el valor como intensidad y devuelve la cadena cortada*/
  int setIntensidad(string&);
  
  /*Recibe una cadena, la valida, guarda el valor como cantidad de columnas y devuelve la cadena cortada*/
  int setColumnas(string&);
  
  /*Recibe una cadena, la valida, guarda el valor como cantidad de filas y devuelve la cadena cortada*/
  int setFilas(string&);
  
  /*Recibe una input stream, lo lee, lo valida y carga la matriz*/
  int setMatriz(std::istream&);
  
  /*Actualiza el tamaño de la matriz al tamaño actual que indica los atributos columnas y filas*/
  int resizeMatriz();

public:
  /*Constructor por defecto del objeto Imagen.
  * Los valores por defecto estan definidos por las macros
  * COLUMNAS_DEF y FILAS_DEF. Se asume que no hay error al hacer el resize
  * al ser la cantidad por defecto un valor chico.*/
  Imagen();

  /*Constructor del objeto imagen.
  * Se le pasa: cantidad de filas, columnas, el valor maximo
  * de intensidad, y el valor con que se quiere rellenar la imagen
  * (entre 0 e intensidad, si se pasa algo mayor o menor llena con VALOR_DEF).
  * En caso de haber un error al hacer el resize, se crea la matriz
  * con COLUMNAS_DEF Y FILAS_DEF.*/
  Imagen(int, int, int, int);

  /* Constructor por copia.*/
  Imagen(const Imagen&);

  /*Destructor del objeto imagen.*/
  ~Imagen();

  /*Operador de copia*/
  Imagen& operator=(const Imagen&);

  /* Operador de comparacion */
  bool operator==(const Imagen&) const;

  /* Operador de comparacion */
  bool operator!=(const Imagen&) const;

  /*Getter para cantidad de filas*/
  int getFilas() const;

  /*Getter para cantidad de columnas*/
  int getColumnas() const;

  /*Getter para intensidad maxima*/
  int getIntensidad() const;

  Imagen transformar(const lista<string>) const;

  /* Metodo para cargar una imagen a partir de un archivo PGM.
  * Si encuentra un error imprime un mensaje y cierra el programa.
  * Al leer, el metodo ignora todos los comentarios (que comienzan
  * con "#" segun la macro definida). Además ignora todos los espacios
  * que pueda haber al comienzo de una linea. Si una linea está totalmente
  * vacia se tomará como un error. */
  int readPGM(std::istream&);

  /* Se guarda el objeto imagen en un archivo ".pgm". La cantidad de numeros
  * por linea esta dado por la macro NUMEROS_LINEA_SALIDA.*/
  void savePGM(std::ostream&);


};



#endif // IMAGEN_H
