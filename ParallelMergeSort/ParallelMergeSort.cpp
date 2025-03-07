// ParallelMergeSort.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdlib.h>
#include "linkedList.h"
#include "mergeSort.h"

int main() {
    Node* list = new Node();
    list->value = 0;

    for (int i = 1; i < 20; i++) {
        Node* next = new Node();
        next->value = rand() % 101;
        list = insertFirst(list, next);
    }

    printList(list);

    list = mergeSort(list, 20);

    printList(list);
}