#pragma once

struct Node {
	int value;
	Node* next = nullptr;
};

Node* insertFirst(Node* list, Node* node);

Node* insertLast(Node* list, Node* node);

bool isSorted(Node* list, int n);

void printList(Node* list);

Node* generateList(int nItems, int elementSize);

Node* freeList(Node* list);