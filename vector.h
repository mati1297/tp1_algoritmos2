#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>

#define DEFAULT_SIZE 0

using namespace std;

template <typename T>
class Vector {
      T *ptr; //Puntero a la primera posición del vector
      size_t size;

      public:
        Vector(); // Constructor por defecto
        Vector(const size_t); // Constructores por parametros
        Vector(const size_t, const T&);
        Vector(const Vector & ); // Constructor por copia
        ~Vector(); // Destructor

        T & operator[](const size_t) const;
        Vector & operator=(const Vector&);
        bool operator==(const Vector&) const;
        bool operator!=(const Vector&) const;
        
        /*Permiten cambiar el tamano del vector, se le puede pasar
         * como segundo parametro el valor por defecto para rellenar
         * en caso de que se agrande, de lo contrario rellena con
         * valor nulo del tipo de dato */
        void resize(const size_t);
        void resize(const size_t, const T&);
        
        template <typename U>
        friend ostream& operator<<(ostream&, const Vector<U>&);
    };

template <typename T>
Vector<T>::Vector(){
  ptr = new T[DEFAULT_SIZE];
  size = DEFAULT_SIZE;
}

template <typename T>
Vector<T>::Vector(const size_t l){
  if(!l){
	ptr = NULL;
	size = 0;
  }
  else{
    ptr = new T[l];
    size = l;
    
    for(size_t i = 0; i < size; i++){
		ptr[i] = T();
	}
  }
}

template <typename T>
Vector<T>::Vector(const size_t l, const T& defecto){
  if(!l){
	ptr = NULL;
	size = 0;
  }
  else{
    ptr = new T[l];
    size = l;
    
    for(size_t i = 0; i < size; i++){
		ptr[i] = defecto;
	}
  }
}

template <typename T>
Vector<T>::Vector(const Vector & orig){
  if (!orig.size) {
    ptr = NULL;
    size = 0;
  }
  else {
    size = orig.size;
    ptr = new T[size];

    for (size_t i = 0; i < size; i++) {
      ptr[i] = orig.ptr[i];
    }
  }
}

template <typename T>
Vector<T>::~Vector(){
  delete[] ptr;
}


template <typename T>
T& Vector<T>::operator[](const size_t index) const {
  if (index < size) {
    return ptr[index];
  }
  return *ptr;
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& right){
	if(*this == right)
		return *this;
	delete[] ptr;
	if (!right.size) {
      ptr = NULL;
      size = 0;
	}
	else {
      size = right.size;
      ptr = new T[size];

      for (size_t i = 0; i < size; i++) {
        ptr[i] = right.ptr[i];
    }
  }
  return *this;
}

template <typename T>
bool Vector<T>::operator==(const Vector<T>& right) const{
	for(size_t i = 0; i < size; i++){
		if(ptr[i] != right.ptr[i])
			return false;
	}
	return true;
}

template <typename T>
bool Vector<T>::operator!=(const Vector<T>& right) const{
	for(size_t i = 0; i < size; i++){
		if(ptr[i] != right.ptr[i])
			return true;
	}
	return false;
}

template <typename T>
void Vector<T>::resize(const size_t l){
	T* old_ptr = ptr;
	size_t old_size = size;
	if(!l){
		size = 0;
		ptr = NULL;
	}
	else{
		size = l;
		T* new_ptr = new T[l];
		try{
			new_ptr = new T[l];
		}
		catch(std::bad_alloc &err){
			throw err;
		}
		ptr = new_ptr;
		size_t i = 0;
		for( ; i < l && i < old_size; i++){
			ptr[i] = old_ptr[i];
		}
		for( ; i < l; i++){
			ptr[i] = T();
		}
	}
	delete[] old_ptr;
}


template <typename T>
void Vector<T>::resize(const size_t l, const T& def){
	T* old_ptr = ptr;
	size_t old_size = size;
	if(!l){
		size = 0;
		ptr = NULL;
	}
	else{
		size = l;
		T* new_ptr;
		try{
			new_ptr = new T[l];
		}
		catch(std::bad_alloc &err){
			throw err;
		}
		ptr = new_ptr;
		size_t i = 0;
		for( ; i < l && i < old_size; i++){
			ptr[i] = old_ptr[i];
		}
		for( ; i < l; i++){
			ptr[i] = def;
		}
	}
	delete[] old_ptr;
}

template <typename T>
ostream& operator <<(ostream& os, const Vector<T>& vec){
	if(!vec.size)
		os << "Vector vacio";
	for(size_t i = 0; i < vec.size; i++){
		os << vec.ptr[i] << ' ';
	}
	return os;
}

#endif
