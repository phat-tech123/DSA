#include<iostream>
#include<string>
#include<queue>
using namespace std;

template<class K, class V>
class BinaryTree
{
public:
    class Node;

private:
    Node* root;

public:
    BinaryTree() : root(nullptr) {}
    ~BinaryTree()
    {
        // You have to delete all Nodes in BinaryTree. However in this task, you can ignore it.
    }

    class Node
    {
    private:
        K key;
        V value;
        Node* pLeft, * pRight;
        friend class BinaryTree<K, V>;

    public:
        Node(K key, V value) : key(key), value(value), pLeft(NULL), pRight(NULL) {}
        ~Node() {}
    };

    void addNode(string posFromRoot, K key, V value)
    {
        if (posFromRoot == "")
        {
            this->root = new Node(key, value);
            return;
        }

        Node* walker = this->root;
        int l = posFromRoot.length();
        for (int i = 0; i < l - 1; i++)
        {
            if (!walker)
                return;
            if (posFromRoot[i] == 'L')
                walker = walker->pLeft;
            if (posFromRoot[i] == 'R')
                walker = walker->pRight;
        }
        if (posFromRoot[l - 1] == 'L')
            walker->pLeft = new Node(key, value);
        if (posFromRoot[l - 1] == 'R')
            walker->pRight = new Node(key, value);
    }

    // STUDENT ANSWER BEGIN
    //
    void BFS()
    {
        if (!this->root) return;
        queue<Node*> q;
        q.push(root);
        while (!q.empty()) {
            cout << q.front()->value << " ";
            if (q.front()->pLeft) {
                q.push(q.front()->pLeft);
            }
            if (q.front()->pRight) {
                q.push(q.front()->pRight);
            }
            q.pop();
        }
    }



    //
    // STUDENT ANSWER END
};

class BTNode {
public:
    int val;
    BTNode* left;
    BTNode* right;
    BTNode() {
        this->val = 0;
        this->left = NULL;
        this->right = NULL;
    }
    BTNode(int val) {
        this->val = val;
        this->left = NULL;
        this->right = NULL;
    }
    BTNode(int val, BTNode*& left, BTNode*& right) {
        this->val = val;
        this->left = left;
        this->right = right;
    }

    static BTNode* BFS(BTNode* root, int value) {
        if (root->val == value) return root;
        queue<BTNode*> q;
        q.push(root);
        while (!q.empty()) {
            if (q.front()->left) {
                if (q.front()->left->val == value) 
                    return q.front()->left;
                else 
                    q.push(q.front()->left);
            }
            if (q.front()->right) {
                if (q.front()->right->val == value)
                    return q.front()->right;
                else
                    q.push(q.front()->right);
            }
            q.pop();
        }
        return NULL;
    }
    void DFS(BTNode* root) {

    }

    static BTNode* createTree(int* arr, int* end, int *value) {
        const _int64 size = end - arr;
        BTNode* root = NULL;
        if (value != NULL) {
            BTNode** valueAddress = new BTNode * [size];
            root = new BTNode(value[0]);
            valueAddress[0] = root;

            for (int i = 1; (arr + i) != end; i++) {
                BTNode* parrent = valueAddress[arr[i]];
                if (parrent->left == NULL) {
                    parrent->left = new BTNode(value[i]);
                    valueAddress[i] = parrent->left;
                }
                else {
                    parrent->right = new BTNode(value[i]);
                    valueAddress[i] = parrent->right;
                }
            }
            return root;
        }
        root = new BTNode(0);
        for(int i=1; i< size; i++){
            BTNode* parent = BFS(root, arr[i]);
            if (parent->left == NULL) {
                parent->left = new BTNode(i);
            }
            else {
                parent->right = new BTNode(i);
            }
        }
        return root;
    }
};
// STUDENT ANSWER BEGIN
    //
void longestPathSumHelper(BTNode* root, int len, int& maxlen,
    int sum, int& maxSum) {
    if (!root) {
        if (len > maxlen) {
            maxlen = len;
            maxSum = sum;
        }
        else if (maxlen == len && maxSum < sum)
            maxSum = sum;
        return;
    }
    longestPathSumHelper(root->left, len + 1, maxlen, sum + root->val, maxSum);
    longestPathSumHelper(root->right, len + 1, maxlen, sum + root->val, maxSum);
}
int longestPathSum(BTNode* root) {
    int maxlen = 0;
    int maxSum = -1;
    longestPathSumHelper(root, 0, maxlen, 0, maxSum);
    return maxSum;
}

int lowestAncestor(BTNode* root, int a, int b) {
    int anc = root->val;
}

int sumDigitPath(BTNode* root) {
    int sum = 0;
}
//
// STUDENT ANSWER END