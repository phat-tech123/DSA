#include<iostream>

using namespace std;
class SplayTree {
    struct Node {
        int val;
        Node* pLeft;
        Node* pRight;
        Node* pParent;
        Node(int val = 0, Node* l = nullptr, Node* r = nullptr, Node* par = nullptr) : val(val), pLeft(l), pRight(r), pParent(par) { }
    };
    Node* root;

    // print the tree structure for local testing
    void printBinaryTree(string prefix, const Node* root, bool isLeft, bool hasRightSibling) {
        if (!root && isLeft && hasRightSibling) {
            cout << prefix << "├──\n";
        }
        if (!root) return;
        cout << prefix;
        if (isLeft && hasRightSibling)
            cout << "├──";
        else
            cout << "└──";
        cout << root->val << '\n';
        printBinaryTree(prefix + (isLeft && hasRightSibling ? "|  " : "   "), root->pLeft, true, root->pRight);
        printBinaryTree(prefix + (isLeft && hasRightSibling ? "|  " : "   "), root->pRight, false, root->pRight);
    }

    void printPreorder(Node* p) {
        if (!p) {
            return;
        }
        cout << p->val << ' ';
        printPreorder(p->pLeft);
        printPreorder(p->pRight);
    }
public:
    SplayTree() {
        root = nullptr;
    }
    ~SplayTree() {
        // Ignore deleting all nodes in the tree
    }

    void printBinaryTree() {
        printBinaryTree("", root, false, false);
    }

    void printPreorder() {
        printPreorder(root);
        cout << "\n";
    }

    Node* rotateLeft(Node* subroot) {
        Node* tmp = subroot->pRight;
        subroot->pRight = tmp->pLeft;
        if (tmp->pLeft)
            tmp->pLeft->pParent = subroot;
        tmp->pLeft = subroot;
        tmp->pParent = subroot->pParent;
        if (subroot->pParent) {
            if (subroot->pParent->pLeft == subroot)
                subroot->pParent->pLeft = tmp;
            else
                subroot->pParent->pRight = tmp;
        }
        subroot->pParent = tmp;
        return tmp;
    }

    Node* rotateRight(Node* subroot) {
        Node* tmp = subroot->pLeft;
        subroot->pLeft = tmp->pRight;
        if (tmp->pRight)
            tmp->pRight->pParent = subroot;
        tmp->pRight = subroot;
        tmp->pParent = subroot->pParent;
        if (subroot->pParent) {
            if (subroot->pParent->pLeft == subroot)
                subroot->pParent->pLeft = tmp;
            else
                subroot->pParent->pRight = tmp;
        }
        subroot->pParent = tmp;
        return tmp;
    }

    void splay(Node* p) {
        while (p->pParent != nullptr) {
            Node* parent = p->pParent;
            Node* grandparent = parent->pParent;

            if (grandparent == nullptr) {
                if (p == parent->pLeft)
                    rotateRight(parent);
                else
                    rotateLeft(parent);
            }
            else {
                if (p == parent->pLeft) {
                    if (parent == grandparent->pLeft) {
                        rotateRight(grandparent);
                        rotateRight(parent);
                    }
                    else {
                        rotateRight(parent);
                        rotateLeft(grandparent);
                    }
                }
                else {
                    if (parent == grandparent->pLeft) {
                        rotateLeft(parent);
                        rotateRight(grandparent);
                    }
                    else {
                        rotateLeft(grandparent);
                        rotateLeft(parent);
                    }
                }
            }
        }
        root = p;
    }

    void insert(int val) {
        Node* newnode = new Node(val);
        if (root == nullptr) {
            root = newnode;
            return;
        }
        Node* current = root;
        Node* parent = nullptr;
        while (current != nullptr) {
            parent = current;
            if (val < current->val)
                current = current->pLeft;
            else
                current = current->pRight;
        }

        if (val < parent->val) {
            parent->pLeft = newnode;
            newnode->pParent = parent;
        }
        else {
            parent->pRight = newnode;
            newnode->pParent = parent;
        }

        splay(newnode);
    }

    bool search(int val) {
        Node* tmp = this->root;
        Node* lastaccess = NULL;
        while (tmp) {
            if (tmp->val == val) {
                this->splay(tmp);
                return true;
            }
            lastaccess = tmp;
            if (val < tmp->val) {
                tmp = tmp->pLeft;
            }
            else {
                tmp = tmp->pRight;
            }
        }
        if (lastaccess) {
            this->splay(lastaccess);
        }
        return false;
    }

    Node* remove(int val) {
        //invalid
        if (this->root == NULL) return NULL;
        if (!search(val)) return NULL;

        //initialize
        Node* tree1 = this->root->pLeft;
        Node* tree2 = this->root->pRight;
        Node* dlt = this->root;
        dlt->pLeft = NULL;
        dlt->pRight = NULL;
        if(tree1) tree1->pParent = NULL;
        if (tree2) tree2->pParent = NULL;

        //cases
        if (tree1 == NULL) this->root = tree2;
        else {
            Node* tmp = tree1;
            while (tmp->pRight) {
                tmp = tmp->pRight;
            }
            this->root = tree1;
            this->splay(tmp);
            this->root->pRight = tree2;
            if (tree2) tree2->pParent = this->root;
        }
        dlt->pLeft = nullptr;
        dlt->pRight = nullptr;
        dlt->pParent = nullptr;
        return dlt; 
    }
};