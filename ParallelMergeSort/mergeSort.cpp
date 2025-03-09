#include "mergeSort.h"
#include <thread>

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
	if (left != nullptr) {					 //Process left tree
		current->next = left;
	}
	else {
		current->next = right;
	}

	current = head->next; //Store merged list
	delete head;          //Free memory
	return current;
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
	Node* left = mergeSort(list, leftn);
	int rightn = n - leftn;
	Node* right = mergeSort(second, rightn);

	Node* result = mergeList(left, right);
	return result;
}

int test(int n, int m) {
	std::thread subThread(test, 5, m);
	return n + m;
}

void multiThreadMergeSort(Node** list, int n, int depth) {
	if (n < 2) return;

	Node* middle = *list;
	for (int i = 0; i < int(n / 2) - 1; i++) {
		middle = middle->next;
	}

	Node* second = middle->next;
	middle->next = nullptr;

	int leftn = n / 2;
	int rightn = n - leftn;
	Node* left,* right;
	if (depth > 1) {
		left = *list;
		right = second;
		std::thread subThread(multiThreadMergeSort, &left, leftn, depth - 1);
		multiThreadMergeSort(&right, rightn, depth - 1);

		subThread.join();
	}
	else {
		left = mergeSort(*list, leftn);
		right = mergeSort(second, rightn);
	}
	

	*list = mergeList(left, right);
}