
/*
 Assignment	: #5
 Class		: CST 136
 File Name	: refCounter.h
 Date		: 8/4/12
 Author		: Nhan Tran
 Sources	: Michael Hoffman - Stack Class Template http://home.comcast.net/~oit_hoffmanm/cst136/lectures/15a_refCounter_h.txt
 Description: This refCounter class has one variable to act as a counter. The purpose of the class object is to keep track of the number
			  of references made to an object (in this case the Array/SafeArray object) containing a refCounter object.

Modification:
8/4
Added overloaded assignment operator=
 */

#ifndef  refCounter_H
#define  refCounter_H

class RefCounter
{
  public  :

    RefCounter();

    RefCounter(const RefCounter  &rhs);

    ~RefCounter();

    bool  onlyInstance() const	{  return *m_cnt == 1;  }
	const RefCounter& operator=(const RefCounter& rc);

  private  :

    int  *m_cnt;
};


#endif
