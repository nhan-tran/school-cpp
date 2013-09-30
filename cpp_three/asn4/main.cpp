
#include "complex.h"
#include <string>

using namespace std;

void test1();
void test2();
void test3();
void show(Complex x, string y);


void test4()	//test cout
{
	Complex a(1, 2);
	Complex b(1, -2);
	Complex c(-1, 2);
	Complex d(-1, -2);
	Complex e(5, 0);
	Complex f(0, 5);
	Complex g(0, -5);
	Complex h(5, 1);
	Complex i(5, -1);
	Complex j(0, 1);
	Complex k(0, -1);
	Complex l(0, 0);

	cout << a << endl << b << endl << c << endl << d << endl << e << endl;
	cout << f << endl << g << endl << h << endl << i << endl << j << endl;

	cout << k << endl;
	cout << l << endl;
	cout << l << endl;
}

void test3()
{
	Complex a(3.1,4.2);
	Complex b(5.1,6.2);
	Complex c;
	
	cout << a << endl << b << endl;

	b += a;
	show(b, "b += a");

	b -= a;
	show(b, "b -= a");

	b *= a;
	show(b, "b *= a");

	b /= a;
	show(b, "b /= a");

	c = b /= a;
	show(c, "c = b /= a");
	show(b, "b");
}

void test5()
{
	int i = 5;
	while (i > 0)
	{cout << "Enter in a complex number: ";
	Complex a;

	cin >> a;

	cout << "Complex number you just created is: " << a << endl;
	i--;
	}
}


int main()
{
	test1();
	test2();
	test3();
	test4();
	test5();

#ifdef _WIN32
	if (_CrtDumpMemoryLeaks()) {
		cout << "Memory leaks!" << endl;
	}
#endif

	return 0;
}

void show(Complex x, string y)
{
	double v_real = x.real();
	double v_img = x.imaginary();
	cout << y << " \t" << v_real << " " << v_img << endl;
}


void test1()
{
	Complex a;
	Complex b(3.3, 9.9);
	Complex c;
	Complex d(10,5);
	Complex e;


	show(a, "a");	//show default
	show(b, "b");
	show(-b, "-b");	//negated value

	//no such thing c = +b;		//unary plus
	show(c, "c");	

	a = d + b;
	show(d, "d");
	show(a, "a: d + b");

	a = a - a;
	show(a, "a");
	a = Complex(1.1, 1.1);
	
	show(a, "a");
	show(b, "b");
	show(e, "e");

	b = b / a;
	show(b, "b: b/a");

	e = a * b;
	show(e, "e: a*b");
}

void test2()
{
	Complex a(5, 10);
	Complex b(3, 12);
	Complex c(8, 16);
	Complex d(1, 2);
	Complex e(5, 10);
	Complex f(5, 9);
	Complex g(5, 12);

	bool aa, bb, cc, dd, ee, ff, gg, hh, ii, jj, kk, ll, mm;
	
	aa = a < b;	//false
	bb = a < c;	//true
	cc = a >= d;	//true
	dd = a <= c;	 //true
	ee = a != e;	//true
	ff = a != b;		//true because 5 > 3
	gg = a < b;		//false since ff true
	hh = a > g;		//false
	ii = a > e;		//false
	jj = a > c;		//false
	kk = a >= e;	//true ==
	ll = a <= e;	//true ==	
	mm = a < g;	//true <
}