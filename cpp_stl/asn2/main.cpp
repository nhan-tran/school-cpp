/*
 Assignment	 : #2
 Class		 : CST420
 Date		 : 7/21/13
 Author		 : Nhan Tran
 Description : A program to index every unique word found in a document text file while not including the words found in a skip text file.
*/

#include "word.h"
#include <string>
#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;


//strips all the badChars from the str
void stripChars(string &str)
{
	string badChars = ".,\";:?'()!{}[]\\/";
	int pos; 

	//http://www.cplusplus.com/reference/string/string/find_first_of/
	while (str.find_first_of(badChars) != string::npos)
	{
		pos = str.find_first_of(badChars);
		str.erase(pos, 1);
	}
	
	//to lowercase using transform
	transform(str.begin(), str.end(), str.begin(), tolower);
}


//splits a string into tokens stores in it a word object and returning a vector of word objects
vector<Word> tokenizer(string aLine, const int &pageCount, const int &lineCount)
{
	vector<Word> w;

	//http://stackoverflow.com/questions/236129/splitting-a-string-in-c
	istringstream iss(aLine);

	while (! iss.eof())
	{
		string token;
		iss >> token;

		//strip invalid characters and lowercase the token
		stripChars(token);

		//add to vector
		string index = to_string(pageCount) + "." + to_string(lineCount);
		Word aWord(token, index);
		w.push_back(aWord);
		//cout << endl;
		//cout << aWord.getValue() << endl;
		//cout << "   " + aWord.getIndex();
	}

	return w;
}

fstream openFile(string fileName)
{
	char c;
	fstream docFile (fileName);
	if (docFile.is_open())
		return docFile;
	else   //bad file
	{
		cout << "\nFile cannot be opened. Press any key then Enter to quit." << endl;
		cin >> c;
		exit(1) ;
	}
}

//for each word index the word
void indexWord(Word aWord, set<Word> &docWords, const set<Word> &skipWords)
{	
	set<Word>::iterator wordIter = docWords.find(aWord);	//iterator to that word in docWords
	set<Word>::iterator skipCheck = skipWords.find(aWord);
	
	//check if in ignore list
	if (skipCheck != skipWords.end())	//word was found in skip file exit the function
		return;

	if (wordIter != docWords.end()) //if iter does not point to set end then it was found
	{
		//check if new index string already exists in the found word's index string
		if (wordIter->getIndex().find(aWord.getIndex()) == string::npos)	
		{
			//append the new index string
			aWord.setIndex(wordIter->getIndex() + ", " + aWord.getIndex());						
			docWords.erase(wordIter);	//erase old
			docWords.insert(aWord);		//put back the word with new indexes
		}
	}
	else							//word was not found so just insert for indexing
		docWords.insert(aWord);
}


//Desc: takes in a string filename and returns a string vector of the strings in the file
set<Word> indexer(fstream docFile, const set<Word> &skipWords)
{

	set<Word> docWords;
	set<Word>::iterator wordIter;	
	string aLine;
	vector<Word> lineWords;
	vector<Word>::iterator lineWordIter;
	int pageCount = 1, lineCount = 1;

	while (docFile.good())
		{			
			getline(docFile, aLine);	//get one line from the file
			
			if (aLine == "<newpage>")
			{
				pageCount++;
				lineCount = 1;
			}
			else if (aLine == "") // the line is blank
			{
				lineCount++;
			}
			else                 // the line is not blank
			{
				lineWords = tokenizer(aLine, pageCount, lineCount);

				for (lineWordIter = lineWords.begin(); lineWordIter != lineWords.end(); lineWordIter++)
					indexWord(*lineWordIter, docWords, skipWords);					

				lineCount++;
			}
		}
	return docWords;
}

set<Word> getSkipFile(fstream skipFile)
{
	set<Word> skipWords;
	string skip;
	while (skipFile.good())
	{
		skipFile >> skip;		
		//to lowercase using transform
		transform(skip.begin(), skip.end(), skip.begin(), tolower);

		Word aWord(skip, "");
		skipWords.insert(aWord);
	}

	return skipWords;
}


int main()
{
	typedef set<Word>	wordSet;
	string docFileName;
	string skipFileName;
	wordSet myWords;
	wordSet skipWords;
	wordSet::iterator wordIter;
	char c;

	cout << "Enter document file name: ";
	cin >> docFileName;

	cout << "\nEnter skip file name: ";
	cin >> skipFileName;
	
	skipWords = getSkipFile(openFile(skipFileName));
	myWords = indexer(openFile(docFileName), skipWords);
	
	cout << endl << "Index" << endl;
	cout << "-----" << endl;
	for (wordIter = myWords.begin(); wordIter != myWords.end(); wordIter++)
		cout << *wordIter;

	cout << "\nPress any key then Enter to quit.";
	cin >> c;

	return 0;
}