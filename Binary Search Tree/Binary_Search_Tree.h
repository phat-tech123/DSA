#include <iostream>
#include <string>
#include <sstream>
using namespace std;
#define SEPARATOR "#<ab@17943918#@>#"
template<class T>


class BinarySearchTree
{
public:
    class Node;
private:
    Node* root;
public:
    BinarySearchTree() : root(nullptr) {}
    ~BinarySearchTree()
    {
        // You have to delete all Nodes in BinaryTree. However in this task, you can ignore it.
    }

    //Helping function
    // 
    //Question 1
    void add(T value) {
        Node* newnode = new Node(value);
        if (this->root == NULL) {
            this->root = newnode;
        }
        else {
            Node* parent = NULL;
            Node* tmp = this->root;
            while (tmp != NULL) {
                parent = tmp;
                if (value > tmp->value) {
                    tmp = tmp->pRight;
                }
                else {
                    tmp = tmp->pLeft;
                }
            }
            if (value > parent->value) {
                parent->pRight = newnode;
            }
            else {
                parent->pLeft = newnode;
            }
        }
    }

    Node* getSmallest(Node* subroot) {
        if (subroot == NULL) return NULL;
        Node* tmp = subroot;
        while (tmp->pLeft != NULL) {
            tmp = tmp->pLeft;
        }
        return tmp;
    }
    Node* getLargest(Node* subroot) {
        if (subroot == NULL) return NULL;
        Node* tmp = subroot;
        while (tmp->pRight != NULL) {
            tmp = tmp->pRight;
        }
        return tmp;
    }
    Node* findParent(Node* subroot, Node* child) {
        if (child == subroot) return NULL;
        while (subroot->pLeft != child && subroot->pRight != child) {
            if (child->value < subroot->value) {
                subroot = subroot->pLeft;
            }
            else {
                subroot = subroot->pRight;
            }
        }
        return subroot;
    }
    void deleteNode(T value) {
        Node* tmp = this->root;
        while (tmp->value != value) {
            if (value < tmp->value) {
                tmp = tmp->pLeft;
            }
            else {
                tmp = tmp->pRight;
            }
        }
        if (tmp->pLeft == NULL && tmp->pRight == NULL) {
            Node* parent = this->findParent(this->root, tmp);
            if (parent->pLeft == tmp) {
                parent->pLeft = NULL;
            }
            else {
                parent->pRight = NULL;
            }
            delete tmp;
        }
        else {
            if (tmp->pRight != NULL) {
                Node* smallest = this->getSmallest(tmp);
                tmp->value = smallest->value;
                Node* parent = this->findParent(this->root, smallest);
                if (parent->pLeft == smallest) {
                    parent->pLeft = NULL;
                }
                else {
                    parent->pRight = NULL;
                }
                delete smallest;
            }
            else if (tmp->pLeft != NULL) {
                Node* largest = this->getLargest(tmp);
                tmp->value = largest->value;
                Node* parent = this->findParent(this->root, largest);
                if (parent->pLeft == largest) {
                    parent->pLeft = NULL;
                }
                else {
                    parent->pRight = NULL;
                }
                delete largest;
            }
        }
    }

    //

    string inOrderRec(Node* root) {
        stringstream ss;
        if (root != nullptr) {
            ss << inOrderRec(root->pLeft);
            ss << root->value << " ";
            ss << inOrderRec(root->pRight);
        }
        return ss.str();
    }

    string inOrder() {
        return inOrderRec(this->root);
    }

    class Node
    {
    private:
        T value;
        Node* pLeft, * pRight;
        friend class BinarySearchTree<T>;
    public:
        Node(T value) : value(value), pLeft(NULL), pRight(NULL) {}
        ~Node() {}
    };
};
