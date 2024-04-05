#include "Splay_Tree.h"

int main() {
    SplayTree tree;
    int query;
    cin >> query;
    for (int i = 0; i < query; i++) {
        string op;
        int val;
        cin >> op >> val;
        if (op == "insert")
            tree.insert(val);
        else if (op == "search")
            cout << (tree.search(val) ? "found" : "not found") << '\n';
        else if (op == "print")
            tree.printPreorder();
    }
}