#pragma once

#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Complex
{
public:
	/* Constructors */

	//A default constructor that initializes an object to 0
	Complex() : real_(0), imaginary_(0) { }
	//A constructor that has only a single parameter of type double
	Complex(double realPart) : real_(realPart), imaginary_(0) { }
	//A constructor with two parameters of type double that can be used to set the member variables of an object to any values.
	Complex(double realPart, double imaginaryPart) : real_(realPart), imaginary_(imaginaryPart) { }

	/* Overload operators */

	Complex& operator=(const char*);
	Complex& operator=(const Complex&);
	friend ostream& operator <<(ostream& out, const Complex& x);
	friend istream& operator >>(istream& in, Complex& x);
	friend bool operator ==(const Complex& a, const Complex& b);
	friend bool operator !=(const Complex& a, const Complex& b);
	friend const Complex operator +(const Complex& a, const Complex& b);
	friend const Complex operator -(const Complex& a, const Complex& b);
	friend const Complex operator *(const Complex& a, const Complex& b);
	friend const Complex operator /(const Complex& a, const Complex& b);
	friend double& real(Complex& x);
	friend double& imag(Complex& x);

	double real() const
	{
		return real_;
	}

	double imag() const
	{
		return imaginary_;
	}

private:
	double real_, imaginary_;
};
