/*
 Assignment	: #6
 Class		: CST 136
 File Name	: evaluator.cpp
 Date		: 8/14/12
 Author		: Nhan Tran
 Description: Implementation for Evaluator class and derived classes: Postfix Evaluator, PrefexEvaluator, InfixEvaluator.
*/

#include "evaluator.h"
#include <stack>
#include <stdlib.h>
#include <iostream>

Evaluator::Evaluator(const Tokenizer &tok)
{
}

void Evaluator::setResult(const double r)
{
	m_result = r;
}


bool Evaluator::isOperand(const string &tok)
{
	char c;
	bool v = false;
	c = tok[0];	//assign first letter of tok into c

	//if the first char is 0-9 ascii values 48-57 then it is a number and operand
	if (c >= 48 && c <=57)
		v = true;

	return v; 
}

double Evaluator::convertToOperand(const string &tok)
{
	double v;
	const char *token = 0;

	token = tok.data();
	v = atof(token);  

	return v;
}

bool Evaluator::validateOperator(const string &tok)
{
	char c;
	bool v = false;
	c = tok[0];	//assign first letter of tok into c

	//if the first char is 0-9 ascii values 48-57 then it is a number and operand
	if (c == '+' || c == '-' || c == '*' || c == '/')
		v = true;
	else
		throw invalidOperator_;

	return v;
}

char Evaluator::convertToOperator(const string &tok)
{
	return tok[0];
}

double Evaluator::compute(char oper, double operand1, double operand2)
{
	double outcome;

	if (oper == '+')
		outcome = operand1 + operand2;
	else if (oper == '-')
		outcome = operand1 - operand2;
	else if (oper == '*')
		outcome = operand1 * operand2;
	else if (oper == '/')
		outcome = operand1 / operand2;
	else	//should never get here but if it does throw exception
		throw (invalidOperator_);

	return outcome;
}



/////////////////////////////////////////
//PostfixEvaluator
/////////////////////////////////////////

PostfixEvaluator::PostfixEvaluator(const Tokenizer &tok) : Evaluator(tok)
{
	//run calculate immediately and set the m_result
	setResult(calculate(tok));
}

double PostfixEvaluator::calculate(const Tokenizer &tok)
{
	stack<double> values;
	
	while (!tok.done())
	{
		//get next token string
		string token = tok.nextToken();
		
		//if token is an operand then convert the string to a double and push
		//it onto the operand stack, afterwards go straight to next token
		if (isOperand(token))
		{
			values.push(convertToOperand(token));
			continue;
		}
		else if (validateOperator(token)) //if not operand then check if operator
		{
			//if token is operator then fetch last to values in stack - do the math
			//then return the result to the top of the stack
			double value2 = fetch(values);	//rhs 
			double value1 = fetch(values);	//lhs because this number came first so it was deeper in the stack

			values.push(compute(convertToOperator(token), value1, value2));
		}
		//it is an invalid operand. hard to see how it could get here because validateOperator() will throw exception if not valid
		else
			throw invalidOperand_;
	}
	
	//when no more tokens then the top of the stack is the final result
	//return the top of the stack
	return fetch(values);
}

double PostfixEvaluator::result() const
{
	return getResult();
}

double PostfixEvaluator::fetch(stack<double> &values)
{
	if (values.empty())			//if the stack is empty then the operand needed is missing
		throw missingOperand_;

	double operand = values.top();	//assing the top value on stack
	
	values.pop();					//pop the top value

	return operand;
}



/////////////////////////////////////////
//PrefixEvaluator
/////////////////////////////////////////

PrefixEvaluator::PrefixEvaluator(const Tokenizer &tok) : Evaluator(tok), firstToken(true)
{
	//run calculate immediately and set the m_result
	setResult(calculate(tok));
}

double PrefixEvaluator::result() const
{
	return getResult();
}

double PrefixEvaluator::calculate(const Tokenizer &tok)
{
	if (tok.done())		//if Tokenizer string is out of tokens then expression is missing values
		throw missingOperand_;
	
	//check if first token is operator
	string token = tok.nextToken();

	if (firstToken && validateOperator(token))
		firstToken = false;

	if (isOperand(token))				//if token is operand then return the operand value
		return convertToOperand(token);
	else if (validateOperator(token))	//if it is an operator then add the next two values, since prefix is <operator> <operand> <operand>
	{
		char op = convertToOperator(token);
		double value1 = calculate(tok);		//recursive calls to calculate()
		double value2 = calculate(tok);
	
		return compute(op, value1, value2);
	}
	else
		throw invalidOperator_;
}



/////////////////////////////////////////
//InfixEvaluator
/////////////////////////////////////////

InfixEvaluator::InfixEvaluator(const Tokenizer &tok) : Evaluator(tok), firstToken(true)
{
	//run calculate immediately and set the m_result
	setResult(calculate(tok));
}

double InfixEvaluator::result() const
{
	return getResult();
}

double InfixEvaluator::calculate(const Tokenizer &tok)
{
	double value1;
	double value2;
	char op;
	string token;
	double result = 0;

	value1 = getOperand(tok);
	
	if (tok.done()) 
		throw missingOperator_;	//nothing after the value1
	else
	{
		token = tok.nextToken();
		while (!token.empty())
		{
			if (validateOperator(token))
			{
				op = convertToOperator(token);
				value2 = getOperand(tok);	//gets operand or possibly a left bracket
				
				result = compute(op, value1, value2);
			
				if (!tok.done())	// if tok not done
				{
					token = tok.nextToken();	//grabs next token
					if (token == ")")
						return result;
					value1 = result;
				}
				else
					token.clear();	//token is done. will break while loop
			}
			else
			{
				throw invalidOperator_;
			}
		}
	}

	return result;
}

double InfixEvaluator::getOperand(const Tokenizer &tok)
{
	double operand;
	
	if (tok.done())
		throw missingOperand_;

	string token = tok.nextToken();

	if ( token == "(" )
	{
		operand = calculate(tok);	//if open paren step back into calculate again
	}
	else
	{
		if (isOperand(token))
			operand = convertToOperand(token);
		else
			throw invalidOperand_;	//not a ( or and operand 
	}

	return operand;
}