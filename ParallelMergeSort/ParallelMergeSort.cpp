// ParallelMergeSort.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _CRT_SECURE_NO_WARNINGS

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
Node* copyList(Node* original, Node* target) {
    Node* head = target;
    while (original != nullptr && target != nullptr) {
        target->value = original->value;
        target = target->next;
        original = original->next;
    }
    return head;
}

void runTests() {
    FILE* fp = fopen("results.txt", "w");
    Node* original = new Node();
    Node* list = new Node();
    int nItems = 10;
    int valRange = 100;
    long long total = 0;
    int nAttempts = 10;
    int numThreads = 1;
    srand(1337); //Random seed decide on value later
    original->value = rand() % valRange;
    list->value = original->value;
    for (nItems = 10; nItems <= 1000000; nItems *= 10) {
        for (int i = 0; i < nItems - 1; i++) {
            Node* listNode = new Node();
            Node* originalNode = new Node();
            listNode->value = rand() % (valRange + 1);
            originalNode->value = listNode->value;
            list = insertFirst(list, listNode);
            original = insertFirst(original, originalNode);
        }
        for (int numThreads = 1; numThreads < 16; numThreads *= 2) {
            fprintf(fp, "Test started with %d threads and %d elements!\n", numThreads, nItems);
            for (int i = 0; i < nAttempts; i++) {
                auto start = std::chrono::high_resolution_clock::now();
                multiThreadMergeSort(&list, nItems, numThreads);
                auto end = std::chrono::high_resolution_clock::now();
                bool verified = isSorted(list, nItems);
                fprintf(fp, "attempt = %d\ttime = %lld\n", i + 1, (end - start).count());
                total += (end - start).count();
                list = copyList(original, list);
            }
            fprintf(fp, "nItems = %d  -> Average time = %lld\n\n", nItems, total / nAttempts);
        }
        
    }
    fclose(fp);

}



int main() {
    int n = 10000000;   //Element count.
    int valRange = 100; //Numbers will range from 0 < - > valRange
    runTests();
    return 0;
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