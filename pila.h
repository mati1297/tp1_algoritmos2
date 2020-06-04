#ifndef PILA__H
#define PILA__H

#include <iostream>

using namespace std;

template <typename T>
class pila{
	class nodo{
		friend class pila;
		
		nodo* sig;
		T dato;
		
	public:
		nodo();
		nodo(const T&);
		~nodo();
		template <typename U> friend ostream& operator<<(ostream& os, const pila<U>&);
	};
	
	size_t tam;
	nodo * pri;

public:	
	typedef T t_dato;
	typedef nodo t_nodo;
	
	pila();
	pila(const pila<T>&);
	~pila();
	bool vacia() const;
	bool llena() const;
	T pop();
	void push(const T&);
	
	
	template <typename U> friend ostream& operator<<(ostream& os, const pila<U>&);
};


template <typename T>
pila<T>::nodo::nodo(){
	sig = 0;
}

template <typename T>
pila<T>::nodo::nodo(const T& dato_){
	sig = 0;
	dato = dato_;
}

template <typename T>
pila<T>::nodo::~nodo(){
}

template <typename T>
pila<T>::pila(){
	tam = 0;
	pri = 0;
}

template <typename T>
pila<T>::pila(const pila<T>& orig){
	nodo* ant;
	tam = orig.tam;
	for(nodo* p = orig.pri; p; p = p->sig){
		nodo* nuevo = new nodo(p.dato);
		
		if(!ant)
			pri = nuevo;
		else
			ant->sig = nuevo;
			
		ant = nuevo;
	}
}

template <typename T>
pila<T>::~pila(){
	for(nodo* p = pri; p; ){
		nodo* q = p->sig;
		delete p;
		p = q;
	}
}

template <typename T>
bool pila<T>::vacia() const{
	return !tam ? true : false;
}

template <typename T>
bool pila<T>::llena() const{
	return tam ? true : false;
}

template <typename T>
T pila<T>::pop(){
	if(!tam)
		throw std::logic_error("Pila vacia");
	T dato_ = pri->dato;
	nodo* p = pri;
	pri = p->sig;
	tam--;
	delete p;
	return dato_;
}

template <typename T>
void pila<T>::push(const T& dato_){
	nodo* nuevo = new nodo(dato_);
	nuevo->sig = pri;
	pri = nuevo;
	tam++;
}

template <typename T> 
ostream& operator<<(ostream& os, const pila<T>& pila_){
	if(!pila_.tam)
		os << "La pila esta vacia";
	for(typename pila<T>::nodo * p = pila_.pri; p; p = p->sig){
		os << p->dato << " ";
	}
	return os;
}


#endif


