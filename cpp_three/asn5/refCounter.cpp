

/*
 Assignment	: #5
 Class		: CST 136
 File Name	: refCounter.cpp
 Date		: 8/4/12
 Author		: Nhan Tran
 Sources	: Michael Hoffman - Stack Class Template http://home.comcast.net/~oit_hoffmanm/cst136/lectures/15a_refCounter_c.txt
 Description: Implemetation for refCounter.h
 */

#include	<iostream>
#include	"refCounter.h"
#include	"array.h"
using namespace std;


//
// Constructor
//
RefCounter::RefCounter()  :  m_cnt(new int(1))
{
  if  (! m_cnt)
  {
    cerr  <<  "Memory allocation error!"  <<  endl;
	throw ERR_MEM_ALLOC;
  }
}


//
// Copy constructor
//When the refCounter is copied then the m_count is shallowed
//copied and the value of it is incremented by 1 representing 
//the newest reference of the refCounter object.
//Basically the newest refCounter object will be a new object
//but its m_cnt will point to the same counter

RefCounter::RefCounter(const RefCounter  &rhs) :
  m_cnt(rhs.m_cnt)
{
  (*m_cnt)++;
}


//
// Destructor
//
RefCounter::~RefCounter()
{
	//decrements the count first then checks if 0 then delete
	if  ( ! --(*m_cnt) )	//if 0 then !0 is true, if 1 or more which is true then !true is false
		delete m_cnt;
 }
 
const RefCounter& RefCounter::operator=(const RefCounter& rc)
{
	if(onlyInstance())
		delete m_cnt;	//if 1 then delete
	else				//otherwise if > 1 then --m_cnt
		--(*m_cnt);		//decrement because this is no longer referencing the last object

	m_cnt = rc.m_cnt;	//shallow copy m_count of passed in RefCounter;
	(*m_cnt)++;			//increment the count since it's a new copy

	return *this;
}
