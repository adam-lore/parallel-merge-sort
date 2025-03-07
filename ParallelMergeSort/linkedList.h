#pragma once

struct Node {
	int value;
	Node* next = nullptr;
};

Node* insertFirst(Node* list, Node* node);

Node* insertLast(Node* list, Node* node);

void printList(Node* list);