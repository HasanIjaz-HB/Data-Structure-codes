#include "dictionary.h"
#include "HashTable.h"
#include <iostream>
#include <fstream>
#include <string>
#define SIZE 4096
using namespace std;

int main() 
{
	ifstream in;
	ofstream out;
	string s;
	Dictionary ITEM_NOT_FOUND;
	HashTable<Dictionary> compress(ITEM_NOT_FOUND,SIZE);
	for (int i = 0; i<256; i++) 
	{// the integers from 0 to 255 refer to single characters so they are stored as code (int) and key (char/string) pairs
		s = i;
		compress.insert(Dictionary(i, s)); //this is opp of what we did in compression code
	}
	string fname = "compout.txt";
	in.open(fname.c_str());
	string ofname = "decompout.txt";
	out.open(ofname.c_str());

	int ccode, prevcode, dictidx = 256;// reading integers from file prevcode starts with first string and then keeps the prevcode in case we find a new string we attach the prev one to it and dict idx starts with the value 256 for obv reasons
	in >> prevcode;//read first int in file to prevcode this will refer to first char/string
	string temp;
	temp = compress.find(Dictionary(prevcode)).key;
	out << compress.find(Dictionary(prevcode)).key; //write on the output file the corresponding char/string in dict of the int
	while (in >> ccode)
	{
		 //read the next int this will be our current string
		string tobeadded = compress.find(prevcode).key;
		if (compress.find(ccode).key == ITEM_NOT_FOUND.key) //if doesn't exist in the dict add the first char of prevcode's string to prevcode's string
		{
			tobeadded += tobeadded.at(0);
		}
		else
		{
			tobeadded += compress.find(ccode).key.at(0);//if ccode exists in the dict then find the corresponding string get fc(ccode) = first char and add to prevcode's string
		}
		compress.insert(Dictionary(dictidx, tobeadded));
		dictidx++;
		out << compress.find(ccode).key;//write the corresponding string/char to file
		prevcode = ccode; //make the int of current as previous so that we can add the string referred to prev int incase we don't find the next int in dict and create a new string and store
	}
	out.close();
	in.close();

	return 0;
}