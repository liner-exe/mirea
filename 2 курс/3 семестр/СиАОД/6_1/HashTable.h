#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <list>
#include <vector>

#include "Specialization.h"

using Bucket = std::list<Specialization>;

class HashTable
{
	std::vector<Bucket> table;
	size_t size;
	size_t capacity;
	const double MAX_LOAD_FACTOR = 0.75;

	unsigned int hashFunction(const std::string& key) const;

	void rehash();
public:
	HashTable(int initialCapacity);

	void insert(const std::string& code, const std::string& university);
	void remove(const std::string& code);
	void search(const std::string& code) const;
	void display() const;
};

#endif //HASHTABLE_H