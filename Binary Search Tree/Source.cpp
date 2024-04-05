#include"Binary_Search_Tree.h"

int main() {
	BinarySearchTree<int> root;
    root.add(50);
    root.add(30);
    root.add(20);
    root.add(40);
    root.add(70);
    root.add(60);

    printf("Original BST: ");
    cout <<  root.inOrder();

    printf("\n\nDelete a Leaf Node: 20\n");
    root.deleteNode(20);
    printf("Modified BST tree after deleting Leaf Node:\n");
    cout << root.inOrder();

    printf("\n\nDelete Node with single child: 70\n");
    root.deleteNode(70);
    printf("Modified BST tree after deleting single child Node:\n");
    cout <<  root.inOrder();

    printf("\n\nDelete Node with both child: 50\n");
    root.deleteNode(50);
    printf("Modified BST tree after deleting both child Node:\n");
    cout << root.inOrder();
}