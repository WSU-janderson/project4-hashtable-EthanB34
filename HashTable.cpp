/**
 * HashTable.cpp
 */
#include "HashTable.h"
#include <string>
#include <vector>

HashTable::HashTable(size_t initCapacity)
    : bucketData(initCapacity), probeOffsets(initCapacity-1), numElts(0)
{
    for (size_t i = 0; i < probeOffsets.size(); i++)
        probeOffsets[i] = i+1;
}

bool HashTable::insert(std::string key, size_t value) {
return false;
}

bool HashTable::remove(std::string key) {
return false;
}
bool HashTable::contains(const std::string& key) const {
return false;
}

std::optional<size_t> HashTable::get(const std::string& key) const {

}
size_t& HashTable::operator[](const std::string& key) {

}

std::vector<std::string> HashTable::keys() const {
    return{};

}

double HashTable::alpha() const {
return 0.0;
}
size_t HashTable::capacity() const {
return 0;
}

size_t HashTable::size() const {
return 0;
}