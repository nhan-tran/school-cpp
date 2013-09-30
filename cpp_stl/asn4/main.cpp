/*
Nhan Tran
CST420
Assignment 4 - Anagram finder w/o looping.
*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>
#include <functional>
using namespace std;

typedef set<string> StrSet;
typedef vector<string> StrVect;
typedef StrVect::iterator StrVectIter;

StrSet findAnagrams(string &entry, StrVect dict);
StrVect getDict(const string fileName);

struct IsAnagram : public binary_function<string, string, bool>
{
	bool operator()(string dictWord, string sortedEntry) const
	{
		sort(dictWord.begin(), dictWord.end());
		if (dictWord.compare(sortedEntry) == 0)
			return true;
		else
			return false;
	}
};


int main()
{
	StrVect dict;
	StrSet anagrams;
	string entry, fileName;
	StrVectIter iter;

	cout << "Enter dictionary file name: " ;  //get dictionary file name
	cin >> fileName;
	dict = getDict(fileName);

	cout << "\nEnter 'quit' anytime to quit the program." << endl;

	while (1) 
	{
		cout << "\n\nEnter a word: " ; 	//get user input
		cin >> entry;
	
		if (entry == "quit")
			break;
		else if (find(dict.begin(), dict.end(), entry) == dict.end()) //if entry is not a word in the dict then break
			cout << "  " << entry << " is not a valid word";
		else
		{
			anagrams = findAnagrams(entry, dict);
			if (anagrams.size() > 0) 
			{
				cout << "  Anagrams: " ;
				for_each(anagrams.begin(), anagrams.end(), [] (string s) { cout << s << " ";});				
			}
			else
				cout << "  No anagrams found";
		}
	}
	return 0;
}


StrSet findAnagrams(string &entry, StrVect dict)
{
	StrSet anagrams;
	string sortedEntry = entry;

	sort(sortedEntry.begin(), sortedEntry.end());	//sort into ascending order
	//copy from dict if the dict word sorted value matches entry sorted value 
	copy_if(dict.begin(), dict.end(), inserter(anagrams, anagrams.begin()), bind2nd(IsAnagram(), sortedEntry));
	anagrams.erase(entry);
	return anagrams;
}

StrVect getDict(const string fileName)
{
	StrVect dictionary;
	ifstream iFile(fileName); 	//associate file to stream
	typedef istream_iterator<string> StrIter;
	StrIter iter(iFile);	//associate stream to iterator

	if (iFile.is_open()) 		//copy string from file stream into string vector
		copy(iter, StrIter(), inserter(dictionary, dictionary.begin()));
	else //bad file
	{
		cout << "File not found. " ;
		system("pause");	//press any key to continue...
		exit(1);
	}
	return dictionary;
}
