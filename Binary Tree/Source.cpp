#include "Binary-Tree.h"

int main() {
	int arr[] = { -1,0,1,0,1,4,5,3,7,3 };
	int value[] = { 6,12,23,20,20,20,3,9,13,15 };
	BTNode* root = BTNode::createTree(arr, arr + sizeof(arr) / sizeof(int), value);
	cout << longestPathSum(root);
}