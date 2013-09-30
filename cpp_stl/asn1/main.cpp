
/*
 Assignment	 : #1
 Class		 : CST420
 Date		 : 7/5/13
 Author		 : Nhan Tran
 Description : A program to find all the anagrams of a user input word. A dictionary file is required for 
			   finding anagrams.
*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

vector<string> getDict(const string fileName);
vector<string> findAnagrams(string &s, vector<string> &dict);

int main()
{
	vector<string> dict;
	vector<string> anagrams;
	vector<string>::iterator iter;
	string entry;
	string fileName;
	char c;

	//get dictionary file name
	cout << "Enter dicitonary file name: " ;
	cin >> fileName;
	dict = getDict(fileName);
	
	cout << "\nEnter 'quit' anytime to quit the program." << endl;
	//get user input
	while (1) 
	{
		cout << "\n\nEnter a word: " ;
		cin >> entry;
	
		if (entry == "quit")
			break;
		else
		{
			anagrams = findAnagrams(entry, dict);
			if (anagrams.size() > 0) {
				cout << "  Anagrams: " ;
				for (iter = anagrams.begin(); iter != anagrams.end(); iter++)
				cout << *iter << ' ';
			}
			else
				cout << "  No anagrams found";
		}
	}
	return 0;
}


//Desc: takes in a string and string vector, finds anagrams of the string within the string vector
vector<string> findAnagrams(string &s, vector<string> &dict)
{
	vector<string> anagrams;
	int wLength;
	string sCopy;
	string word;
	vector<string>::iterator dictIter;
	bool isAnagram;
	int pos;
	char c;

	wLength = s.length();	//get length of the user string

	//create search dict where only words of the same length is stored
	for (dictIter = dict.begin(); dictIter != dict.end(); dictIter++)
	{
		word = *dictIter;
		isAnagram = false;	//set flag to false
		if (word.length() == wLength)	//if same length
		{
			//store string in temp stack or another string
			sCopy = s;

			//check to see if same word
			if (word.compare(sCopy) != 0)	//if not the same then it is possibly an anagram				
				isAnagram = true;			//turn on flag to enter while loop check

			while (!sCopy.empty() && isAnagram)
			{
				c = sCopy.back();
				pos = word.find_first_of(sCopy.back(),0);
				if ( pos >= 0)
				{
					//the char was found, so remove the char from the word and sCopy
					sCopy.pop_back();	//pop_back removes the last char, C++11 standard
					word.erase(pos, 1);
				}
				else  //the char was not found
					isAnagram = false;
			}

			//after exiting the while loop and isAnagram is still true then add to anagrams result vector
			if (isAnagram)
				anagrams.push_back(*dictIter);
		}
	}
	
	return anagrams;
}


//Desc: takes in a string filename and returns a string vector of the strings in the file
vector<string> getDict(string fileName)
{
	fstream dictionaryFile (fileName);
	vector<string> dict;
	string word;
	string c;
	if (dictionaryFile.is_open())
	{
		while (dictionaryFile.good())
		{			
			dictionaryFile >> word;
			dict.push_back(word);
		}
	}
	else   //bad file
	{
		cout << "File cannot be opened. Press any key then Enter to quit.";
		cin >> c;
		exit(1) ;
	}

	return dict;
}