#include "array.h"

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
	SafeArray<int> test1(10,5);	//test default constructor

	//fill array with values 
	for (int i = test1.lowerBound(); i <= test1.upperBound(); i++)
	{
		test1.set(i, i * 10);
		cout << "\narray index " << i << " has " << test1.get(i);	
	}

	cout << "\nsize of test1 " << test1.size() << endl;

	cout << "Index 8 is : " << test1.at(8);
	test1.at(8) = 12345;
	cout << "\nIndex 8 is : " << test1.at(8);

		for (int i = test1.lowerBound(); i <= test1.upperBound(); i++)
	{
		//test1.set(i, i * 10);
		cout << "\narray index " << i << " has " << test1.at(i);	
	}

	SafeArray<int> test2(test1);	//test shallow copy

	cout << "\n\nnArray test2" << endl;	//should be same ast test1
	for (int i = test2.lowerBound(); i <= test2.upperBound(); i++)
	{
		//test1.set(i, i * 10);
		cout << "\narray index " << i << " has " << &test2.at(i) << " : " << &test1.at(i) << " test1";
	}

	//reset test1
	for (int i = test1.lowerBound(); i <= test1.upperBound(); i++)
	{
		test1.set(i, i * 100);
		cout << "\narray index " << i << " has " << test1.get(i);	
	}

	cout << "\nsize of test1 " << test1.size() << endl;

	test1.set(5, 999);
	cout << "\ntestArray index 5 " << test1.get(5) << endl;

	//look at 2, should be same as the newly reset test1
	cout << "\nArray test2" << endl;
	for (int i = test2.lowerBound(); i <= test2.upperBound(); i++)
	{
		//test1.set(i, i * 10);
		cout << "\narray index " << i << " has " << test2.get(i);
		cout << "\narray index " << i << " has " << &test2.at(i) << " : " << &test1.at(i) << " test1";
	}
	
	//cout << "Address of test1: "; 
	//test1.retArrayAddress;

	//test1.retAddrefCount;

	SafeArray<int> test3(SafeArray<int>(4,2));

	//cout << "test2 index 5 " << test2.get(5); //check copy

	//test2.set(4, 888); //try to set out of bound
	//test5.set(55,2222);
}

void test1()
{
	Array<double> test9(5,0);

	test9.at(0) = 0.22229;
	test9.at(1) = 1.33;
	test9.at(2) = 2.9;
	test9.at(3) = 3.49;
	test9.at(4) = 4;

	for (int i = test9.lowerBound(); i <= test9.upperBound(); i++)
	{
		cout << "\n index " << i << ": " << test9.at(i) << endl;
	}

	SafeArray<char> test0(5,4);
	test0.at(4) = 'c';
	cout << test0.at(4);

}

int main()
{
	test();
	test1();

#ifdef _WIN32
	if (_CrtDumpMemoryLeaks()) {
		cout << "Memory leaks!" << endl;
	}
#endif

	return 0;
}