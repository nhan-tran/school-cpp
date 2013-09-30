
#include "raceAnalyzer.h"

typedef set<string> StrSet; //the typedef within the .h did not carry over to here...  have to redeclare


	//where do you normally put functors? .h .cpp inclass, outside?
//functor for removing riders not in team
struct NotInTeam : public binary_function<Rider, string, bool>
{
	bool operator()(const Rider &rider, string team) const
	{
		bool result = true;		//assume not in team at the start

		if (rider.getTeam().compare(team) == 0)		//team matches
			result = false;

		return result;		
	}
};


//functor for removing riders not in country
struct NotInCountry : public binary_function<Rider, string, bool>
{
	bool operator()(const Rider &rider, string country) const
	{
		bool result = true;		//assume not in country at the start

		if (rider.getCountry().compare(country) == 0)		//country matches
			result = false;

		return result;		
	}
};


struct GetStageTime : public binary_function<Rider, unsigned, RaceAnalyzer::PairResults>
{
	RaceAnalyzer::PairResults operator()( const Rider &rider, unsigned stage) const
	{
		RaceAnalyzer::PairResults aResult;
		unsigned int totSecs;
		Rider::UnIntVector stages = rider.getStageTimes();

		//return the pair for the specfic stage
		if (stage > 0 )
			aResult = make_pair(rider.getStageTimes().at(stage - 1), rider.getName()); 
		else //stage is 0
		{
			//get the sum of all stage times
			totSecs = accumulate(stages.begin(), 
									stages.end(), 0);
			aResult = make_pair(totSecs, rider.getName());
		}

		return aResult;
	}
};

bool SortPairResults(RaceAnalyzer::PairResults lhs, RaceAnalyzer::PairResults rhs)
{
	return lhs.first < rhs.first;
}


struct GetTeamTime : public binary_function<Rider, unsigned, Seconds>
{
	Seconds operator()(const Rider &rider, unsigned stage) const
	{
		//return the seconds for the stage
		return rider.getStageTimes().at(stage - 1);
	}
};


//find best time for a given stage
Seconds SingleStageTime(list<Rider> ridersList, unsigned stage, unsigned numRiders)
{		
	Seconds totalTime;
	vector<Seconds> timesVector;

	transform(ridersList.begin(), ridersList.end(), 
					inserter(timesVector, timesVector.end()),bind2nd(GetTeamTime(), stage));
	//sort
	sort(timesVector.begin(), timesVector.end());
	//sum up the top elements of the vector
	totalTime = accumulate(timesVector.begin(), timesVector.begin() + numRiders, 0);

	return totalTime;
}


//functor class for teamTime() use
class GetTourTime
{
 public:
	 GetTourTime(const list<Rider> &ridersList, unsigned *stage, const unsigned numRiders) :
		 m_riders(ridersList), m_stage(stage), m_numRiders(numRiders) {}
	 void operator()(Seconds &s)
	 {
		//working on this!
		 s = SingleStageTime(m_riders, *m_stage, m_numRiders);
		 *(m_stage) -= 1;
		 //s = 999;
	 }

private:
	list<Rider> m_riders;
	unsigned m_numRiders;
	unsigned *m_stage;
};



RaceAnalyzer::RaceAnalyzer( const string  &stageFilename, const string  &riderFilename )
{
	ifstream iFile(riderFilename);
	ifstream sFile(stageFilename);

	// input stream iterators of Rider types...
	typedef  istream_iterator<Rider> RiderIstreamIterator;
  	
	//associate file with RiderInputstreamIterator
	RiderIstreamIterator iter(iFile);
	//put riders into set of Rider
	copy(iter, RiderIstreamIterator(), inserter(allRiders, allRiders.begin()));

	//put stages into stage vector
	typedef	istream_iterator<double> DoubleIstreamIterator;
	DoubleIstreamIterator d_iter(sFile);
	copy(d_iter, DoubleIstreamIterator(), back_inserter(stageDistances));

}

string RaceAnalyzer::getTeam( const  string  &riderName )  const 
{
	//make temp rider obj with the riderName
	Rider v(riderName, "temp", "temp");
	RiderSetIter found  = allRiders.find(v);
	return (*found).getTeam();
}

string RaceAnalyzer::getCountry( const  string  &riderName )  const 
{
	//make temp rider obj with the riderName
	Rider v(riderName, "temp", "temp");
	RiderSetIter found  = allRiders.find(v);
	return (*found).getCountry();
}



StrSet RaceAnalyzer::riders()  const
{	
	  StrSet  result;

	  //crazy stupid transform expecting the wrong version 5args instead of 4... had to use lambda workaround
	  //http://stackoverflow.com/questions/12915676/how-can-i-avoid-the-compiler-error-stdtransform
	  transform( allRiders.begin(),
				 allRiders.end(),
				 inserter( result, result.end() ),
				 [&](Rider s){ return s.getName();} );

		 //This is the error! Which will error out when building... why???
	  	 // transform( allRiders.begin(),
				 //allRiders.end(),
				 //inserter( result, result.end() ),
				 //riderToName );

	return result;
}

StrSet RaceAnalyzer::teams()  const
{	
	  StrSet  result;

	  //crazy stupid transform expecting the wrong version 5args instead of 4... had to use lambda workaround
	  //http://stackoverflow.com/questions/12915676/how-can-i-avoid-the-compiler-error-stdtransform
	  transform( allRiders.begin(),
				 allRiders.end(),
				 inserter( result, result.end() ),
				 [&](Rider s){ return s.getTeam();} );

	return result;
}

StrSet RaceAnalyzer::countries()  const
{	
	  StrSet  result;

	  //crazy stupid transform expecting the wrong version 5args instead of 4... had to use lambda workaround
	  //http://stackoverflow.com/questions/12915676/how-can-i-avoid-the-compiler-error-stdtransform
	  transform( allRiders.begin(),
				 allRiders.end(),
				 inserter( result, result.end() ),
				 [&](Rider s){ return s.getCountry();} );

	return result;
}


double RaceAnalyzer::calcMPH( Seconds  seconds, unsigned  stage )  const
{
	double mph, miles, hours;

	if (stage != 0)
		miles = stageDistances.at(stage - 1);
	else  //all stages
		miles = accumulate(stageDistances.begin(), stageDistances.end(), 0.0);
	
	hours = seconds / 3600.00;
	mph = miles / hours;

	return mph;
}

RaceAnalyzer::Results RaceAnalyzer::riderResults( unsigned stage,
                        const string  &team,
                        const string  &country )  const
{
	list<Rider> ridersList;		//list for use and algorithm remove_if does not work on sorted containers...
	RaceAnalyzer::PairResults aResult;			//pair of <time in seconds, rider name>
	RaceAnalyzer::Results results;				//list of RaceAnalyzer::PairResults

	copy(allRiders.begin(), allRiders.end(), inserter(ridersList, ridersList.end()));

	//remove if not team
		//remove_if(ridersList.begin(), ridersList.end(), bind2nd(NotInTeam(), team));
			//how do you use remove_if and erase together again...? Found. Read#8 from:
			//http://home.comcast.net/~oit_hoffmanm/cst420/assignments/assign3FAQ.txt
	
	//use list remove
	if (team.length() > 0)
		ridersList.remove_if(bind2nd(NotInTeam(), team));

	//remove if not country
	if (country.length() > 0)
		ridersList.remove_if(bind2nd(NotInCountry(), country));

	//get stage time
	transform(ridersList.begin(), ridersList.end(), 
				inserter(results, results.begin()), bind2nd(GetStageTime(), stage));

	//sort by time
	results.sort(SortPairResults);

	return results;
}





Seconds  RaceAnalyzer::teamTime( const string  &teamName,
                       unsigned       stage,
                       unsigned       numRiders )  const
{
	Seconds totalTime;
	list<Rider> ridersList;
	vector<Seconds> timesVector;

	//vars needed to calc all stage times
	unsigned stageCount = stageDistances.size();
	vector<Seconds> allTimes;
	allTimes.resize(stageDistances.size(),0);


	copy(allRiders.begin(), allRiders.end(), inserter(ridersList, ridersList.end()));

	//limit to specific team, use list remove
	if (teamName.length() > 0)
		ridersList.remove_if(bind2nd(NotInTeam(), teamName));
	
	//get a list of all the times for a stage
	//if stage is > 0 Then transform riderList into a timeList of the stage time
	if (stage > 0)
	{
		totalTime = SingleStageTime(ridersList, stage, numRiders);
	}
	else	//all stages
	{
		//int stage = m_stages.size();
		//create vector<Seconds> timesVector[stage];
		for_each(allTimes.begin(), allTimes.end(), GetTourTime(ridersList, &stageCount, numRiders));
		totalTime = accumulate(allTimes.begin(), allTimes.end(), 0);

		//do a for_each( vec.beg, vec.end, findtimeofstage())

		//function findtimeofstage class (&stage - 1, list of riders, numRiders) as member variables, stage will be passed as a reference, important
			//actual function operator( takes in the vector element of Seconds)
				//does its calculation using the _member variables 
				//sets the element to the result

		//so the foreach will run for stage.size() and each time it runs the stage var is decremented...
		//when finished the vector<Seconds> will have the fastest times for each stage.. then just accumulate...
	}


	return totalTime;

}