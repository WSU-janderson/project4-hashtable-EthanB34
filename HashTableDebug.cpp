/**
 * HashTableDebug.cpp
 *
 * Write your tests in this file
 */
#include <iostream>

#include "HashTable.h"

int main() {
    HashTable ht;
    ht.insert("dilly", 999);
    ht.insert("solly", 999);
    ht.insert("zilly", 999);
    ht.insert("willy", 999);
    ht.insert("billy", 989);

    std::optional<size_t> num = ht.get("billy");

        std::cout << std::endl;






    std::cout << ht << std::endl;
    if (ht.contains("billy")) {
        std::cout << *num << std::endl;
    }
    ht.remove("dilly");
    std::cout << ht<< std::endl;
            std::cout << "Hello, World!" << std::endl;
            return 0;
        }
