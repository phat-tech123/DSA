#include "SinglyLinkedList.h"

using namespace std;

int main() {
    SLinkedList<int> list;

    int size = 10;
    for (int idx = 0; idx < size; idx++) {
        list.add(idx);
    }

    SLinkedList<int>::Iterator it;
    int expvalue = 0;
    for (it = list.begin(); it != list.end(); it++) {
        assert(*it == expvalue);
        expvalue += 1;
    }
}