#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H
#include <iostream>

template <class T>
class DLinkedList
{
public:
    class Iterator; //forward declaration
    class Node;     //forward declaration
protected:
    Node* head;
    Node* tail;
    int count;
public:
    DLinkedList() : head(NULL), tail(NULL), count(0) {};
    ~DLinkedList();
    void add(const T& e);
    void add(int index, const T& e);
    T removeAt(int index);
    bool removeItem(const T& item);
    bool empty();
    int size();
    void clear();
    T get(int index);
    void set(int index, const T& e);
    int indexOf(const T& item);
    bool contains(const T& item);
    std::string toString();
    Iterator begin()
    {
        return Iterator(this, true);
    }
    Iterator end()
    {
        return Iterator(this, false);
    }
public:
    class Node
    {
    private:
        T data;
        Node* next;
        Node* previous;
        friend class DLinkedList<T>;

        Iterator begin()
        {
            return Iterator(this, true);
        }
        Iterator end()
        {
            return Iterator(this, false);
        }

    public:
        Node()
        {
            this->previous = NULL;
            this->next = NULL;
        }

        Node(const T& data)
        {
            this->data = data;
            this->previous = NULL;
            this->next = NULL;
        }
    };
    class Iterator
    {
    private:
        DLinkedList<T>* pList;
        Node* current;
        int index; // is the index of current in pList
    public:
        Iterator(DLinkedList<T>* pList, bool begin);
        Iterator& operator=(const Iterator& iterator);
        void set(const T& e);
        T& operator*();
        bool operator!=(const Iterator& iterator);
        void remove();

        // Prefix ++ overload
        Iterator& operator++();

        // Postfix ++ overload
        Iterator operator++(int);
    };
};
/*
 * TODO: Implement class Iterator's method
 * Note: method remove is different from SLinkedList, which is the advantage of DLinkedList
 */


template <class T>
void DLinkedList<T>::add(const T& e) {
    /* Insert an element into the end of the list. */
    //create new node
    Node* newnode = new Node(e);

    //insert
    if (this->head == NULL || this->tail == NULL) {
        this->head = newnode;
        this->tail = newnode;
    }
    else {
        this->tail->next = newnode;
        newnode->previous = this->tail;
        this->tail = newnode;
    }
    ++this->count;
}

template<class T>
void DLinkedList<T>::add(int index, const T& e) {
    /* Insert an element into the list at given index. */
    //special case
    if (index<0 || index>this->size()) return;
    //create newnode
    Node* newnode = new Node(e);
    //insert first
    if (index == 0) {
        if (this->head == NULL || this->tail == NULL) {
            this->head = newnode;
            this->tail = newnode;
        }
        else {
            newnode->next = this->head;
            this->head->previous = newnode;
            this->head = newnode;
        }
    }
    //insert last
    else if (index == this->size()) {
        if (this->head == NULL || this->tail == NULL) {
            this->head = newnode;
            this->tail = newnode;
        }
        else {
            this->tail->next = newnode;
            newnode->previous = this->tail;
            this->tail = newnode;
        }
    }
    //insert middle
    else {
        Node* pre = this->head;
        for (int i = 1; i < index; i++) {
            pre = pre->next;
        }
        Node* post = pre->next;
        //insert
        pre->next = newnode;
        post->previous = newnode;
        newnode->previous = pre;
        newnode->next = post;
    }
    ++this->count;
}

template<class T>
int DLinkedList<T>::size() {
    /* Return the length (size) of list */
    return this->count;
}

template<class T>
T DLinkedList<T>::get(int index) {
    /* Give the data of the element at given index in the list. */
    if (index < 0 || index >= this->size()) return T();
    Node* copy = this->head;
    for (int i = 0; i < index; i++) {
        copy = copy->next;
    }
    return copy->data;
}

template <class T>
void DLinkedList<T>::set(int index, const T& e) {
    /* Assign new value for element at given index in the list */
    if (index < 0 || index >= this->size()) return;
    Node* copy = this->head;
    for (int i = 0; i < index; i++) {
        copy = copy->next;
    }
    copy->data = e;
}

template<class T>
bool DLinkedList<T>::empty() {
    /* Check if the list is empty or not. */
    return this->head == NULL;
}

template<class T>
int DLinkedList<T>::indexOf(const T& item) {
    /* Return the first index wheter item appears in list, otherwise return -1 */
    int idx = 0;
    Node* copy = this->head;
    while (copy) {
        if (copy->data == item) {
            return idx;
        }
        else {
            idx++;
            copy = copy->next;
        }
    }
    return -1;
}

template<class T>
bool DLinkedList<T>::contains(const T& item) {
    /* Check if item appears in the list */
    Node* copy = this->head;
    while (copy) {
        if (copy->data == item) {
            return 1;
        }
        else {
            copy = copy->next;
        }
    }
    return 0;
}

template <class T>
T DLinkedList<T>::removeAt(int index)
{
    /* Remove element at index and return removed value */
    if (!this->head || index < 0 || index >= this->size()) return T();
    T tmp;
    if (index == 0) {
        tmp = this->head->data;
        this->head = this->head->next;
        if (this->head) {
            this->head->previous = NULL;
        }
        else {
            this->tail = NULL;
        }
    }
    else if (index == this->size() - 1) {
        tmp = this->tail->data;
        this->tail = this->tail->previous;
        if (this->tail) {
            this->tail->next = NULL;
        }
        else {
            this->head = NULL;
        }
    }
    else {
        Node* copy1 = this->head;
        for (int i = 1; i < index; i++) {
            copy1 = copy1->next;
        }
        tmp = copy1->next->data;
        Node* copy2 = copy1->next->next;
        copy1->next = copy2;
        copy2->previous = copy1;
    }
    --this->count;
    return tmp;
}

template <class T>
bool DLinkedList<T>::removeItem(const T& item)
{
    /* Remove the first apperance of item in list and return true, otherwise return false */
    if (this->size() == 0) return 0;
    bool found = 0;
    //item in first
    if (this->head->data == item) {
        if (this->size() == 1) {
            this->head = NULL;
            this->tail = NULL;
        }
        else {
            this->head = this->head->next;
            this->head->previous = NULL;
        }
        found = 1;
    }
    else {
        Node* copy = this->head;
        while (copy->next) {
            if (copy->next->data == item) {
                if (copy->next == this->tail) {
                    this->tail = copy;
                    this->tail->next = NULL;
                }
                else {
                    Node* copy1 = copy->next->next;
                    copy->next = copy1;
                    copy1->previous = copy;
                }
                found = 1;
                break;
            }
            else {
                copy = copy->next;
            }
        }
    }
    --this->count;
    return found;
}

template<class T>
void DLinkedList<T>::clear() {
    /* Remove all elements in list */
    this->head = NULL;
    this->tail = NULL;
    this->count = 0;
}


template <class T>
DLinkedList<T>::Iterator::Iterator(DLinkedList<T>* pList, bool begin)
{
    this->pList = pList;
    if (begin == true) {
        this->index = (this->pList != NULL) ? 0 : -1;
        this->current = (this->pList != NULL) ? this->pList->head : NULL;
    }
    else {
        this->current = NULL;
        this->index = (this->pList != NULL) ? this->pList->size() : 0;
    }
}

template <class T>
typename DLinkedList<T>::Iterator& DLinkedList<T>::Iterator::operator=(const DLinkedList<T>::Iterator& iterator)
{
    this->pList = iterator.pList;
    this->index = iterator.index;
    this->current = iterator.current;

    return (*this);
}

template <class T>
void DLinkedList<T>::Iterator::set(const T& e)
{
    if (this->current == NULL) {
        throw std::out_of_range("Segmentation fault!");
    }
    else {
        this->pList->set(this->index, e);
        this->current->data = e;
    }
}

template<class T>
T& DLinkedList<T>::Iterator::operator*()
{
    static T null_ref; // default-constructed object for the null reference
    if (this->current == nullptr) {
        return null_ref; // return the null reference
    }
    return this->current->data;
}

template<class T>
void DLinkedList<T>::Iterator::remove()
{
    /*
    * TODO: delete Node in pList which Node* current point to.
    *       After that, Node* current point to the node before the node just deleted.
    *       If we remove first node of pList, Node* current point to nullptr.
    *       Then we use operator ++, Node* current will point to the head of pList.
    */
    if (this->current == this->pList->head && this->current == this->pList->tail) {
        this->pList->head = NULL;
        this->pList->tail = NULL;
        this->index = -1;
        this->current = NULL;
        this->pList->count--;
    }
    else if (this->current == this->pList->head) {
        this->pList->head = this->pList->head->next;
        this->current = this->pList->head->previous;
        this->index = -1;
        this->pList->count--;
    }
    else if (this->current == this->pList->tail) {
        this->pList->tail = this->pList->tail->previous;
        this->index = -1;
        delete this->current;
        this->current = this->pList->tail;
        this->pList->count--;
    }
    else {
        Node* tmp = current->previous;
        current->previous->next = current->next;
        current->next->previous = current->previous;
        delete current;
        this->index -= 1;
        current = tmp;
        this->pList->count--;
    }
}

template<class T>
bool DLinkedList<T>::Iterator::operator!=(const DLinkedList::Iterator& iterator)
{
    return !(this->current == iterator.current && this->index == iterator.index);
}

template<class T>
typename DLinkedList<T>::Iterator& DLinkedList<T>::Iterator::operator++()
{
    if (this->index == -1) {
        this->index++;
        this->current = this->pList->head;
    }
    else {
        this->current = this->current->next;
        this->index++;
    }
    return *this;
}

template<class T>
typename DLinkedList<T>::Iterator DLinkedList<T>::Iterator::operator++(int)
{
    Iterator it = (*this);
    if (this->index == -1) {
        this->current = this->pList->head;
        this->index += 1;
    }
    else {
        this->current = this->current->next;
        this->index += 1;
    }
    return it;
}


struct ListNode {
    int val;
    ListNode *left;
    ListNode *right;
    ListNode(int x = 0, ListNode *l = nullptr, ListNode* r = nullptr) : val(x), left(l), right(r) {}
};
ListNode* reverseDLL(ListNode* head) {
    ListNode* current = head;

    while (current != NULL) {
        ListNode* tmp = current->left;
        current->left = current->right;
        current->right = tmp;
        if (current->left == NULL) {
            head = current;
        }
        current = current->left;
    }
    return head;
}
ListNode* tail(ListNode* head) {
    if (head == NULL) return NULL;
    ListNode* current = head;
    while (current->right) {
        current = current->right;
    }
    return current;
}

ListNode* reverse(ListNode* head, int a, int b) {
    if (head == NULL)return NULL;
    //Determine index a & b
    ListNode* pre = head;
    ListNode* post = head;
    for (int i = 1; i < a; i++) {
        pre = pre->right;
        post = post->right;
    }
    for (int i = a; i < b; i++) {
        post = post->right;
    }
    if (pre == NULL || post == NULL) return head;
    //reverse
    if (pre->left == NULL && post->right == NULL) {
        return reverseDLL(head);
    }
    else if (pre->left == NULL) {
        ListNode* afterPost = post->right;
        post->right = NULL;
        afterPost->left = NULL;
        head = reverseDLL(pre);
        ListNode* t = tail(head);
        t->right = afterPost;
        afterPost->left = t;
    }
    else if (post->right == NULL) {
        ListNode* beforPre = pre->left;
        pre->left = NULL;
        beforPre->right = NULL;
        ListNode* h = reverseDLL(pre);
        beforPre->right = h;
        h->left = beforPre;
    }
    else {
        ListNode* afterPost = post->right;
        post->right = NULL;
        afterPost->left = NULL;
        ListNode* beforPre = pre->left;
        pre->left = NULL;
        beforPre->right = NULL;
        ListNode* h = reverseDLL(pre);
        ListNode* t = tail(h);
        beforPre->right = h;
        h->left = beforPre;
        t->right = afterPost;
        afterPost->left = t;
    }
    
    return head;    
}
#include "DoublyLinkedList.cpp"
#endif
