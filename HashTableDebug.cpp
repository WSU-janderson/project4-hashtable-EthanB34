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


ht.remove("zilly");
   ht.insert("zilly", 111);
    std::cout <<  ht << std::endl;
    
if (ht.contains("zilly") == true) {
    std::cout << "zilly is contained" << std::endl;
}
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
