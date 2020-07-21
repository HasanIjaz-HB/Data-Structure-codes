#include "HashTable.h"


template <class HashedObj>
HashTable<HashedObj>::HashTable(const HashedObj & notFound, int size)
	: ITEM_NOT_FOUND(notFound), array(nextPrime(size))
{
	makeEmpty();
}

template <class HashedObj>
int HashTable<HashedObj>::findPos(const HashedObj & x) const
{
	int collisionNum = 0;
	int currentPos = hash(x, array.size());

	while (array[currentPos].info != EMPTY &&
		array[currentPos].element != x)
	{
		currentPos += 2 * ++collisionNum - 1;  // add the difference
		if (currentPos >= array.size())             // perform the mod
			currentPos -= array.size();             // if necessary
	}

	return currentPos;
}

template <class HashedObj>
bool HashTable<HashedObj>::isActive(int currentPos) const
{
	return array[currentPos].info == ACTIVE;
}

template <class HashedObj>
void HashTable<HashedObj>::remove(const HashedObj & x)
{
	int currentPos = findPos(x);
	if (isActive(currentPos))
		array[currentPos].info = DELETED;
}


template <class HashedObj>
const HashedObj & HashTable<HashedObj>::find(const HashedObj & x)
const
{
	int currentPos = findPos(x);
	if (isActive(currentPos))
		return array[currentPos].element;

	return   ITEM_NOT_FOUND;
}

template <class HashedObj>
void HashTable<HashedObj>::insert(const HashedObj & x)
{
	// Insert x as active
	int currentPos = findPos(x);
	if (isActive(currentPos))
		return;
	array[currentPos] = HashEntry(x, ACTIVE);

	// enlarge the hash table if necessary 
	if (++currentSize >= array.size() / 2)
		rehash();
}

template <class HashedObj>
void HashTable<HashedObj>::rehash()
{
	vector<HashEntry> oldArray = array;

	// Create new double-sized, empty table
	array.resize(nextPrime(2 * oldArray.size()));
	for (int j = 0; j < array.size(); j++)
		array[j].info = EMPTY;

	// Copy table over
	currentSize = 0;
	for (int i = 0; i < oldArray.size(); i++)
		if (oldArray[i].info == ACTIVE)
			insert(oldArray[i].element);
}

int nextPrime(int n) {
	if (n % 2 == 0)
		n++;

	for (; !isPrime(n); n += 2)
		;

	return n;
}

bool isPrime(int n) {
	if (n == 2 || n == 3)
		return true;

	if (n == 1 || n % 2 == 0)
		return false;

	for (int i = 3; i * i <= n; i += 2)
		if (n % i == 0)
			return false;

	return true;
}