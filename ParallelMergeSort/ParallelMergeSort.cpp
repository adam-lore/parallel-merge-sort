// ParallelMergeSort.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdlib.h>
#include "linkedList.h"
#include "mergeSort.h"
#include <thread>
#include <chrono>

void printIfSorted(Node* list, int n) {
    if (isSorted(list, n)) {
        std::cout << "List is sorted :)\n";
    }
    else {
        std::cout << "List is not sorted >:(\n";
    }
}

int main() {
    int n = 10000000;   //Element count.
    int valRange = 100; //Numbers will range from 0 < - > valRange

    srand(time(NULL));

    Node* list = new Node();
    list->value = rand() % (valRange + 1);

    for (int i = 1; i < n; i++) {
        Node* next = new Node();
        next->value = rand() % (valRange + 1);
        list = insertFirst(list, next);
    }

    printIfSorted(list, n);
    //printList(list);
    //list = mergeSort(list, n);
    //printList(list);
    //return(0);
    printf("starting\n");
    auto start = std::chrono::high_resolution_clock::now();

    std::thread t1(multiThreadMergeSort, &list, n, 1);
    t1.join();

    //list = mergeSort(list, 1000);

    auto end = std::chrono::high_resolution_clock::now();

    const std::chrono::duration<double, std::milli> time = end - start;

    printIfSorted(list, n);
    //printList(list);
    std::cout << time.count() << "\n";
}