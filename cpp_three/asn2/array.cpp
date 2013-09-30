/*
 Assignment	:  #2
 Class		:  CST 136
 File Name	: array.cpp
 Date		: 7/15/12
 Author		: Nhan Tran
 Description: Implementation file for array.h

private:
		int m_upperBound;
		int m_lowerBound;
		ELEMENT_TYPE* m_Array;
*/

#include "array.h"
#include <iostream>
#include <string>

using namespace std;

Array::Array(int ubound, int lbound) :
	m_upperBound(ubound), m_lowerBound(lbound)
{
	//if invalid upper bound print error message then exits
	if (ubound < lbound)
		errorExit("Error upper bound is less than lower bound.", 1);

	//create array the size between the specified upper and lower bound
	m_Array = new ELEMENT_TYPE[numElements()];

	//check memory allocation
	if (!m_Array)
		errorExit("Error - bad allocation of memory.", 2);
}

//copy constructor
Array::Array(const Array& anArray):
	m_upperBound(anArray.upperBound()), m_lowerBound(anArray.lowerBound())
{
	m_Array = new ELEMENT_TYPE[numElements()];
	
	if (!m_Array)
		errorExit("Error - bad allocation of memory.", 2);

	//deep copy elements from anArray
	for (int i = m_lowerBound; i <= m_upperBound; i++)
	{
		set(i, anArray.get(i));
	}
}

//destructor
Array::~Array()
{
	if (m_Array)
		delete [] m_Array;
}

//Name: get()
//Desc: takes in the logical index that's between lower and upper and converts it to the physical index and returns the value
ELEMENT_TYPE Array::get(int index) const
{
	return m_Array[index - lowerBound()];	//if Array(10, 5), index 10 is position Array[5] because index (10) - lowerBound (5) = 5
}


//Name: set()
//Desc: takes in the logical index that's between lower and upper, converts it to the physical index and puts a value in it
void Array::set(int index, ELEMENT_TYPE value)
{
	m_Array[index - lowerBound()] = value;
}


int Array::upperBound() const
{
	return m_upperBound;
}

int Array::lowerBound() const
{
	return m_lowerBound;
}

//return number of elements in the array
int Array::numElements() const
{
	return (m_upperBound - m_lowerBound + 1);
}

//returns the number of buytes allocated to hold all the array elements
int Array::size() const
{
	return sizeof(ELEMENT_TYPE) * numElements();
}

//Name: errorExit()
//Desc: print error message then exit
void Array::errorExit(string message, int errorCode) const
{
		cout << '\n' << message << endl;
		cout << "Press Enter to exit. ";
		cin.get();
		exit (errorCode);
}