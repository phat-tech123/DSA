#pragma once
#include <iostream>
#include <math.h>
#include <queue>
#include<stack>
using namespace std;
#define SEPARATOR "#<ab@17943918#@>#"

enum BalanceValue
{
    LH = -1,
    EH = 0,
    RH = 1
};

void printNSpace(int n)
{
    for (int i = 0; i < n - 1; i++)
        cout << " ";
}

void printInteger(int& n)
{
    cout << n << " ";
}

template<class T>
class AVLTree
{
public:
    class Node;
private:
    Node* root;
protected:
    int getHeightRec(Node* node)
    {
        if (node == NULL)
            return 0;
        int lh = this->getHeightRec(node->pLeft);
        int rh = this->getHeightRec(node->pRight);
        return (lh > rh ? lh : rh) + 1;
    }
public:
    AVLTree() : root(nullptr) {}
    ~AVLTree() {}
    int getHeight()
    {
        return this->getHeightRec(this->root);
    }
    void printTreeStructure()
    {
        int height = this->getHeight();
        if (this->root == NULL)
        {
            cout << "NULL\n";
            return;
        }
        queue<Node*> q;
        q.push(root);
        Node* temp;
        int count = 0;
        int maxNode = 1;
        int level = 0;
        int space = pow(2, height);
        printNSpace(space / 2);
        while (!q.empty())
        {
            temp = q.front();
            q.pop();
            if (temp == NULL)
            {
                cout << " ";
                q.push(NULL);
                q.push(NULL);
            }
            else
            {
                cout << temp->data;
                q.push(temp->pLeft);
                q.push(temp->pRight);
            }
            printNSpace(space);
            count++;
            if (count == maxNode)
            {
                cout << endl;
                count = 0;
                maxNode *= 2;
                level++;
                space /= 2;
                printNSpace(space / 2);
            }
            if (level == height)
                return;
        }
    }

    int getBalance(Node* subroot) {
        if (!subroot) return 0;
        return getHeightRec(subroot->pLeft) - getHeightRec(subroot->pRight);
    }

    Node* rotateLeft(Node* subroot)
    {
        //TODO: Rotate and return new root after rotate
        Node* tmp = subroot->pRight;
        subroot->pRight = tmp->pLeft;
        tmp->pLeft = subroot;
        return tmp;
    }
    Node* rotateRight(Node* subroot)
    {
        //TODO: Rotate and return new root after rotate
        Node* tmp = subroot->pLeft;
        subroot->pLeft = tmp->pRight;
        tmp->pRight = subroot;
        return tmp;
    }

    Node* findParent(Node* subroot, Node* child) {
        if (child == subroot) return NULL;
        while (subroot->pLeft != child && subroot->pRight != child) {
            if (child->data < subroot->data) {
                subroot = subroot->pLeft;
            }
            else {
                subroot = subroot->pRight;
            }
        }
        return subroot;
    }

    void insert(const T& value) {
        //insert
        Node* newnode = new Node(value);
        if (this->root == NULL) {
            this->root = newnode;
            return;
        }
        Node* current = this->root;
        Node* parent = NULL;
        while (current != NULL) {
            parent = current;
            if (value > current->data)
                current = current->pRight;
            else
                current = current->pLeft;
        }

        if (value < parent->data) {
            parent->pLeft = newnode;
        }
        else {
            parent->pRight = newnode;
        }

        //except case
        if (parent == this->root) return;

        //create grandParent
        Node* grandParent = findParent(this->root, parent);
        int balanceIdxgrandParent = 0;
        int balanceIdxParent = 0;
        Node* initParent = parent;
        Node* initGrandParent = grandParent;
        while (parent != this->root) {
            balanceIdxgrandParent = this->getHeightRec(grandParent->pLeft) - this->getHeightRec(grandParent->pRight);
            balanceIdxParent = this->getHeightRec(parent->pLeft) - this->getHeightRec(parent->pRight);
            if (balanceIdxgrandParent > 1 || balanceIdxgrandParent < -1) break;
            
            parent = findParent(this->root, parent);
            grandParent = findParent(this->root, grandParent);
        }
        if (balanceIdxgrandParent <= 1 && balanceIdxgrandParent >= -1) {
            parent = initParent;
            grandParent = initGrandParent;
        }
        

        //rotate according the cases after insert
        Node* parentOfGrandParent = findParent(this->root, grandParent);
        //
        if (balanceIdxParent >= 1 && balanceIdxgrandParent > 1) {
            //LoL 
            if (parentOfGrandParent == NULL) {
                this->root = rotateRight(grandParent);
            }
            else {
                if (parentOfGrandParent->pLeft == grandParent) {
                    parentOfGrandParent->pLeft = rotateRight(grandParent);
                }
                else if (parentOfGrandParent->pRight == grandParent) {
                    parentOfGrandParent->pRight = rotateRight(grandParent);
                }
            }
        }
        else if (balanceIdxParent <= -1 && balanceIdxgrandParent > 1) {
            //RoL
            grandParent->pLeft = rotateLeft(parent);
            if (parentOfGrandParent == NULL) {
                this->root = rotateRight(grandParent);
            }
            else {
                if (parentOfGrandParent->pLeft == grandParent) {
                    parentOfGrandParent->pLeft = rotateRight(grandParent);
                }
                else if (parentOfGrandParent->pRight == grandParent) {
                    parentOfGrandParent->pRight = rotateRight(grandParent);
                }
            }
        }
        else if (balanceIdxParent <= -1 && balanceIdxgrandParent < -1) {
            //RoR
            if (parentOfGrandParent == NULL) {
                this->root = rotateLeft(grandParent);
            }
            else {
                if (parentOfGrandParent->pLeft == grandParent) {
                    parentOfGrandParent->pLeft = rotateLeft(grandParent);
                }
                else if (parentOfGrandParent->pRight == grandParent) {
                    parentOfGrandParent->pRight = rotateLeft(grandParent);
                } 
            }
        }
        else if (balanceIdxParent >= 1 && balanceIdxgrandParent < -1) {
            //LoR
            grandParent->pRight = rotateRight(parent);
            if (parentOfGrandParent == NULL) {
                this->root = rotateLeft(grandParent);
            }
            else {
                if (parentOfGrandParent->pLeft == grandParent) {
                    parentOfGrandParent->pLeft = rotateLeft(grandParent);
                }
                else if (parentOfGrandParent->pRight == grandParent) {
                    parentOfGrandParent->pRight = rotateLeft(grandParent);
                }
            }
        }
    }

   
    
    void printInorderHelping(Node* subroot) {
        if (subroot == NULL) return;
        printInorderHelping(subroot->pLeft);
        cout << subroot->data << " ";
        prinOderHelping(subroot->pRight);
    }
    void printInorder() {
        //TODO
        this->printInorderHelping(this->root);
    }
    bool search(const T& value) {
        //TODO
        Node* tmp = this->root;
        while (tmp != NULL) {
            if (tmp->data == value)
                return true;
            else {
                if (value < tmp->data)
                    tmp = tmp->pLeft;
                else
                    tmp = tmp->pRight;
            }
        }
        return false;
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
    
    void remove(const T& value) {
        //value is not in AVL tree
        if (!search(value)) return;

        //remove
        Node* tmp = this->root;
        while (tmp->data != value) {
            if (value < tmp->data) {
                tmp = tmp->pLeft;
            }
            else {
                tmp = tmp->pRight;
            }
        }
        Node* parent = NULL;
        if (tmp->pLeft == NULL && tmp->pRight == NULL) {
            //delete leaf node
            Node* parentOfleaf = this->findParent(this->root, tmp);
            if (parentOfleaf->pLeft == tmp) {
                parentOfleaf->pLeft = NULL;
            }
            else {
                parentOfleaf->pRight = NULL;
            }
            parent = parentOfleaf;
            delete tmp;
        }
        else {
            if (tmp->pLeft != NULL) {
                Node* largest = this->getLargest(tmp->pLeft);
                Node* parentofLargest = this->findParent(this->root, largest);
                tmp->data = largest->data;
                if (parentofLargest->pLeft == largest) {
                    parentofLargest->pLeft = NULL;
                }
                else {
                    parentofLargest->pRight = NULL;
                }
                parent = parentofLargest;
                delete largest;
            }
            else if (tmp->pRight != NULL) {
                Node* smallest = this->getSmallest(tmp->pRight); 
                tmp->data = smallest->data;
                Node* parentofSmallest = this->findParent(this->root, smallest);
                if (parentofSmallest->pLeft == smallest) {
                    parentofSmallest->pLeft = NULL;
                }
                else {
                    parentofSmallest->pRight = NULL;
                }
                parent = parentofSmallest;
                delete smallest;
            }
        }   
        //fix here
        int balanceIdxParent = 0;
        if (parent) {
            balanceIdxParent = this->getHeightRec(parent->pLeft) - this->getHeightRec(parent->pRight);
        }
        while (parent != NULL) {
            if (parent != NULL) {
                balanceIdxParent = this->getHeightRec(parent->pLeft) - this->getHeightRec(parent->pRight);
            }
            if (balanceIdxParent > 1 || balanceIdxParent < -1) break;

            parent = this->findParent(this->root, parent);
        }
        if (balanceIdxParent <= 1 && balanceIdxParent >= -1) {
            return;
        }
        Node* child = NULL;
        Node* childLeft = parent->pLeft;
        Node* childRight = parent->pRight;
        int balanceIdxChildRight = 0, balanceIdxChildLeft = 0, balanceIdxChild = 0;
        
        
        if (childLeft == NULL) {
            child = childRight;
            balanceIdxChild = this->getHeightRec(child->pLeft) - this->getHeightRec(child->pRight);
        }
        else if (childRight == NULL) {
            child = childLeft;
            balanceIdxChild = this->getHeightRec(child->pLeft) - this->getHeightRec(child->pRight);
        }
        else {
            balanceIdxChildLeft = this->getHeightRec(childLeft->pLeft) - this->getHeightRec(childLeft->pRight);
            balanceIdxChildRight = this->getHeightRec(childRight->pLeft) - this->getHeightRec(childRight->pRight);
            if (balanceIdxChildLeft != 0) {
                child = childLeft;
                balanceIdxChild = balanceIdxChildLeft;
            }
            else {
                child = childRight;
                balanceIdxChild = balanceIdxChildRight;
            }
        }
        
        //balance
        Node* grandParent = this->findParent(this->root, parent);
        if (balanceIdxChild >= 0 && balanceIdxParent > 1) {
            //LoL 
            if (grandParent == NULL) {
                this->root = rotateRight(parent);
            }
            else {
                if (grandParent->pLeft == parent) {
                    grandParent->pLeft = rotateRight(parent);
                }
                else if (grandParent->pRight == parent) {
                    grandParent->pRight = rotateRight(parent);
                }
            }
        }
        else if (balanceIdxChild <= -1 && balanceIdxParent > 1) {
            //RoL
            parent->pLeft = rotateLeft(child);
            if (grandParent == NULL) {
                this->root = rotateRight(parent);
            }
            else {
                if (grandParent->pLeft == parent) {
                    grandParent->pLeft = rotateRight(parent);
                }
                else if (grandParent->pRight == parent) {
                    grandParent->pRight = rotateRight(parent);
                }
            }
        }
        else if (balanceIdxChild <= 0 && balanceIdxParent < -1) {
            //RoR
            if (grandParent == NULL) {
                this->root = rotateLeft(parent);
            }
            else {
                if (grandParent->pLeft == parent) {
                    grandParent->pLeft = rotateLeft(parent);
                }
                else if (grandParent->pRight == parent) {
                    grandParent->pRight = rotateLeft(parent);
                }
            }
        }
        else if (balanceIdxChild >= 1 && balanceIdxParent < -1) {
            //LoR
            parent->pRight = rotateRight(child);
            if (grandParent == NULL) {
                this->root = rotateLeft(parent);
            }
            else {
                if (grandParent->pLeft == parent) {
                    grandParent->pLeft = rotateLeft(parent);
                }
                else if (grandParent->pRight == parent) {
                    grandParent->pRight = rotateLeft(parent);
                }
            }
        }
    }
    class Node
    {
    private:
        T data;
        Node* pLeft, * pRight;
        BalanceValue balance;
        friend class AVLTree<T>;

    public:
        Node(T value) : data(value), pLeft(NULL), pRight(NULL), balance(EH) {}
        ~Node() {}
    };
};

template<typename T>
void prinOderHelping(AVLTree<T>) {

}