/*
 Assignment	: #2
 Class		: CST 136
 File Name	: array.h
 Date		: 7/15/12
 Author		: Nhan Tran
 Description: Array is a class that creates an array using a defined upper and lower bound.
 */

#ifndef ARRAY_H
#define ARRAY_H

#include <string>

using namespace std;
typedef int ELEMENT_TYPE;

class Array
{
public:
		Array(int ubound, int lbound = 0);
		Array(const Array& anArray) ;
		~Array();		//destructor
		int upperBound() const;
		int lowerBound() const;
		int numElements() const;
		ELEMENT_TYPE get(int index) const;
		void set(int index, ELEMENT_TYPE value);
		int size() const;
		void errorExit(string message, int errorCode) const;

private:
		int m_upperBound;
		int m_lowerBound;
		ELEMENT_TYPE* m_Array;
};

#endif


/*
 Author		: Nhan Tran
 Description: SafeArray is a class derived from the Array class. This class adds additional functionality of
			  checking the bounds of the Array when setting or getting a value from an index.
*/


#ifndef SAFEARRAY_H
#define SAFEARRAY_H

#include <iostream>
#include "array.h"


class SafeArray : public Array
{

public:
		SafeArray(int ubound, int lbound = 0);
		//SafeArray(const Array& anArray);
		ELEMENT_TYPE get(int index) const;
		void set(int index, ELEMENT_TYPE value);

private:
		void boundsCheck(int checkIndex) const; 
};

#endif