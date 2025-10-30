/**
 * HashTable.cpp
 */
#include "HashTable.h"

#include <algorithm>
#include <ctime>
#include <random>
#include <string>
#include <vector>



HashTable::HashTable(size_t initCapacity)
    : bucketData(initCapacity), numElts(0)
{
    srand(time(nullptr));
    generateProbeOffset(initCapacity);


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
void HashTable::generateProbeOffset(size_t capacity) {
    probeOffsets.clear();
    for (size_t i = 1; i < capacity; i++) {
        probeOffsets.push_back(i);
    }

    std::random_device randGen;
    std::mt19937 gen(randGen());

    std::shuffle(probeOffsets.begin(), probeOffsets.end(), gen);





}
