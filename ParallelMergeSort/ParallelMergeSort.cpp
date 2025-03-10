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
    Node* list = new Node();
    int maxItems = 20;      //Maximum number of items = 2^maxItems
    long long total;
    int nAttempts = 10;
    int maxThreadDepth = 0; //Number of threads = 2^threadDepth
    int elementRange = 100;
    int seed = 1337;

    for (int nItems = pow(2, 4); nItems <= pow(2, maxItems); nItems *= 2) {
        for (int threadDepth = 0; threadDepth <= maxThreadDepth; threadDepth++) {
          //  fprintf(fp, "Test started with %d threads and %d elements!\n", threadDepth, nItems);
            total = 0;
            srand(1337);
            for (int i = 0; i < nAttempts; i++) {
                list = generateList(nItems, elementRange);                        //Generate this rounds list
                auto start = std::chrono::high_resolution_clock::now();
                multiThreadMergeSort(&list, nItems, threadDepth);
                auto end = std::chrono::high_resolution_clock::now();
                if (!isSorted) {                                                        //Makeshift "error handling"
                    fprintf(fp, "Error, lists do not match!!!\n"); 
                    printf("Error, lists do not match!!!\n");
                    fclose(fp);
                    list = freeList(list);
                    return; 
                }
            //    fprintf(fp, "attempt = %d\ttime = %lld\n", i + 1, (end - start).count());
                fprintf(fp, "%d,%d,%d,%lld\n", int(pow(2, threadDepth)), nItems, i+1, (end - start).count());
                total += (end - start).count();
                list = freeList(list);                                                  //free for next iteration
            }
            
            fprintf(fp, "%d,%d,Average,%lld\n", int(pow(2, threadDepth)), nItems, total / nAttempts);
        }
    }
    fclose(fp);
    printf("Tests complete!");
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