/**
 * HashTable.h
 */
#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <optional>
#include <string>
#include <vector>

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






};
#endif // HASHTABLE_H
