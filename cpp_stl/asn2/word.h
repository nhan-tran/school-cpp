//nt_cst420_asn2 word.h
//class representing a word and index

#ifndef WORD_H
#define WORD_H

#include <iostream>

using namespace std;

class Word
{

public:
	friend ostream &operator<< (ostream &out, const Word &rhs);
	
	Word(string, string);
	bool operator<(const Word  &rhs) const;
	bool Word::operator<(string someValue) const;
	string getValue() const;
	string getIndex() const;
	void setIndex(string indexes);

private:
	string m_val;
	string m_index;
	
};

#endif
