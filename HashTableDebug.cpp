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
    ht.remove("dilly");
    ht.remove("solly");
    ht.remove("zilly");
    ht.remove("willy");
    ht.remove("billy");

    //std::optional<size_t> num = ht.get("billy");

        std::cout << std::endl;






   // std::cout << ht << std::endl;
   // if (ht.contains("billy")) {
   //     std::cout << *num << std::endl;
    //}
   // ht.remove("dilly");
   // ht["solly"] = 111;
    std::cout << ht<< std::endl;
    const size_t val = ht.capacity();
    std::cout << val << std::endl;
            std::cout << "Hello, World!" << std::endl;


            return 0;
        }
