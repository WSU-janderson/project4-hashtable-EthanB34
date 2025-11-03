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
 * Default / parameterized constructor
 * parameters : initCapacity = 8
 * returns: nothing, constructor
 *
 */
HashTable::HashTable(size_t initCapacity)
    : bucketData(initCapacity), numElts(0)
{
    generateProbeOffset(initCapacity);


}
/*
*insert :
* parameters: string key -  the desired key, size_t value - the value to be paired with said key
* returns : true if insert operation successful, false if unsuccessful
* Marks bucket as BucketType NORMAL
 */

bool HashTable::insert(std::string key, size_t value) {
    std::hash<std::string> h;
    size_t bucketHash = h(key) & bucketData.size();
    //PROBE SEQUENCE
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

/* remove-
*
* parameters: string key- key associated with pair that is to be removed and marked EAR
* returns: true if operation succeeds, or false otherwise
 */

bool HashTable::remove(std::string key) {
    const size_t size = bucketData.size();
    if (size == 0) {
        return false;
    }
//PROBE SEQUENCE
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

/* contains -
*
* parameters: string key reference
* returns - true if associated key value pair is in the table, false otherwise
*
 */
bool HashTable::contains(const std::string& key) const {
const std::size_t size = bucketData.size();
    if (size == 0) {
        return false;
    }
    //PROBE SEQUENCE
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

/* get -
*
* parameters - string key reference
* returns, optional<size_t> - returns the value associated with the provided key
*
*
 */
std::optional<size_t> HashTable::get(const std::string& key) const {
    size_t size = bucketData.size();
    std::size_t bucketHash = std::hash<std::string>()(key) % size;

    //PROBE SEQUENCE
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

/* operator [] overload
*
*parameters - string key reference
* returns - size_t& returns a reference to the value with the associated key, allowing for reassignment.
*
 */
size_t& HashTable::operator[](const std::string& key) {
size_t size = bucketData.size();

std:: size_t bucketHash = std::hash<std::string>()(key) % size;

    //PROBE SEQUENCE
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
/* operator << overload -
* parameters- ostream, reference to the hashTable
* returns - ostream& - prints all of the normal key value pairs to the ostream in a neat format.
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
/* keys-
* parameters- none
* returns - a vector of strings of all keys currently in use
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
/* alpha -
*
* parameters - none
* returns - double that is the current load factor of the table or, the ratio of amount of stored pairs /
* size of empty and non empty buckets
 */
double HashTable::alpha() const {
return static_cast<double>(numElts) / bucketData.size();
}
/* capacity -
*
* parameters - none
* returns - size_t  amount of empty and nonempty buckets in the table
 */
size_t HashTable::capacity() const {
return bucketData.size() ;
}
/* size -
*
* parameters - none
* returns - the amount of key value pairs currently held in the table
 */
size_t HashTable::size() const {
return numElts;
}
/* generateProbeOffset
*
* parameters - size_t capacity, the amount of offsets to generate
* returns - void
* each time a new table is created, generate a pseudo random probing sequence.
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
/* resize -
*
* parameters - size_t newCapacity, or double the size of the previous table
* returns - nothing, void
* whenever the load factor exceeds 0.5, double the size of the table to reduce average number of probes in the probe
* sequence
 */
void HashTable::resize(size_t newCapacity) {
    std::vector<HashTableBucket> oldTable = bucketData;

    bucketData.clear();
    bucketData.resize(newCapacity);
    numElts = 0;
    generateProbeOffset(newCapacity);
    for (const HashTableBucket& bucket : oldTable) {
        if (bucket.type == HashTableBucket::BucketType::NORMAL) {
            insert(bucket.key, bucket.value);
        }
    }
}