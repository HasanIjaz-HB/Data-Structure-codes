#ifndef DICTIONARY_H_
#define DICTINARY_H_
#include <string>

using namespace std;


class Dictionary {
public:
	Dictionary() : key(""), code(INT_MAX) {}
	Dictionary(string c, int i = 0) : code(i), key(c) {}
	Dictionary(const Dictionary & rhs) : code(rhs.code), key(rhs.key) {}

	bool operator == (const Dictionary & rhs) const;
	bool operator != (const Dictionary & rhs) const;
	void operator = (Dictionary & rhs);
	unsigned code;
	string key;
};

unsigned hashing(const Dictionary & d, int size);


#endif
