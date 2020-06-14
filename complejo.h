#ifndef _COMPLEJO_H_INCLUDED_
#define _COMPLEJO_H_INCLUDED_

#include <iostream>

class complejo {
	double re_, im_;
public:
	complejo();
	complejo(double);
	complejo(double, double);
	complejo(const complejo &);
	complejo const &operator=(complejo const &);
	complejo const &operator*=(complejo const &);
	complejo const &operator+=(complejo const &);
	complejo const &operator-=(complejo const &);
	~complejo();

	void SetReal(double xx){re_=xx;}
	void SetImag(double yy){im_=yy;}
	double re() const;
	double im() const;
	double modulo() const;
	double modulo2() const;
  double fase() const;
	complejo const &conjugar();
	complejo const conjugado() const;
	bool zero() const;
	complejo const logc() const;
	complejo const expc() const;
	complejo const & seno();
	complejo const & coseno();
	complejo const operator+(complejo const &);
	complejo const operator-(complejo const &);
	complejo const operator*(complejo const &);
	complejo const operator/(complejo const &);
	complejo const operator/(double);
	complejo const operator^(complejo const & pot);
	friend bool operator==(complejo const &, double);
	friend bool operator==(complejo const &, complejo const &);

	friend std::ostream &operator<<(std::ostream &, const complejo &);
	friend std::istream &operator>>(std::istream &, complejo &);
};

#endif
