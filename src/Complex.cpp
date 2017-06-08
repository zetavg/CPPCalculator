#include "Complex.h"

using namespace std;

/*
* Overload operators
*/
/*
Complex& Complex::operator=(const char *number) {
	set_value(number);
	return *this;
}

Complex& Complex::operator=(const Complex &decimal) {
	copy_value_from(decimal);
	return *this;
}*/

ostream& operator <<(ostream& out, const Complex& x)
{
	return out << x.real() << " + " << x.imag() << "*i" << endl;
}

istream& operator >>(istream& in, Complex& x)
{
	return in >> real(x) >> imag(x);
}

bool operator ==(const Complex& a, const Complex& b)
{
	return a.real() == b.real() && a.imag() == b.imag();
}

bool operator !=(const Complex& a, const Complex& b)
{
	return !(a == b);
}

const Complex operator +(const Complex& a, const Complex& b)
{
	return Complex(a.real() + b.real(), a.imag() + b.imag());
}

const Complex operator -(const Complex& a, const Complex& b)
{
	return Complex(a.real() - b.real(), a.imag() - b.imag());
}

const Complex operator *(const Complex& a, const Complex& b)
{
	return Complex(a.real() * b.real() - a.imag() * b.imag(), a.imag() * b.real() + a.real() * b.imag());
}

const Complex operator /(const Complex& a, const Complex& b)
{
	double common = pow(b.real(), 2) + pow(b.imag(), 2);
	return Complex((a.real() * b.real() + a.imag() * b.imag()) / common, (a.imag() * b.real() - a.real() * b.imag()) / common);
}

double& real(Complex& x)
{
	return x.real_;
}

double& imag(Complex& x)
{
	return x.imaginary_;
}