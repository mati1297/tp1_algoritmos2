#ifndef _COMPLEJO_H_INCLUDED_
#define _COMPLEJO_H_INCLUDED_

#include <iostream>

class complejo {
	double re_, im_;
	complejo multiplicar_i() const;
public:
	complejo();
	complejo(double);
	complejo(double, double);
	complejo(const complejo &);
	complejo &operator=(complejo const &);
	complejo &operator*=(complejo const &);
	complejo &operator+=(complejo const &);
	complejo &operator-=(complejo const &);
	~complejo();

	void SetReal(double xx){re_=xx;}
	void SetImag(double yy){im_=yy;}
	double re() const;
	double im() const;
	double modulo() const;
	double modulo2() const;
	double fase() const;
	complejo& conjugar();
	complejo conjugado() const;
	bool zero() const;
	complejo logc() const;
	complejo expc() const;
	complejo seno() const;
	complejo coseno() const;
	complejo senoh() const;
	complejo cosenoh() const;
	complejo operator+(complejo const &) const;
	complejo operator-(complejo const &) const;
	complejo operator*(complejo const &) const;
	complejo operator/(complejo const &) const;
	complejo operator/(double) const;
	complejo operator^(complejo const & pot) const;
	bool operator==(double) const;
	bool operator==(complejo const &) const;
	bool operator!=(double) const;
	bool operator!=(complejo const &) const;

	friend std::ostream &operator<<(std::ostream &, const complejo &);
	friend std::istream &operator>>(std::istream &, complejo &);
};

#endif
