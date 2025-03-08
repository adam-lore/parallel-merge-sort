#include "mergeSort.h"
#include "assert.h"

Node* mergeList_old(Node* left, Node* right) {
	if (left == nullptr) return right;
	if (right == nullptr) return left;

	if (left->value < right->value) {
		left->next = mergeList_old(left->next, right);
		return left;
	}
	else {
		right->next = mergeList_old(left, right->next);
		return right;
	}
}
Node* mergeList(Node* left, Node* right) {
	Node* current =  new Node();				  //itterator
	Node* head = current;						  //Head of new list, dummyhead
	current->next = nullptr;					  //If both lists are null, null will be returned.

	while (left != nullptr && right != nullptr) { //Go through both lists
		if (left->value < right->value) { 
			current->next = left;				  //Left smaller, next element is left
			current = current->next;			  //move current
			left = left->next;					  //left points at first unhandled element in left
		}
		else {									  //Same for right
			current->next = right;
			current = right;
			right = right->next;
		}
	}
	//only one of the lists have elements, they are sorted, just fill into new list
	while (left != nullptr) {					 //Process left tree
		current->next = left;
		current = left;
		left = left->next;
	}
	while (right != nullptr) {
		current->next = right;
		current = right;
		right = right->next;
	}
	return head->next;
}

Node* mergeSort(Node* list, int n) {
	if (n < 2) return list;

	Node* middle = list;
	for (int i = 0; i < int(n / 2) - 1; i++) {
		middle = middle->next;
	}

	Node* second = middle->next;
	middle->next = nullptr;

	int leftn = n / 2;
	Node* left = mergeSort(list, int(n / 2));
	int rightn = n - leftn;
	Node* right = mergeSort(second, n - int(n / 2));

	return mergeList(left, right);
}