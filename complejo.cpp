#include "complejo.h"
#include <iostream>
#include <cmath>
#include <limits>

using namespace std;

complejo::complejo() : re_(0), im_(0){
}

complejo::complejo(double r) : re_(r), im_(0){
}

complejo::complejo(double r, double i) : re_(r), im_(i){
}

complejo::complejo(complejo const &c) : re_(c.re_), im_(c.im_){
}


complejo& complejo::operator=(complejo const &c){
	re_ = c.re_;
	im_ = c.im_;
	return *this;
}

complejo& complejo::operator*=(complejo const &c){
	double re = re_ * c.re_
	         - im_ * c.im_;
	double im = re_ * c.im_
	         + im_ * c.re_;
	re_ = re, im_ = im;
	return *this;
}

complejo& complejo::operator+=(complejo const &c){
	double re = re_ + c.re_;
	double im = im_ + c.im_;
	re_ = re, im_ = im;
	return *this;
}

complejo& complejo::operator-=(complejo const &c){
	double re = re_ - c.re_;
	double im = im_ - c.im_;
	re_ = re, im_ = im;
	return *this;
}

complejo::~complejo(){
}

double complejo::re() const{
	return re_;
}

double complejo::im() const{
	return im_;
}

double complejo::modulo() const{
	return std::sqrt(re_ * re_ + im_ * im_);
}

double complejo::modulo2() const{
	return re_ * re_ + im_ * im_;
}

double complejo::fase() const{
	if(this->zero() || !im_)
		return 0;

    return atan2(im_,re_);
}

complejo complejo::conjugado() const{
	return complejo(re_, -im_);
}

bool complejo::zero() const{
	return !re_ && !im_;
}

complejo complejo::operator+(const complejo & r) const{
	return complejo(re_ + r.re_ , im_ + r.im_);
}


complejo complejo::operator-(const complejo & r) const{
	return complejo(re_ - r.re_ , im_ - r.im_);
}

complejo complejo::operator*(complejo const &x) const{
	return complejo(x.re_ * re_ - x.im_ * im_,
	          x.re_ * im_ + x.im_ * re_);
}

complejo complejo::operator/(complejo const &x) const{
	if(x.zero())
		return complejo(std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity());
	complejo r;
	r.re_ = (re_ * x.re_ + im_ * x.im_)/x.modulo2();
	r.im_ = (im_ * x.re_ - re_ * x.im_)/x.modulo2();
	return r;
}

complejo complejo::operator/(double f) const{
	return complejo(re_ / f, im_ / f);
}


bool complejo::operator==(double f) const{
	return re_ == f && !im_;
}

bool complejo::operator==(complejo const &r) const{
	return re_ == r.re_ && im_ == r.im_;
}

bool complejo::operator!=(double f) const{
	return re_ != f || im_;
}

bool complejo::operator!=(complejo const &r) const{
	return re_ != r.re_ || im_ != r.im_;
}

ostream &
operator<<(ostream &os, const complejo &c){
	return os << "("
	          << c.re_
	          << ", "
	          << c.im_
	          << ")";
}

complejo complejo::logc() const {
	return complejo(log(this->modulo()), this->fase());
}

complejo complejo::expc() const {
	return complejo(exp(re_)*cos(im_), exp(re_)*sin(im_));
}

complejo complejo::seno() const {
	return complejo(sin(re_) * cosh(im_), cos(re_) * sinh(im_));
}

complejo complejo::coseno() const {
	return complejo(cos(re_) * cosh(im_), -sin(re_) * sinh(im_));
}

// cosh(z) = cos(iz)
complejo complejo::senoh() const {
	return (*this * complejo(0,1)).coseno();
}

// sinh(z) = -i * sin(iz)
complejo complejo::cosenoh() const {
	return ((*this * complejo(0,1)).seno()) * complejo(0,-1);
}

complejo complejo::operator^(complejo const & pot) const{
	return (this->logc() * pot).expc();
}
