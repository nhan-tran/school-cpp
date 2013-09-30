/*
 Assignment	: #5
 Class		: CST 136
 File Name	: array.h
 Date		: 8/4/12
 Author		: Nhan Tran
 Description: Implementation file for array.h

private:
		int m_upperBound;
		int m_lowerBound;
		ELEMENT_TYPE* m_Array;
		RefCounter	m_rCounter;
*/

#include "array.h"
#include <iostream>
#include <string>

using namespace std;

template<class ELEMENT_TYPE>
Array<ELEMENT_TYPE>::Array(int ubound, int lbound) :
	m_upperBound(ubound), m_lowerBound(lbound)
{
	//if invalid upper bound print error message then exits
	if (ubound < lbound)
		throw ERR_BAD_BOUNDS;

	//create array the size between the specified upper and lower bound
	m_Array = new ELEMENT_TYPE[numElements()];

	//check memory allocation
	if (!m_Array)
		throw ERR_MEM_ALLOC;
}


//destructor
//the destructor body executes first than any other variables left is destroyed once it exits
//because the refCounter object is not in here once execution leaves this destructor
//the refCounter object is destroyed and goes into its destructor
template<class ELEMENT_TYPE>
Array<ELEMENT_TYPE>::~Array()
{
	if (m_Array && m_rCount.onlyInstance())
		delete [] m_Array;
}


template<class ELEMENT_TYPE>
SafeArray<ELEMENT_TYPE>::SafeArray(int ubound, int lbound) : Array(ubound, lbound)
{
	//Array::operator[](3) = 333;	//assign value to const SafeArray to test if index can read but not write

}


//Name: boundsCheck
//Desc: exits the program if index is not within bounds
template<class ELEMENT_TYPE>
void SafeArray<ELEMENT_TYPE>::boundsCheck(int checkIndex) const
{
	if (checkIndex > upperBound() || checkIndex < lowerBound())
		throw ERR_OUT_OF_BOUNDS;
}

template<class ELEMENT_TYPE>
const Array<ELEMENT_TYPE>& Array<ELEMENT_TYPE>::operator=(const Array<ELEMENT_TYPE>& anArray)	//overloading assignment operator
{
	if(this != &anArray)
	{
		m_upperBound = anArray.m_upperBound;
		m_lowerBound = anArray.m_lowerBound;

		if(m_Array && m_rCount.onlyInstance())		//if m_Array is currently true, holding values, AND is the only instance
			delete [] m_Array;

		m_Array = anArray.m_Array;		//shallow copy Array pointer
		m_rCount = anArray.m_rCount;	//assign RefCounter of anArray to this RefCounter (operator= is overloaded in RefCounter)
	}
	return *this;
}


template<class ELEMENT_TYPE>
ELEMENT_TYPE& SafeArray<ELEMENT_TYPE>::operator[](const int index) 
{ 
	boundsCheck(index);
	return Array::operator[](index);
	//Another way to return:	
	//Array a(0);		//create an Array object
	//a = *this;		//assign this SafeArray into Array a... remember shallow copy
	//return a[index] ;	//uses the [] of 'a' which is of Array type and returns the index, of which since it was a shallow copy is the same as *this object.
}

template<class ELEMENT_TYPE>
const ELEMENT_TYPE& SafeArray<ELEMENT_TYPE>::operator[](const int index) const
{ 
	boundsCheck(index);
	return Array::operator[](index);
}