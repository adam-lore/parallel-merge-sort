#include "mergeSort.h"

Node* mergeList(Node* left, Node* right) {
	if (left == nullptr) return right;
	if (right == nullptr) return left;

	if (left->value < right->value) {
		left->next = mergeList(left->next, right);
		return left;
	}
	else {
		right->next = mergeList(left, right->next);
		return right;
	}
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