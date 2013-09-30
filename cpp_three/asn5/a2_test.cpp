#include "array.h"

#include <iostream>
#include "array.h"

#ifdef _WIN32
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

using namespace std;


void test2()
{
	Array<int>	a(10, 5);
	Array<int>  b(2, 1);
	Array<int>	c(9, 3);

	a = a;
	//a.at(5) = 5555;
	//cout << a.at(5) << endl;
	a[5] = 5555;
	cout << a[5] << endl;
	b = a;	//make b equal a... a has 2 copies
	cout << b[5] << endl;

	c[3] = 888;
	a = c;	//make a equal c... c has 2 copies, a has 1?

	cout << a[5] << endl;
	cout << b[5] << endl;
	cout << c[3] << " " << &c[3] << endl;
	cout << a[3] << " " << &a[3] << endl;
	cout << "wait";

	b = c;
	cout << b[5] << endl;
	c[5] = 777;
	cout << "a[5]: " << a[5] << " " << &a[5] << "\nb[5]: " << b[5] << " " << &b[5] << "\nc[5]: " << c[5] << " " << &c[5] << endl;
}

void test3()
{
	SafeArray<int>	a(10, 5);
	SafeArray<int>  b(2, 1);
	SafeArray<int>	c(9, 3);

	a = a;
	//a.at(5) = 5555;
	//cout << a.at(5) << endl;
	a[5] = 5555;
	cout << "a[5]: " << a[5] << endl;
	b = a;	//make b equal a... a has 2 copies
	cout << "b[5]: " << b[5] << endl;

	c[3] = 888;
	a = c;	//make a equal c... c has 2 copies, a has 1?

	cout << "a[5]: " << a[5] << endl;
	cout << "b[5]: " << b[5] << endl;
	cout << "c[3]: " << c[3] << " " << &c[3] << endl;
	cout << "a[3]: " << a[3] << " " << &a[3] << endl;
	cout << "wait" << endl;

	b = c;
	cout << "b[5]: " << b[5] << endl;
	c[5] = 777;
	cout << "a[5]: " << a[5] << " " << &a[5] << "\nb[5]: " << b[5] << " " << &b[5] << "\nc[5]: " << c[5] << " " << &c[5] << endl;
}

void test4()
{
	const SafeArray<int> z(5,3);	//make const Array object
	Array<int> y(10);			//regular object 

	cout << z[3];			//show first index of z... in z ctr had set it to 333
	y[0] = 4444;			//set first index of y, y nis not const it works
	cout << endl << y[0] << endl;
	y = z;					//set y = z, non-const y now has same data as const z due to shallow copy
	cout << y[3] << endl;
	y[3] = 555;				//set the data of y
	cout << "y[3]: " << y[3] << " " << &y[3] << " z[3]: " << z[3] << " " << &z[3] << endl;	//z has change cuz y changed it
}

void test5()
{
	Array<char> w(330, 333);
	const SafeArray<int> z(5,3);	//make const Array object
	SafeArray<int> y(10);			//regular object 
	Array<double> x(30);

	cout << z[3];			//show first index of z... in z ctr had set it to 333
	y[0] = 4444;			//set first index of y, y nis not const it works
	cout << endl << y[0] << endl;
	y = z;					//set y = z, non-const y now has same data as const z due to shallow copy
	cout << y[3] << endl;
	y[3] = 555;				//set the data of y
	cout << "y[3]: " << y[3] << " " << &y[3] << " z[3]: " << z[3] << " " << &z[3] << endl;	//z has change cuz y changed it
	y[9] = 999;		//out of bounds
}


int main()
{
	try { 
	////copy array to array
	//test2();

	//copy safe array to safe array
	test3();
	
	//make const SafeArray, copy const SA to regular Array, set regular Array, const SA is changes as well due to shallow copy
	test4();

	//exception handling
	test5();
	}
	catch(int xcpt)
	{
		if (xcpt == ERR_BAD_BOUNDS)
			cout << "ERR_BAD_BOUNDS";
		else if (xcpt == ERR_OUT_OF_BOUNDS)
			cout << "ERR_OUT_OF_BOUNDS";
	}

#ifdef _WIN32
	if (_CrtDumpMemoryLeaks()) {
		cout << "Memory leaks!" << endl;
	}
#endif

	return 0;
}