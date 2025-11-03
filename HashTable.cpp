/** Student Name: Ethan Barnes
* Project 4: Hash Table
 * File Name: HashTable.cpp
 *
 *This file implements the hash table class, its declarations are stored in HashTable.h
 *
 *Functions:
 *insert - The first insert always ends up in the first bucket, then after that the pseudo random probing sequence is used,
 to mitigate clustering, and once the table reaches a load factor of greater than 0.5, or for a default table of size 8
 when it reaches 5 elements, the table size is doubled and thus the average number of probes remains a constant after every
 *subsequent insert
 *
 *remove-Traverses the table in search of a normal pair that matches the provided key, and erases the key value pair from the
 *table, and marks it Empty After Remove
 *
 *contains - traverses the table in search of a normal pair that matches the provided key, but returns true or false value.
 *
 *get -  traverses the table in search of a normal pair that matches the provided key, and returns that value.
 *
 *operator[] overload -  similar to get, but returns a reference allowing for value assigment
 *
 *operator << overload - Prints all of the key value pairs in the following format "Bucket: 9 <bobby, 999>
 *
 * Variables : numElts - number of key, value pairs currently held in the table
 */
#include "HashTable.h"

#include <algorithm>
#include <ctime>
#include <random>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>


/*
 *
 *
 *
 */
HashTable::HashTable(size_t initCapacity)
    : bucketData(initCapacity), numElts(0)
{
    generateProbeOffset(initCapacity);


}
/*
*
*
*
 */
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

/*
*
*
*
 */
bool HashTable::remove(std::string key) {
    const size_t size = bucketData.size();
    if (size == 0) {
        return false;
    }
    std::size_t bucketHash = std::hash<std::string>()(key) % size;
    for (size_t i = 0; i< size; i++) {
        size_t bucketOffset =   (i==0) ? 0 : probeOffsets[i];
        size_t currProbeOffset = (bucketHash + bucketOffset) % size;

        HashTableBucket& bucket = bucketData[currProbeOffset];

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

/*
*
*
*
 */
bool HashTable::contains(const std::string& key) const {
const std::size_t size = bucketData.size();
    if (size == 0) {
        return false;
    }
    const size_t bucketHash = std::hash<std::string>()(key) % size;
    for (size_t i = 0; i < size; i++) {
        size_t currProbeOffset = probeOffsets[i];
        size_t bucketOffset = (bucketHash + currProbeOffset) %size;

        const HashTableBucket& bucket = bucketData[currProbeOffset];
if (bucket.type == HashTableBucket::BucketType::ESS) {
    return false;
}
        if (bucket.type == HashTableBucket::BucketType::NORMAL && bucket.key == key) {
            return true;
        }

    }
    return false;
}

/*
*
*
*
 */
std::optional<size_t> HashTable::get(const std::string& key) const {
    size_t size = bucketData.size();
    std::size_t bucketHash = std::hash<std::string>()(key) % size;
    for (size_t i = 0; i < size; i++) {
        size_t currProbeOffset = probeOffsets[i];
        size_t bucketOffset = (bucketHash + currProbeOffset) % size;

        const HashTableBucket& bucket = bucketData[bucketOffset];


        if (bucket.type == HashTableBucket::BucketType::NORMAL && bucket.key == key) {
            return(bucket.value);
        }

    }
    return std::nullopt;




}
/*
*
*
*
 */
size_t& HashTable::operator[](const std::string& key) {
size_t size = bucketData.size();
std:: size_t bucketHash = std::hash<std::string>()(key) % size;
    for (size_t i = 0; i < size; i++) {
        size_t bucketOffset = probeOffsets[i];
        size_t currProbeOffset = (bucketHash + bucketOffset) % size;
        HashTableBucket& bucket = bucketData[bucketOffset];
        if (bucket.type == HashTableBucket::BucketType::NORMAL) {
            return bucket.value;
        } else {
            throw std::out_of_range("HashTable::get: Key not found");
        }

        }
    }
/*
*
*
*
 */
std::ostream& operator<<(std::ostream& os, const HashTable& hashTable) {
    for (std::size_t i = 0; i < hashTable.bucketData.size(); i++) {
        if (const HashTableBucket& bucket = hashTable.bucketData[i]; bucket.type == HashTableBucket::BucketType::NORMAL) {
            os << "Bucket: " << i << " <" << bucket.key << ", " << bucket.value << ">" << "\n";
        }
    }
    return os;
}
/*
*
*
*
 */
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
/*
*
*
*
 */
double HashTable::alpha() const {
return static_cast<double>(numElts) / bucketData.size();
}
/*
*
*
*
 */
size_t HashTable::capacity() const {
return bucketData.size() ;
}
/*
*
*
*
 */
size_t HashTable::size() const {
return numElts;
}
/*
*
*
*
 */
void HashTable::generateProbeOffset(size_t capacity) {
    probeOffsets.clear();
    for (size_t i = 1; i < capacity; i++) {
        probeOffsets.push_back(i);
    }

    std::random_device randGen;
    std::mt19937 gen(randGen());

    std::shuffle(probeOffsets.begin(), probeOffsets.end(), gen);


}
/*
*
*
*
 */
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