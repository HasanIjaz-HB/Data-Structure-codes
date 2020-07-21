#include "Dictionary.h"

bool Dictionary::operator == (const Dictionary & rhs) const {
	return key == rhs.key;
}

bool Dictionary::operator != (const Dictionary & rhs) const {
	return key != rhs.key;
}

unsigned hashing(const Dictionary & d, int size) {
	if (d.key.length() == 1)
		return unsigned char(d.key.at(0));
	else
		return 256;
}

void Dictionary::operator = (Dictionary & rhs) {
	code = rhs.code;
	key = rhs.key;
}