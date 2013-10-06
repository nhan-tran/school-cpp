/*
nt_lab3_main.cpp
Lab 3 - Memory Managment
Author: Nhan Tran
Date: 11/30/12
Desc: Memory replacement simulator that tests memory replacment policies FIFO, LRU, and OPT on
the user defined number of frames. Program will read from input file with the page info and test
the data on all three policies then report back the number of page faults per each policy.

Sources:
http://courses.cs.vt.edu/csonline/OS/Lessons/VirtualMemory/index.html  Virtual memory overview
http://www.csci.csusb.edu/dick/samples/stl.html#The C++ Standard Template Library
http://www.youtube.com/watch?v=ju1k-FZs4co LRU
http://www.youtube.com/watch?v=GUL2txPndHs OPT
*/


#include <stdlib.h>
#include <list>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct frame
{
	int pid;
	int pref;
	bool opt_exist;
	int opt_distance;
};

//clear input stream
void clearInput()
{
	std::cin.clear() ; // to be safe, clear error flags which may be set
	std::cin.ignore( 255, '\n' );
}


//reset input file to the begining
void rewindFile(ifstream &in_file)
{
	in_file.clear();
	in_file.seekg(0, ios::beg);
}

/*
checkFrame()
Returns true if page already exist in list, false otherwise
FIFO and OPT use option 0
LRU uses option 1:
if a page exists it will be moved to the back of the list since it is the most recently used
this results in the top of the list always being the least recently used.
*/
bool checkFrame(frame &page, list<frame> &pmem, int opt)
{
	bool exist = false;
	list<frame>::iterator pm;

	//go through pmem to see if frame is already loaded
 	for(pm = pmem.begin(); pm != pmem.end(); ++pm)
 	{
		if (pm->pid == page.pid && pm->pref == page.pref)
		{
			//cout << pm->pid << " " << pm->pref << "Exists!" << endl;
			
			if (opt == 1 )	//for LRU
			{
				pmem.erase(pm);			//erase the current list position of the frame
				pmem.push_back(page);	//move the 'same' new frame to back of the list
			}
			exist = true;
			break;
		}
	}

	return exist;
}

int fifo(int f_size, ifstream * inputFile)
{
	list<frame> pmem;
	int pfault = 0;
	frame new_page;

	while (!inputFile->eof())	//while not end of file
	{
		(*inputFile) >> new_page.pid;		//get pid and page reference
		(*inputFile) >> new_page.pref;

		if (!checkFrame(new_page, pmem, 0))	//checkFrame false, pid/pref doesn't exist in pmem
		{
			pfault += 1;				//increment page fault counter
			
			if (pmem.size() < f_size)	//pmem is not full	
				pmem.push_back(new_page);	//add new frame to back
			else	
			{
				pmem.pop_front();			//pop the first frame FIFO
				pmem.push_back(new_page);	//add new frame to back				
			}
		}
	}

	////Show frames currently in pmem
	//cout << "\nFIFO\n" ;
	//list<frame>::iterator pm;
 //	for(pm = pmem.begin(); pm != pmem.end(); ++pm)
	//	cout << pm->pid << " " << pm->pref << endl;	

	return pfault;
}



//Uses the same list strategy as fifo but when a page already exist in physical memory then move the list item to the back of the list
//the top of the list will always be the 'least' frequently used, so that will be the one that is replaced
int lru(int f_size, ifstream * inputFile)
{
	list<frame> pmem;
	int pfault = 0;
	frame new_page;

	while (!inputFile->eof())	//while not end of file
	{
		(*inputFile) >> new_page.pid;		//get pid and page reference
		(*inputFile) >> new_page.pref;

		//if the page doesn't exist in pmem then add it to the back of the list
		//if it does exist then checkFrame() moves the existing page in the list to the back
		if (!checkFrame(new_page, pmem, 1))	//checkFrame false, pid/pref doesn't exist in pmem
		{
			pfault += 1;				//increment page fault counter
			
			if (pmem.size() < f_size)	//pmem is not full	
				pmem.push_back(new_page);	//add new frame to back
			else	
			{
				//pop the first frame. checkFrame() ensures the first frame is the least recently used
				pmem.pop_front();
				pmem.push_back(new_page);	//add new frame to back, indicating	
			}
		}
	}

	//list<frame>::iterator pm;
	////go through pmem
	//cout << "\nLRU\n" ;
 //	for(pm = pmem.begin(); pm != pmem.end(); ++pm)
	//	cout << pm->pid << " " << pm->pref << endl;	

	return pfault;
}

void optReplacement(list<frame> &inputList, list<frame> &pmem, frame &new_page)
{
	list<frame>::iterator pm;
	list<frame>::iterator il;	//iterator for inputList
	int i;
	int d = 0;	//distance tracker
	bool removed = false;
	char ch;

	//go through pmem to see if frame is already loaded
	//clear all opt flags in pmem
 	for(pm = pmem.begin(); pm != pmem.end(); ++pm)
 	{
		pm->opt_exist = false;
		pm->opt_distance = 0;
	}

	//for every frame
		//check every item on the list if/till it exist
		//remember how far it is away	
	for(pm = pmem.begin(); pm != pmem.end(); ++pm)
 	{
		i = 1;
		for(il = inputList.begin(); il != inputList.end(); ++il)
		{
			if (pm->pid == il->pid && pm->pref == il->pref)
			{
				pm->opt_exist = true;
				pm->opt_distance = i;
				break;
			}
			++i;
		}
	}

	//for every frame
	//if there are opt_exist false frames (meaning they will not show up again later)
		//then remove the first one because that one has been in the longest, FIFO
	//else all frames are opt_exist true (meaning they all will show up sometime later)
		//then remove the one with the longest distance
	for(pm = pmem.begin(); pm != pmem.end(); ++pm)
	{
		if (pm->opt_exist == false)
		{
			pmem.erase(pm);			//erase the current frame
			pmem.push_back(new_page);	//move the new frame to back of the list
			removed = true;
			break;
		}

		//remember the longest distance
		if (pm->opt_distance > d)
			d = pm->opt_distance;
	}

	if (!removed)
	{
		for(pm = pmem.begin(); pm != pmem.end(); ++pm)
		{
			if (pm->opt_distance == d)
			{
				pmem.erase(pm);			//erase the current frame
				pmem.push_back(new_page);	//move the new frame to back of the list
				removed = true;
				break;
			}
		}

		//should never enter this block since the for loop should always set removed to true
		if (!removed) //removed is still not true, nothing was removed from the for loop, impossible...
		{
			cout << "error in optRemove(): nothing was removed" << endl;
			cin >> ch;
			exit(EXIT_FAILURE);
		}
	}
}


//OPT replacement
int opt(int f_size, ifstream * inputFile)
{
	list<frame> pmem;
	list<frame> inputList;
	int pfault = 0;
	frame new_page;

	//setup inputList for the OPT replacement to 'look ahead'
	while (!inputFile->eof())	//while not end of file
	{
		(*inputFile) >> new_page.pid;		//get pid and page reference
		(*inputFile) >> new_page.pref;
		inputList.push_back(new_page);
	}

	while (!inputList.empty())
	{
		new_page = inputList.front();	//grab front of inputList
		inputList.pop_front();			//pop the front

		//if page doesn't exist in pmem and pmem is full then do OPT replacement policy to determine which frame to replace
		//if pmem not full then push page to bottom of list, this maintains FIFO of the list, required by OPT
		
		if (!checkFrame(new_page, pmem, 0))	//checkFrame false: pid/pref doesn't exist in pmem
		{
			pfault += 1;				//increment page fault counter
			
			if (pmem.size() < f_size)	//pmem is not full	
				pmem.push_back(new_page);	//add new frame to back
			else	
			{
				//find which to remove?
				optReplacement(inputList, pmem, new_page);
			}
		}	
	}

	//list<frame>::iterator pm;
	////go through pmem
	//cout << "\nOPT\n" ;
 //	for(pm = pmem.begin(); pm != pmem.end(); ++pm)
	//	cout << pm->pid << " " << pm->pref << endl;	

	return pfault;
}


int main()
{
	int f_size;
	ifstream in_file;
	int fifo_pfault, lru_pfault, opt_pfault;
	string fname;
	char ch;

	do {
		in_file.clear();
		cout << "Enter filename: "; 
		cin >> fname;
		in_file.open(fname);
		clearInput();
	} while (!in_file.good());

	do {
		cout << "\nEnter number of frames (3-300): "; 
		cin >> f_size;
		clearInput();
	} while (f_size < 3 || f_size > 300);

	cout << "\nGathering results for FIFO, LRU, and OPT policies . . . " << endl << endl;
		
	fifo_pfault = fifo(f_size, &in_file);
	rewindFile(in_file);	//rewind the input file back to begining
	
	lru_pfault = lru(f_size, &in_file);
	rewindFile(in_file);	//rewind the input file back to begining

	opt_pfault = opt(f_size, &in_file);

	cout << "\nNumber of frames: " << f_size << endl;
	cout << "\nPage faults" << endl;
	cout << "-----------" << endl;
	cout << "FIFO : " << fifo_pfault << endl;
	cout << "LRU  : " << lru_pfault << endl;
	cout << "OPT  : " << opt_pfault << endl;

	cout << "\nPress q or any key then enter to quit: " ;
	cin >> ch;

	return 0;
}
