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
    generateProbeOffset(initCapacity);


}

bool HashTable::insert(std::string key, size_t value) {
    std::hash<std::string> h;
    size_t bucketHash = h(key) & bucketData.size();
    for (size_t i = 0; i < bucketData.size(); i++) {
        size_t bucketOffset =  (i==0) ? 0 : probeOffsets[i-1];
        size_t currProbeOffset = (bucketHash + bucketOffset) % bucketData.size();

        HashTableBucket& bucket = bucketData[currProbeOffset];

        if (bucket.type == HashTableBucket::BucketType::ESS) {
            bucket.key = key;
            bucket.value = value;
            bucket.type = HashTableBucket::BucketType::NORMAL;
            numElts++;
            return true;
        }
        if (bucket.type == HashTableBucket::BucketType::NORMAL && bucket.key == key) {
            return false;
        }

    }
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
