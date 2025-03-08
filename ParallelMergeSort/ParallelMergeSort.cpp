// ParallelMergeSort.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdlib.h>
#include "linkedList.h"
#include "mergeSort.h"
#include <thread>
#include <chrono>

int main() {
    Node* list = new Node();
    list->value = 0;

    srand(time(NULL));

    for (int i = 1; i < 1000; i++) {
        Node* next = new Node();
        next->value = rand() % 101;
        list = insertFirst(list, next);
    }

    //printList(list);

    auto start = std::chrono::high_resolution_clock::now();

    std::thread t1(multiThreadMergeSort, &list, 10000, 3);
    t1.join();

    //list = mergeSort(list, 1000);

    auto end = std::chrono::high_resolution_clock::now();

    const std::chrono::duration<double, std::milli> time = end - start;

    //printList(list);
    std::cout << time.count() << "\n";
}