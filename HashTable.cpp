/**
 * HashTable.cpp
 */
#include "HashTable.h"

#include <algorithm>
#include <ctime>
#include <random>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>


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
            if (alpha() > 0.5) {
                resize(bucketData.size()*2);
            }
            return true;
        }
        if (bucket.type == HashTableBucket::BucketType::NORMAL && bucket.key == key) {
            return false;
        }

    }
return false;
}
//TODO

bool HashTable::remove(std::string key) {
    const size_t cap = bucketData.capacity();
    if (cap == 0) {
        return false;
    }
    std::size_t bucketHash = std::hash<std::string>()(key) % cap;
    for (size_t i = 0; i< cap; i++) {
        size_t currProbeOffset = (i == 0) ? 0 : probeOffsets[i-1];
        size_t index = (bucketHash + currProbeOffset) % cap;

        HashTableBucket& bucket = bucketData[index];
        if (bucket.type == HashTableBucket::BucketType::ESS) {
            return false;
        }
        if (bucket.type == HashTableBucket::BucketType::NORMAL && bucket.key == key) {
            bucket.type = HashTableBucket::BucketType::EAR;
            bucket.key.clear();
            bucket.value = 0;
            numElts--;
            return true;
        }
    }

 return false;
}


bool HashTable::contains(const std::string& key) const {
return false;
}
//TODO
std::optional<size_t> HashTable::get(const std::string& key) const {

}
size_t& HashTable::operator[](const std::string& key) {
std:: size_t bucketHash = std::hash<std::string>()(key) % bucketData.size();
    for (size_t probe = 1; probe < bucketData.size(); probe++) {
        size_t bucketOffset = (bucketHash + probeOffsets[probe]) % bucketData.size();
        HashTableBucket& bucket = bucketData[bucketOffset];
        if (bucket.type == HashTableBucket::BucketType::NORMAL) {
            return bucket.value;
        } else {
            throw std::out_of_range("HashTable::get: Key not found");
        }

        }
    }

std::ostream& operator<<(std::ostream& os, const HashTable& hashTable) {
    os << hashTable.printMe();
    return os;
}
std::string HashTable::printMe() const {
std::ostringstream oss;
    for (std::size_t i = 0; i < bucketData.size(); i++) {
        if (const HashTableBucket& bucket = bucketData[i]; bucket.type == HashTableBucket::BucketType::NORMAL) {
            oss << "Bucket: " << i << " <" << bucket.key << ", " << bucket.value << ">" << "\n";
        }
    }

    return oss.str();
}
std::vector<std::string> HashTable::keys() const {
    std::vector<std::string> result;
    result.reserve(numElts);
    for (std::size_t i = 0; i < bucketData.size(); i++) {
    const HashTableBucket& bucket = bucketData[i];
        if (bucket.type == HashTableBucket::BucketType::NORMAL) {
            result.push_back(bucket.key);
        }
    }

    return result;
}

double HashTable::alpha() const {
return static_cast<double>(numElts) / bucketData.size();
}
size_t HashTable::capacity() const {
return bucketData.size() - numElts;
}

size_t HashTable::size() const {
return numElts;
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
void HashTable::resize(size_t newCapacity) {
    std::vector<HashTableBucket> oldTable = bucketData;

    bucketData.clear();
    bucketData.resize(newCapacity);
    numElts = 0;
    generateProbeOffset(newCapacity);
    for (const auto& bucket : oldTable) {
        if (bucket.type == HashTableBucket::BucketType::NORMAL) {
            insert(bucket.key, bucket.value);
        }
    }
}