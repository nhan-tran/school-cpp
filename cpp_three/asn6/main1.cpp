
/*
 Assignment	: #6
 Class		: CST 136
 File Name	: 
 Date		: 8/14/12
 Author		: Nhan Tran
 Description: Test Evaluator class
*/


#include "evaluator.h"
#include <iostream>
#include <string>

using namespace std;

string getInput()
{
    string  input;

    cout  <<  endl  <<  "Enter expression (blank line exits): ";

    getline( cin, input );

	if ( input.empty() ) exit (1);

	return input;
}



int test1(string expression)
{
  try 
  {
	Tokenizer tok(expression);
	
	cout << "\nEvaluating postfix expression: " << endl;

	PostfixEvaluator pfe1(tok);

	cout << "\tPostfixEvaluator = " << pfe1.result() << endl;
  }

  catch( Evaluator::Error  err )
  {
    const char  *errStr[]  =  {"missing operand", "invalid operand",  "missing operator", "invalid operator"
                              };
    cout  <<  "\tPostfix Error: "  <<  errStr[err]  <<  endl;
  }

	return 0;
}

int test2(string expression)
{
  try 
  {
	//Tokenizer tok(expression);
	
	cout << "\nEvaluating prefix expression: " << endl;

	PrefixEvaluator pfe1(expression);

	cout << "\tPrefixEvaluator = " << pfe1.result() << endl;

  }

  catch( Evaluator::Error  err )
  {
    const char  *errStr[]  =  {"missing operand", "invalid operand",  "missing operator", "invalid operator"
                              };
    cout  <<  "\tPrefix Error: "  <<  errStr[err]  <<  endl;
  }

	return 0;
}

int test3(string expression)
{
  try 
  {
	//Tokenizer tok(expression);
	
	cout << "\nEvaluating prefix expression: " << endl;

	InfixEvaluator ife1(expression);

	cout << "\tInfixEvaluator = " << ife1.result() << endl;

  }

  catch( Evaluator::Error  err )
  {
    const char  *errStr[]  =  {"missing operand", "invalid operand",  "missing operator", "invalid operator"
                              };
    cout  <<  "\tInfix Error: "  <<  errStr[err]  <<  endl;
  }

	return 0;
}


int dotests()
{
	while( true)
	{
		string expression;	
		expression = getInput();

		test1(expression);	//postfix
		test2(expression);	//prefix
		test3(expression);	//infix
	}
	return 0;
}

int main()
{
	dotests();

	#ifdef _WIN32
	if (_CrtDumpMemoryLeaks()) {
		cout << "Memory leaks!" << endl;
		}
	#endif
}
