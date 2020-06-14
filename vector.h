#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>

template <typename T>

class Matriz {

  public:
    class Vector {
      T *ptr; // Apunta a la primer poscicion del vector
      size_t largo;

      public:
        Vector(); // Constructor por defecto
        Vector(const size_t); // Constructor por parametros
        Vector(const Vector & ); // Constructor por copia
        ~Vector(); // Destructor

        T & operator[](const size_t) const;
        Vector & operator=(const Vector) ;
    };

      Matriz(); // Constructor por defecto
      Matriz(const size_t); // Constructor por parametros
      Matriz(const Vector & ); // Constructor por copia
      ~Matriz(); // Destructor

      T & operator[](const size_t) const;

  private:
    Vector* ptr_m;
    // La fila indica el largo de los vectores, columnas la cantidad de vectores
    size_t fil;
    size_t col;
};

template <typename T>
Matriz<T>::Vector::Vector(){
  ptr = new T[10];
  largo = 10;
}

template <typename T>
Matriz<T>::Vector::Vector(const size_t l){
  ptr = new T[l];
  largo = l;
}

template <typename T>
Matriz<T>::Vector::Vector(const Vector & orig){
  if (largo == 0) {
    ptr = NULL;
    largo = 0;
  } else {

    largo = orig.largo;
    ptr = new T[orig.largo];
    T* aux = ptr;

    for (int i = 0; i < largo; i++) {
      *aux = *(orig.ptr);
      aux += 1;
    }
  }
}

template <typename T>
Matriz<T>::Vector::~Vector(){
  delete[] ptr;
}


template <typename T>
T & Matriz<T>::Vector::operator[](const size_t pos) const {
  if (pos < largo) {
    return *(ptr+pos);
  }
  // Si evaluo donde no deberia me devuelve el primer elemento
  return *ptr;
}

/*
template <typename T>
Vector & Matriz<T>::Vector::operator=(const Vector orig) const {

}*/

template <typename T>
Matriz<T>::Matriz(){
  fil = 5;
  col = 5;
  ptr_m = new Vector (6)[5];
  for (size_t i = 0; i < col; i++) {
    *(ptr_m+i) = new Vector(5);
  }
}

template <typename T>
Matriz<T>::Matriz(const size_t){}// Constructor por parametros

template <typename T>
Matriz<T>::Matriz(const Vector & ){} // Constructor por copia

template <typename T>
Matriz<T>::~Matriz(){
  for (size_t i = 0; i < col; i++) {
    delete[] (ptr_m+i);
  }
  delete[] ptr_m;
} // Destructor

template <typename T>
T & Matriz<T>::operator[](const size_t) const{}

#endif
