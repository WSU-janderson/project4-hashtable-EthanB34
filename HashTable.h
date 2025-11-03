/**Student Name: Ethan Barnes
 *Project 4: Hash Table
 * File Name: HashTable.h
 *
 *This file contains the declarations for the hashTable class, as well as the HashTableBucket class, which implements each
 *individual bucket
 *HashTable variables - numElts, probeOffsets, BucketData
 *HashTableBucket Variables: key, value, type
 */
#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <optional>
#include <string>
#include <utility>
#include <vector>


/* class HashTableBucket -
 * contains the default and parameterized constructors for a single hashtablebucket
 * string key, key to access desired bucket
 * size_t value, value paired with key
 * BucketType type, bucket designator, ESS - empty since start, EAR - empty after removal, NORMAL - key held in bucket
 *
 *
 */
class HashTableBucket {
public:
    enum class BucketType {NORMAL, ESS, EAR};
    std::string key;
    size_t value;
    BucketType type;

    HashTableBucket()
    : key(), value(0), type(BucketType::ESS) {}

    HashTableBucket(std::string  k, size_t v)
        :  key(std::move(k)), value(v), type(BucketType::NORMAL) {}


};
/* class HashTable -
 * contains the definitions for all of the HashTable functions
 * bucketData, vector of hashtablebuckets, probeOffsets, vector of size_t to handle probing sequence
 * numElts - number of key-value pairs held in the table
 *
 */
class HashTable {
public:

    HashTable(size_t initCapacity = 8); // default constructor to create a hashtable with 8 buckets

    // INSERT & REMOVE
    bool insert(std::string key, size_t value);
    bool remove(std::string key);

    //Single pair accessors
    bool contains(const std::string& key) const;
    std::optional<size_t> get(const std::string& key) const;
    size_t& operator[](const std::string& key);

    std::vector<std::string> keys() const; // Vector to hold all used keys

    //O(1) HashTable INFO
    double alpha() const;
    size_t capacity() const;
    size_t size() const;

    void resize(size_t newCapacity); // create new table with doubled size, also regenerate probe offsets, copy all pairs into new table

    friend std::ostream& operator<<(std::ostream& os, const HashTable& hashTable); // print the table to the ostream

private:
    std::vector<HashTableBucket> bucketData;
    std::vector<size_t> probeOffsets;
    size_t numElts;


    void generateProbeOffset(std::size_t capacity);


};
#endif // HASHTABLE_H
