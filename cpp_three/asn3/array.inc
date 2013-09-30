/*
 Assignment	:  #3
 Class		:  CST 136
 File Name	: array.cpp
 Date		: 7/22/12
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
		errorExit("Error upper bound is less than lower bound.", CTR_OBNDS);

	//create array the size between the specified upper and lower bound
	m_Array = new ELEMENT_TYPE[numElements()];

	//check memory allocation
	if (!m_Array)
		errorExit("Error - bad allocation of memory.", CRT_BADALLOC);
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


//Name: errorExit()
//Desc: print error message then exit
template<class ELEMENT_TYPE>
void Array<ELEMENT_TYPE>::errorExit(string message, arrayError errorCode) const
{
		cout << '\n' << message << endl;
		cout << "Press Enter to exit. ";
		cin.get();
		exit (errorCode);
}

template<class ELEMENT_TYPE>
SafeArray<ELEMENT_TYPE>::SafeArray(int ubound, int lbound) : Array(ubound, lbound)
{
}

template<class ELEMENT_TYPE>
ELEMENT_TYPE SafeArray<ELEMENT_TYPE>::get(int index) const
{
	boundsCheck(index);
	return Array::get(index);
}


template<class ELEMENT_TYPE>
void SafeArray<ELEMENT_TYPE>::set(int index, ELEMENT_TYPE value)
{
	boundsCheck(index);
	Array::set(index, value);
}

//Name: boundsCheck
//Desc: exits the program if index is not within bounds
template<class ELEMENT_TYPE>
void SafeArray<ELEMENT_TYPE>::boundsCheck(int checkIndex) const
{
	if (checkIndex > upperBound() || checkIndex < lowerBound())
		Array<ELEMENT_TYPE>::errorExit("Error index out of bounds. ", SCRT_OBNDS);
}