
//Nhan Tran
//
//implementation of rider.h

#include "rider.h"

Rider::Rider(string n, string t, string c) : m_name(n), m_country(c), m_team(t)
{
}

Rider::Rider()
{
}

bool Rider::operator<(const Rider &rhs) const
{
	return m_name < rhs.m_name;
}

typedef istream_iterator<double> DoubleInIter;

istream &operator>> (istream &in, Rider &rhs)
{
	//read in the name team country
	in >> rhs.m_name >> rhs.m_country  >> rhs.m_team;

	//read in the remaing numbers of stage times
	string inputBuffer;

	getline(in, inputBuffer);
	
	istringstream inStrm(inputBuffer);

	DoubleInIter iter(inStrm);

	rhs.stageTimes.clear();
	copy(iter, DoubleInIter(), back_inserter(rhs.stageTimes));

	return in;
}



string Rider::getName() const
{
	return m_name;
}

string Rider::getTeam() const
{
	return m_team;
}

string Rider::getCountry() const
{
	return m_country;
}

Rider::UnIntVector Rider::getStageTimes() const
{
	return stageTimes;
}