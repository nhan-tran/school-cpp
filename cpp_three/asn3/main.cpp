#include <iostream>
#include "array.h"

#ifdef _WIN32
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

using namespace std;

void test()
{
	SafeArray test1(10,5);	//test default constructor

	//fill array with values 
	for (int i = test1.lowerBound(); i <= test1.upperBound(); i++)
	{
		test1.set(i, i * 10);
		cout << "\narray index " << i << " has " << test1.get(i);	
	}

	cout << "\nsize of test1 " << test1.size() << endl;

	test1.set(5, 999);
	cout << "\ntestArray index 5 after " << test1.get(5) << endl;

		for (int i = test1.lowerBound(); i <= test1.upperBound(); i++)
	{
		//test1.set(i, i * 10);
		cout << "\narray index " << i << " has " << test1.get(i);	
	}

	SafeArray test2(test1);
	SafeArray test3(SafeArray(4,2));

	//cout << "test2 index 5 " << test2.get(5); //check copy

	//test2.set(4, 888); //try to set out of bound
	//test5.set(55,2222);
}

int main()
{
	cout << "The size of the TYPE_DEF is " << sizeof(ELEMENT_TYPE) << endl;
	
	test();

#ifdef _WIN32
	if (_CrtDumpMemoryLeaks()) {
		cout << "Memory leaks!" << endl;
	}
#endif

	return 0;
}