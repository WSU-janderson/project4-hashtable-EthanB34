[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/7RAFczHS)
# Project 4 - HashTable

Project description can be found [in the repo](Project4_HashTable.pdf)

Place your complexity analysis below.

• insert
```
The time complextiy of inserting into the table is O(1/1-a) where a = number of elements/table size, when alpha reaches
a value greater than 0.5, the table size is doubled, effectivly halving the value of alpha, which keeps the average number of probes
to 2, rather than getting larger based on the number of elements in the table

```
• remove
```
The time complexity for remove is similar to that of insert, 1/1-a for a < 0.5, 2 for a > 0.5, doubling table size removes
unessercery tombstone probes.
```
• contains
```
1/1-a ?
```
• get
```
1/1-a ?

```
• operator[]
```
1/1-a ?


---