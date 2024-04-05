#include<iostream>
#include"DoublyLinkedList.h"

int main() {
    DLinkedList<int> list;
    int size = 10;
    for (int idx = 0; idx < size; idx++)
    {
        list.add(idx);
    }

    DLinkedList<int>::Iterator it = list.begin();
    for (; it != list.end(); it++)
    {
        it.remove();
    }

}