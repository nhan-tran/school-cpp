

/*
 Assignment	: #3
 Class		: CST 136
 File Name	: refCounter.cpp
 Date		: 7/22/12
 Author		: Nhan Tran
 Sources	: Michael Hoffman - Stack Class Template http://home.comcast.net/~oit_hoffmanm/cst136/lectures/15a_refCounter_c.txt
 Description: Implemetation for refCounter.h
 */

#include  <iostream>
#include  "refCounter.h"

using namespace std;


//
// Constructor
//
RefCounter::RefCounter()  :  m_cnt(new int(1))
{
  if  (! m_cnt)
  {
    cerr  <<  "Memory allocation error!"  <<  endl;
    exit(EXIT_FAILURE);
  }
}


//
// Copy constructor
//When the refCounter is copied then the m_count is shallowed
//copied and the value of it is incremented by 1 representing 
//the newest reference of the refCounter object.
//Basically the newest refCounter object will be a new object
//but its m_cnt will point to the same 

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
	if  ( ! --(*m_cnt) )
		delete m_cnt;
 }
 