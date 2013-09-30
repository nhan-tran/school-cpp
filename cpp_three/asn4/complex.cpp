/*
 Assignment	: #4
 Class		: CST 136
 File Name	: complex.h
 Date		: 7/29/12
 Author		: Nhan Tran
 Description: Implementation for complex.h
*/

#include "complex.h"
#include <iostream>
#include <math.h>
#include <string>
using namespace std;

Complex::Complex(double r , double i) : 
	m_real(r), m_imaginary(i)
{	
}

Complex &Complex::operator+=(const Complex &rhs)
{
	*this = *this + rhs;	//take this Complex object we are in and add it with the rhs object. addition of Complex has been defined.
	return *this;
}

Complex &Complex::operator-=(const Complex &rhs)
{
	*this = *this - rhs;	//take this Complex object we are in and substract it with the rhs object. substraction of Complex has been defined.
	return *this;
}

Complex &Complex::operator*=(const Complex &rhs)
{
	*this = *this * rhs;	//take this Complex and multiply it with rhs. multiplication of Complex has been defined.
	return *this;
}

Complex &Complex::operator/=(const Complex &rhs)
{
	*this = *this / rhs;	//take this Complex and divide it with the rhs. division of Complex has been defined.
	return *this;
}

Complex operator+(const Complex &lhs, const Complex &rhs)
	{ return Complex(lhs.real() + rhs.real(), lhs.imaginary() + rhs.imaginary()); }

Complex operator-(const Complex &lhs, const Complex &rhs)
	{ return Complex(lhs.real() - rhs.real(), lhs.imaginary() - rhs.imaginary()); }


//Multiplication:
// (a + bi)(c + di) = (ac - bd) + (ad + bc)i
Complex operator*(const Complex &lhs, const Complex &rhs)
{
	double real = (lhs.real() * rhs.real()) - (lhs.imaginary() * rhs.imaginary());
	double imag = (lhs.real() * rhs.imaginary()) + (lhs.imaginary() * rhs.real());

	return Complex(real, imag); 
}


//Division:
//   (a + bi)     (ac + bd)   (bc - ad)i
//   --------  =  --------- + ----------
//   (c + di)     (c2 + d2)   (c2 + d2)
Complex operator/(const Complex &lhs, const Complex &rhs)
{ 
	double real = ((lhs.real() * rhs.real()) + (lhs.imaginary() * rhs.imaginary())) / (pow(rhs.real(), 2) + pow(rhs.imaginary(), 2));
	double imag = ((lhs.imaginary() * rhs.real()) - (lhs.real() * rhs.imaginary())) / (pow(rhs.real(), 2) + pow(rhs.imaginary(), 2));

	return Complex(real, imag);
}


bool operator==(const Complex &lhs, const Complex &rhs)
{
	return (lhs.real() == rhs.real() &&
			lhs.imaginary() == rhs.imaginary());
}

bool operator!=(const Complex &lhs, const Complex &rhs)
{
	return !(lhs == rhs);	//true if it does not equal. if it does equal the == returns true then this function should return false
}

//lhs a + bi less than rhs c + di when a < c OR (a = c AND b < d)
bool operator<(const Complex &lhs, const Complex &rhs)
{
	return	(	lhs.real() < rhs.real() ||
				(lhs.real() == rhs.real() && lhs.imaginary() < rhs.imaginary()));
}

bool operator<=(const Complex &lhs, const Complex &rhs)
{
	return (lhs == rhs || lhs < rhs);	//if equals or less than return true. == and < was already previously defined
}

bool operator>(const Complex &lhs, const Complex &rhs)
{
	bool x = lhs <= rhs;
	return !(lhs <= rhs);	//if <= evaluates to true then this (>) greater than comparisson is false
}

bool operator>=(const Complex &lhs, const Complex &rhs)
{
	return (lhs == rhs || lhs > rhs);	//if equals or is greater than return true
}

ostream& operator<<(ostream &out, Complex &aComplex)
{
	bool nzReal = (aComplex.m_real != 0);	//real is not zero
	string op;

	if (aComplex.m_real == 0)
	{
		if (aComplex.m_imaginary == 0)
		{
			out << "0";
			return out;
		}
		op = "";
	}
	else
		out << aComplex.m_real;


	if (aComplex.m_imaginary < -1)
	{
		if (nzReal)			//real not zero and imag is negative so make op a minus
			op = " - ";
		else				//real is zero, trim spaces
			op = "-";
		out << op << -aComplex.m_imaginary << "i";	//negate op and show the value
	}
	else
	{
		if (aComplex.m_imaginary == 1)		//if 1 or -1
		{
			if (nzReal)
				op = " + ";
		
			out << op << "i";
		}
		else if (aComplex.m_imaginary == -1)
		{
			if (nzReal)
				out << " - i";
			else
				out << "-i";
		}
		else if (aComplex.m_imaginary == 0)	//not negative and not 1 or 0
		{	
			return out;
		}	
		else
		{			
			if (nzReal)
				op = " + ";
			out << op << aComplex.m_imaginary << "i";	
		}
	}
	return out;
}

istream& operator>>(istream &in, Complex &aComplex)
{
	char op;
	char d;

	in >> aComplex.m_real >> op >> aComplex.m_imaginary >> d;

	if (op == '-')
		aComplex.m_imaginary *= -1;		//if operator is a minus then flip sign of the imaginary

	return in;
}