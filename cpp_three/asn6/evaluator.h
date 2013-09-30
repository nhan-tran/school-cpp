/*
 Assignment	: #6
 Class		: CST 136
 File Name	: evaluator.h
 Date		: 8/14/12
 Author		: Nhan Tran
 Description: Evaluator class is a base class with three derived classes: Postfix Evaluator, PrefexEvaluator, InfixEvaluator.
			  The derived Evaluator classes takes in an expression in the form of a Tokenizer object, evaluates the expression, 
			  and stores in a member m_results variable.
*/


#ifndef EVALUATOR_H
#define EVALUTOR_H

#include "tokenizer.h"
#include <stack>

class Evaluator
{

public:
		enum  Error  {
               missingOperand_,
               invalidOperand_,
               missingOperator_,
               invalidOperator_
             };
	
		Evaluator(const Tokenizer &tok);
		//destructor needed? no
		virtual double result() const = 0;
		double getResult() const { return m_result; }
		void setResult(const double r);
		bool isOperand(const string &tok);
		double convertToOperand(const string &tok);
		bool validateOperator(const string &tok);
		char convertToOperator(const string &tok);
		double compute(char oper, double operand1, double operand2);

private:
		double m_result;

};

class PostfixEvaluator : public Evaluator
{

public:
		PostfixEvaluator(const Tokenizer &tok);
		double result() const;
		double calculate(const Tokenizer &tok);

private:
		double fetch(stack<double> &values);

};

class PrefixEvaluator : public Evaluator
{

public:
		PrefixEvaluator(const Tokenizer &tok);
		double result() const;
		double calculate(const Tokenizer &tok);

private:
		bool firstToken;

};


class InfixEvaluator : public Evaluator
{

public:
		InfixEvaluator(const Tokenizer &tok);
		double result() const;
		double calculate(const Tokenizer &tok);

private:
		bool firstToken;
		double getOperand(const Tokenizer &tok);

};

#endif