#ifndef _COMPLEJO_H_INCLUDED_
#define _COMPLEJO_H_INCLUDED_

#include <iostream>
#include <cmath>
#include <limits>
#include <string>

class complejo {
	double re_, im_;
public:
	complejo(); //Constructor por defecto
	complejo(double); //Constructor parte real
	complejo(double, double); //Constructor parte real e imaginaria.
	complejo(const complejo &); //Constructor por copia
	~complejo();

	void SetReal(double xx){re_=xx;} //Set parte real
	void SetImag(double yy){im_=yy;} //Set parte imaginaria
	double re() const; //Devuelve parte real
	double im() const; //Devuelve parte imaginaria
	double modulo() const; //Devuelve el modulo
	double modulo2() const; //Devuelve el modulo al cuadrado
	double fase() const; //Devuelve el argumento
	complejo conjugado() const; //Devuelve el complejo conjugado
	bool zero() const; //Devuelve true si parte real e imaginaria son 0
	complejo expc() const;
	complejo logc() const; //Logaritmo en base e.
	complejo seno() const;
	complejo coseno() const;
	complejo senoh() const;
	complejo cosenoh() const;
	complejo arctan() const;
	complejo arccos() const;
	complejo operator+(complejo const &) const;
	complejo operator-(complejo const &) const;
	complejo operator*(complejo const &) const;
	complejo operator/(complejo const &) const; //En caso de division por 0 o 0/0, devuelve parte real e imaginaria como inf.
	complejo operator/(double) const; //Divide por un numero real.
	complejo& operator=(complejo const &);
	complejo& operator*=(complejo const &);
	complejo& operator+=(complejo const &);
	complejo& operator-=(complejo const &);
	complejo operator^(complejo const & pot) const;
	bool operator==(double) const;
	bool operator==(complejo const &) const;
	bool operator!=(double) const;
	bool operator!=(complejo const &) const;

	friend std::ostream &operator<<(std::ostream &, const complejo &);
};

#endif
