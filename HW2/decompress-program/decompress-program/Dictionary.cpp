#include "Dictionary.h"

bool Dictionary::operator == (const Dictionary & rhs) const {
	return code == rhs.code;
}

bool Dictionary::operator != (const Dictionary & rhs) const {
	return code != rhs.code;
}

unsigned hash2(const Dictionary & d, int size) {
	return d.code % size;
}

void Dictionary::operator = (Dictionary & rhs) {
	code = rhs.code;
	key = rhs.key;
}