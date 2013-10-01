/*
CIS162 Assingment 1: Shopping Calculator (nt_shoppingCalc.cpp)
Description: A calculator to keep a total of all items bought on a shopping trip.
Author: Nhan Tran
Date: 9/30/2011
Sources:http://www.cplusplus.com/reference/iostream/ios/clear/
		http://www.cplusplus.com/reference/iostream/istream/get/
		http://spot.pcc.edu/~cgoble/CS161/avi/userdialog.wmv
Notes:	cin.get grabs chars up to the delimiter while cin.ignore ignores up to and INCLUDING delimiter.
		DON'T USE cin >> together with getline in a program.
*/

#include <iostream>                 //Required if your program does any I/O
#include <string>					//Required for string type
#include <iomanip>					//Needed for setprecision

using namespace std;

double getPrice();

int main()
{
	double price, total;
	char itemName[101];
	char reply[101];
	bool quit;

	cout.setf(ios::fixed, ios::floatfield);
	cout.setf(ios::showpoint);
	cout.precision(2);

	quit = false;
	total = 0;
	price = 0;
	cout << "Nhan's Shopping Cart Calculator" << endl;
	cout << "-------------------------------" << endl;
	while (!quit)
	{	
		cout << endl;
		cout << "Add an item to the cart? (y/n): ";
		cin >> reply;
		cin.ignore(101, '\n');
		switch(reply[0])
		{
			case 'Y':
			case 'y':
				cout << "Enter the item name: ";
				cin.get(itemName, 101, '\n');
				while(itemName[0] == 0)		//error if user pressed entered then [0] is null
				{
					cin.clear();
					cin.ignore(100, '\n');
					cout << "Please enter a valid item name: ";
					cin.get(itemName, 101, '\n');
				}
				cin.ignore(101, '\n');
				
				price = getPrice();
				while (price < 0)
				{
					cout << "Price cannot be negative." << endl;
					price = getPrice();
				}
				
				total += price;
				cout << "You have added " << itemName << " for $" << price << "." << endl;
				cout << "The total of your cart is now $" << total << "." << endl; 
				break;

			case 'N':
			case 'n':
				cout << "Your final checkout total is $" << total << "." << endl;
				cout << "Press 'Enter' to exit... ";
				cin.get(reply, 1, ' ');
				quit = true;
				break;
			default:
				cout << "Invalid input. Please enter 'y' or 'n'." << endl;
		}
	}	
	return 0;
}

double getPrice()
{
	double priceInput;
	cout << "Enter the item price (xx.xx): ";
	cin >> priceInput;
	while(!cin)	//while cin is ill/sick/false/wrong/bad/invalid...
	{
		cin.clear();	//first clears the error
		cin.ignore(101, '\n');	//removes all the bad input
		cout << "Invalid input. Please enter item price again: ";
		cin >> priceInput;			//get the price again
	}
	cin.ignore(101, '\n');		//throw away any invalid input including newline eg: 33 abcd
	
	return priceInput;
}