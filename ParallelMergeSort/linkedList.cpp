#include "linkedList.h"
#include <iostream>

Node* insertFirst(Node* list, Node* node){
	(*node).next = list;
	return node;
}
Node* generateList(int nItems, int seed, int elementSize) {
	srand(seed); //Temp seed
	Node* list = new Node();
	list->value = rand() % elementSize;
	for (int i = 0; i < nItems - 1; i++) {
		Node* listNode = new Node();
		listNode->value = rand() % elementSize;
		list = insertFirst(list, listNode);
	}
	return list;
}

Node* freeList(Node* list) {
	Node* cursor = list;
	while (cursor) {
		cursor = cursor->next;
		delete list;
		list = cursor;
	}
	return nullptr;
}

Node* insertLast(Node* list, Node* node) {
	Node* current = list;
	while ((*current).next != nullptr) {
		current = (*current).next;
	}
	(*current).next = node;
	return list;
}

bool isSorted(Node* list, int n) {
	int i, previous;
	previous = list->value;

	Node* current = list->next;

	for (i = 1; current != nullptr && i < n; i++) {
		if (current->value < previous) return false;

		previous = current->value;
		current = current->next;
	}

	if (i != n) return false;
	else return true;
}

void printList(Node* list) {
	while (list->next != nullptr) {
		std::cout << list->value << ", ";
		list = list->next;
	}
	std::cout << list->value << "\n";
}