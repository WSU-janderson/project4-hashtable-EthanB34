/**
 * HashTable.h
 */
#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <optional>
#include <string>
#include <utility>
#include <vector>

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

class HashTable {
public:
    HashTable(size_t initCapacity = 8);

    bool insert(std::string key, size_t value);

    bool remove(std::string key);

    bool contains(const std::string& key) const;

    std::optional<size_t> get(const std::string& key) const;

    size_t& operator[](const std::string& key);

    std::vector<std::string> keys() const;

    double alpha() const;

    size_t capacity() const;
    size_t size() const;
    void resize(size_t newCapacity);

private:
    std::vector<HashTableBucket> bucketData;
    std::vector<size_t> probeOffsets;
    size_t numElts;
    void generateProbeOffset(std::size_t capacity);


};
#endif // HASHTABLE_H
