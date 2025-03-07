#include "linkedList.h"
#include <iostream>

Node* insertFirst(Node* list, Node* node){
	(*node).next = list;
	return node;
}

Node* insertLast(Node* list, Node* node) {
	Node* current = list;
	while ((*current).next != nullptr) {
		current = (*current).next;
	}
	(*current).next = node;
	return list;
}

void printList(Node* list) {
	while (list->next != nullptr) {
		std::cout << list->value << ", ";
		list = list->next;
	}
	std::cout << list->value << "\n";
}