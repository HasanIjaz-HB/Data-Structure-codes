#include "dictionary.h"
#include "HashTable.h"
#include <iostream>
#include <fstream>
#include <string>
#define SIZE 4096
using namespace std;


void compressionalgo(HashTable<Dictionary> & table, string data) {
	ofstream out;
	string fileName = "compout.txt";
	int minlen = 2, dictidx = 256;
	out.open(fileName.c_str());
	Dictionary temp, ITEM_NOT_FOUND;
	//looking at strings except for single characters so minlen=2 and dictidx for new codes start from 256 as 0 to 255 is for single char
	while (data.length() >= minlen) {		
		temp = Dictionary(data.substr(0, minlen), dictidx);
		if (table.find(temp)==ITEM_NOT_FOUND) {//if the string doesn't exist in hashtable
			table.insert(temp);		// add the new string to dictidx of the hashtable
			out << table.find(Dictionary(data.substr(0, minlen - 1))).code << " "; //write the code of previous prefix or prev string already in table  and a space bw every integer
			data = data.substr(minlen - 1); //delete the string that is coded
			minlen = 2;//reset the length again if added so that it starts with two characters which are not in table
			dictidx++;//increment idx of dict
		}
		else
			minlen++;
	}
	if (data.length()>0)//if single character left in the end write the code and put an extra space after the last integer
		out << table.find(Dictionary(data)).code<<" ";
	out.close();
}

int main() {
	ifstream in;
	ofstream out;
	string s;
	Dictionary ITEM_NOT_FOUND;

	HashTable<Dictionary> compressDict(ITEM_NOT_FOUND,SIZE); // fill the first 256 entries inside dict with 0 to 255 as code for single characters
	for (int i = 0; i<256; i++) {
		s = i;//puts char referred to ascii value of i in s
		compressDict.insert(Dictionary(s, i));//storing key(char) and code in dict
	}
	string filedata;
	string fileName = "compin.txt";
	in.open(fileName.c_str());
	char temp;
	while (!in.eof()) { //read the entire file into a string or make an array of string in the entire file and then pass it to compression function
		in.get(temp);
		filedata += temp;
	}
	filedata= filedata.substr(0, filedata.length() - 1);

	compressionalgo(compressDict, filedata);

	in.close();
	return 0;
}