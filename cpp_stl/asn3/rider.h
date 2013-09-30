
/*
rider.h
Nhan Tran
8/5/13

Class representing one rider. A rider has a name, team, country, and a vector of completed stage times
in the order of entry in the input file which should be the order of the actual stages.
*/

#include <iostream>
#include <string>
#include <set>
#include <sstream>
#include <algorithm>
#include <vector>

using namespace std;




class Rider
{
	friend istream &operator>>(istream &in, Rider &rhs);	

 public:
	 typedef vector<unsigned int> UnIntVector;


	 Rider();
	 Rider(string n, string t, string c);
	 string getName() const;
	 string getTeam() const;
	 string getCountry() const;
	 UnIntVector getStageTimes() const;
	 void insertTime(double d);
	 bool operator<(const Rider &rhs) const;


 private:
	 string m_name;
	 string m_team;
	 string m_country;
	 UnIntVector stageTimes;
};