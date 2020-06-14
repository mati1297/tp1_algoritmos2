#include "complejo.h"
#include <iostream>
#include <cmath>

using namespace std;

complejo::complejo() : re_(0), im_(0)
{
}

complejo::complejo(double r) : re_(r), im_(0)
{
}

complejo::complejo(double r, double i) : re_(r), im_(i)
{
}

complejo::complejo(complejo const &c) : re_(c.re_), im_(c.im_)
{
}

complejo const &
complejo::operator=(complejo const &c)
{
	re_ = c.re_;
	im_ = c.im_;
	return *this;
}

complejo const &
complejo::operator*=(complejo const &c)
{
	double re = re_ * c.re_
	         - im_ * c.im_;
	double im = re_ * c.im_
	         + im_ * c.re_;
	re_ = re, im_ = im;
	return *this;
}

complejo const &
complejo::operator+=(complejo const &c)
{
	double re = re_ + c.re_;
	double im = im_ + c.im_;
	re_ = re, im_ = im;
	return *this;
}

complejo const &
complejo::operator-=(complejo const &c)
{
	double re = re_ - c.re_;
	double im = im_ - c.im_;
	re_ = re, im_ = im;
	return *this;
}

complejo::~complejo()
{
}



double
complejo::re() const
{
	return re_;
}

double complejo::im() const
{
	return im_;
}

double
complejo::modulo() const
{
	return std::sqrt(re_ * re_ + im_ * im_);
}

double
complejo::modulo2() const
{
	return re_ * re_ + im_ * im_;
}

double
complejo::fase() const
{
	if(this->zero())
		return 0;

    return atan2(im_,re_);//devuelve en grados
//  return atan2(im_,re_)*180/3.14159265359 --> definir pi o usar el de la biblioteca
}


complejo const &
complejo::conjugar()
{
	im_*= -1;
	return *this;
}

complejo const
complejo::conjugado() const
{
	return complejo(re_, -im_);
}

bool
complejo::zero() const
{
#define ZERO(x) ((x) == +0.0 && (x) == -0.0)
	return ZERO(re_) && ZERO(im_) ? true : false;
}


complejo const
complejo::operator+(const complejo & r)
{
return complejo(this->re_ + r.re_ , this->im_ + r.im_);
}


complejo const
complejo::operator-(const complejo & r)

{

return complejo(re_ - r.re_ , im_ - r.im_);

}

complejo const
complejo::operator*(complejo const &x)
{
	complejo r(x.re_ * re_ - x.im_ * im_,
	          x.re_ * im_ + x.im_ * re_);
	return r;
}

complejo const
complejo::operator/(complejo const &x)
{
	re_ = (re_*x.re_)/x.modulo2();
	im_ = (im_*x.im_*-1)/x.modulo2();

	return *this;
}

complejo const
complejo::operator/(double f)
{
	return complejo(re_ / f, im_ / f);
}


bool
operator==(complejo const &c, double f)
{
	bool b = (c.im_ != 0 || c.re_ != f) ? false : true;
	return b;
}

bool
operator==(complejo const &x, complejo const &y)
{
	bool b = (x.re_ != y.re_ || x.im_ != y.im_) ? false : true;
	return b;
}

ostream &
operator<<(ostream &os, const complejo &c)
{
	return os << "("
	          << c.re_
	          << ", "
	          << c.im_
	          << ")";
}

complejo const
complejo::logc() const
{
//	if(*this.zero())
//		return 0;
	double mod, ang;
	mod= (*this).modulo();
	mod = log(mod);
	ang= (*this).fase();

	return complejo(mod, ang);
}


complejo const
complejo::expc() const
{
	double mod,fase;
	mod = exp(re_)*cos(im_);
	fase = exp(re_)*sin(im_);

	return complejo(mod,fase);
}

complejo const & complejo::seno() {
	double aux = re_;
	re_ = sin(re_) * cosh(im_);
	im_ = cos(aux) * sinh(im_);
	return *this;
}

complejo const & complejo::coseno() {
	double aux = re_;
	re_ = cos(re_) * cosh(im_);
	im_ = -sin(aux) * sinh(im_);
	return *this;
}

complejo const
complejo::operator^(complejo const & pot)
{
//	if (pot.im_ == 0)
//		{
		//	if (pot.re_ == 1)
	//			return *this;
//			return *this^(pot-1); //porque -1?
//	}
complejo z;
	z = this->logc();

	z*= pot;

	return z.expc();


	//return *this;
}
