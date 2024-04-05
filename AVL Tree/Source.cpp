#include"AVL_Tree.h"

int main() {
	AVLTree<int> avl;
	int arr[] = { 20,10,40,5,7,42,2,6,15 };
	for (int i = 0; i < 9; i++) {
		avl.insert(arr[i]);
	}
	avl.printTreeStructure();
}