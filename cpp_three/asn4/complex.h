/*
 Assignment	: #4
 Class		: CST 136
 File Name	: complex.h
 Date		: 7/29/12
 Author		: Nhan Tran
 Description: Complex is a class to represent complex numbers. A complex number is in the form of a + bi where 'a' is a real number
			  and 'b' is an imaginary number and 'i' is the square root of -1. This class holds two double member variables to
			  represent the real and imaginary parts of a complex number.
 */


#ifndef COMPLEX_H
#define	COMPLEX_H

#include <iostream>

using namespace std;

class Complex
{
public:
	friend ostream& operator<<(ostream &out, Complex &aComplex);
	friend istream& operator>>(istream &in, Complex &aComplex);

	Complex(double r = 0.0, double i = 0.0);
	double real() const { return m_real; }
	double imaginary() const { return m_imaginary; }

	Complex operator-() const	//unary negation
		{ return Complex(-m_real, -m_imaginary); }
	
	Complex &operator+=(const Complex &rhs);	
	Complex &operator-=(const Complex &rhs);
	Complex &operator*=(const Complex &rhs);
	Complex &operator/=(const Complex &rhs);

private:
		
	double m_real;
	double m_imaginary;
};

Complex operator+(const Complex &lhs, const Complex &rhs);
Complex operator-(const Complex &lhs, const Complex &rhs);
Complex operator*(const Complex &lhs, const Complex &rhs);
Complex operator/(const Complex &lhs, const Complex &rhs);
bool operator==(const Complex &lhs, const Complex &rhs);
bool operator!=(const Complex &lhs, const Complex &rhs);
bool operator<(const Complex &lhs, const Complex &rhs);
bool operator<=(const Complex &lhs, const Complex &rhs);
bool operator>(const Complex &lhs, const Complex &rhs);
bool operator>=(const Complex &lhs, const Complex &rhs);

#endif