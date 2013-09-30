/*
 Assignment	:  #2
 Class		:  CST 136
 File Name	: SafeArray.cpp
 Date		: 7/15/12
 Author		: Nhan Tran
 Description: Implementation file for SafeArray
 */

#include "array.h"

SafeArray::SafeArray(int ubound, int lbound) : Array(ubound, lbound)
{
}
//
//SafeArray::SafeArray(const Array& anArray) : Array(anArray)
//{
//}

ELEMENT_TYPE SafeArray::get(int index) const
{
	boundsCheck(index);
	return Array::get(index);
}

void SafeArray::set(int index, ELEMENT_TYPE value)
{
	boundsCheck(index);
	Array::set(index, value);
}

//Name: boundsCheck
//Desc: exits the program if index is not within bounds
void SafeArray::boundsCheck(int checkIndex) const
{
	if (checkIndex > upperBound() || checkIndex < lowerBound())
		errorExit("Error index out of bounds. ", 3);
}