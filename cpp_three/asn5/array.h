
/*
 Assignment	: #5
 Class		: CST 136
 File Name	: array.h
 Date		: 8/4/12
 Author		: Nhan Tran
 Description: Array is a class that creates an array using a defined upper and lower bound.

 Modifcation: 
 7/22
 Array class has changed to a class template but keeps the same functionality as before. Added at() which returns 
 a reference to an index within the array. Also the copy style has been changed from a deep copy to a shallow copy. 
 Shallow copy is the default copy behavior so a copy constructor is not needed.

 8/4
 Removed at(), get(), set(), errorExit()
 Added overloaded assignment operator=
 Added overloaded array index operator[] for both non-const and const. This allows for easy write/read access to the m_Array
	for non-const objects and read access for const objects. 
 Added exception detection and throwing of three exceptions: ERR_BAD_BOUNDS when array is setup with invalid bounds, 
	ERR_MEM_ALLOC for bad memory allocation, and ERR_OUT_OF_BOUNDS for when a SafeArray goes out of the set bounds.

 */

#define ERR_BAD_BOUNDS	1
#define ERR_MEM_ALLOC	2
#define ERR_OUT_OF_BOUNDS	3

#ifndef ARRAY_H
#define ARRAY_H

#include "refCounter.h"
#include <string>
#include <iostream>

using namespace std;

/*
Constraints for ELEMENT_TYPE datatype for the Array<> template class:
	-ELEMENT_TYPE must have a default constructor if it is a user-defined type
	-ELEMENT_TYPE must be copiable
	-ELEMENT_TYPE must support the assignment operator

*/

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
		
		ELEMENT_TYPE& operator[](const int index) { return m_Array[index - lowerBound()]; }
		const ELEMENT_TYPE& operator[](const int index) const { return m_Array[index - lowerBound()]; }
			
		const Array<ELEMENT_TYPE>& operator=(const Array<ELEMENT_TYPE>& anArray);	//overloading assignment operator

private:
		int m_upperBound;
		int m_lowerBound;
		ELEMENT_TYPE* m_Array;		//ptr to an array of ELEMENT_TYPE	
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
		ELEMENT_TYPE& operator[](const int index); 
		const ELEMENT_TYPE& operator[](const int index) const;

private:
		void boundsCheck(int checkIndex) const; 
};

#include "array.inc"
 
#endif