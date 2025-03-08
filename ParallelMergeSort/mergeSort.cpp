#include "mergeSort.h"
#include <thread>

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
	Node* left = mergeSort(list, leftn);
	int rightn = n - leftn;
	Node* right = mergeSort(second, rightn);

	return mergeList(left, right);
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