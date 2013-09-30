
/*
 Assignment	: #3
 Class		: CST 136
 File Name	: array.h
 Date		: 7/22/12
 Author		: Nhan Tran
 Description: Array is a class that creates an array using a defined upper and lower bound.

 Modifcation: 
 7/22 - Array class has changed to a class template but keeps the same functionality as before. Added at() which returns 
 a reference to an index within the array. Also the copy style has been changed from a deep copy to a shallow copy. 
 Shallow copy is the default copy behavior so a copy constructor is not needed.
 */

#ifndef ARRAY_H
#define ARRAY_H

#include "refCounter.h"
#include <string>
#include <iostream>

using namespace std;

enum arrayError {NOERR, CTR_OBNDS, CRT_BADALLOC, SCRT_OBNDS} ;

template<class ELEMENT_TYPE>
class Array
{
public:
		Array(int ubound, int lbound = 0);
		~Array();		//destructor
		int upperBound() const { return m_upperBound; }
		int lowerBound() const { return m_lowerBound; }
		int numElements() const { return (m_upperBound - m_lowerBound + 1); }
		int size() const { return sizeof(ELEMENT_TYPE) * numElements(); }
		
		//Name: set()
		//Desc: takes in the logical index that's between lower and upper, converts it to the physical index and puts a value in it
		void set(int index, ELEMENT_TYPE value) { m_Array[index - lowerBound()] = value; }

		//Name: get()
		//Desc: takes in the logical index that's between lower and upper and converts it to the physical index and returns the value
		ELEMENT_TYPE get(int index) const { return m_Array[index - lowerBound()]; }	//if Array(10, 5), index 10 is position Array[5] because index (10) - lowerBound (5) = 5

		//Name: at()
		//Desc: returns a reference to an index which can be printed out or used to assign a value to
		ELEMENT_TYPE &at(int index) { return m_Array[index - lowerBound()]; }

protected:
		void errorExit(string message, arrayError errorCode) const;

private:
		int m_upperBound;
		int m_lowerBound;
		ELEMENT_TYPE* m_Array;
		RefCounter m_rCount;
};

/*
 Description: SafeArray is a class derived from the Array class. This class adds additional functionality of
			  checking the bounds of the Array when setting or getting a value from an index.
*/

template<class ELEMENT_TYPE>
class SafeArray : public Array<ELEMENT_TYPE>
{

public:
		SafeArray(int ubound, int lbound = 0);
		ELEMENT_TYPE get(int index) const;
		void set(int index, ELEMENT_TYPE value);
		ELEMENT_TYPE &at(int index) 
			{	
				boundsCheck(index);
				return Array::at(index); }

private:
		void boundsCheck(int checkIndex) const; 
};

#include "array.inc"
 
#endif