//nt_cst420_asn2 word.h implementation

#include "word.h"
#include <string>

Word::Word(string aWord, string index) :
	m_val(aWord),
	m_index(index)
{
}

string Word::getValue() const
{
	return m_val;
}

string Word::getIndex() const
{
	return m_index;
}

void Word::setIndex(string newIndex)
{
	m_index = newIndex;
}

bool Word::operator<(const Word &rhs) const
{
	string x,y;
	x = getValue();
	y = rhs.getValue();

	if (x.compare(y) < 0)
		return true;
	else
		return false;
}

ostream& operator<<(ostream& out, const Word &aWord)
{
	out << aWord.getValue() << endl << "  " << aWord.getIndex() << endl;
	return out;
}