#ifndef SINGLYLINKEDLIST_H
#define SINGLYLINKEDLIST_H
#include <iostream>

template <class T>
class SLinkedList
{
public:
    class Iterator; //forward declaration
    class Node;     //forward declaration
protected:
    Node* head;
    Node* tail;
    int count;
public:
    SLinkedList() {
        head = NULL;
        tail = NULL;
        count = 0;
    };
    ~SLinkedList() {
        delete this->head;
        delete this->tail;
        this->count = 0;
    }
    void add(const T& e) {
        /* Insert an element into the end of the list. */

        //make new node
        Node* tmp = new Node(e, NULL);

        //insert
        if (!this->head && !this->tail) {
            this->head = tmp;
            this->tail = tmp;
        }
        else {
            this->tail->next = tmp;
            this->tail = tmp;
        }
        this->count++;
    }
    void add(int index, T e) {
        /* Insert an element into the list at given index. */

        if (index < 0 || index > this->count) {
            throw std::out_of_range("Segmentation fault!");
        }

        //make new node
        Node* tmp = new Node(e, NULL);
        if (index == 0) {
            if (!this->head && !this->tail) {
                this->head = tmp;
                this->tail = tmp;
            }
            else {
                tmp->next = this->head;
                this->head = tmp;
            }
        }
        else if (index == this->count) {
            if (!this->head && !this->tail) {
                this->head = tmp;
                this->tail = tmp;
            }
            else {
                this->tail->next = tmp;
                this->tail = tmp;
            }
        }
        else {
            Node* copy = this->head;
            for (int i = 1; i < index; i++) {
                copy = copy->next;
            }
            tmp->next = copy->next;
            copy->next = tmp;
        }
        ++this->count;
    }
    T removeAt(int index) {
        /* Return the length (size) of list */
        return this->count;
    }
    bool removeItem(const T& item) {
        /* Remove the first apperance of item in list and return true, otherwise return false */
        if (this->head == NULL) return 0;
        Node* cHead = NULL;
        Node* cTail = NULL;
        Node* current = this->head;
        bool found = 0;
        while (current) {
            if (current->data != item) {
                Node* tmp = new Node(current->data, NULL);
                if (!cTail && !cHead) {
                    cTail = tmp;
                    cHead = tmp;
                }
                else {
                    cTail->next = tmp;
                    cTail = tmp;
                }
            }
            else {
                if (found) {
                    Node* tmp = new Node(current->data, NULL);
                    if (!cTail && !cHead) {
                        cTail = tmp;
                        cHead = tmp;
                    }
                    else {
                        cTail->next = tmp;
                        cTail = tmp;
                    }
                }
                else {
                    found = 1;
                }
            }

            current = current->next;
        }
        this->head = cHead;
        this->tail = cTail;
        --this->count;
        return found;
    }
    bool empty() {
        /* Check if the list is empty or not. */
        if (this->size() == 0) return 1;
        return 0;
    }
    int size(){
        /* Return the length (size) of list */
        return this->count;
    }
    void clear() {
        /* Remove all elements in list */
        this->count = 0;
        this->head = NULL;
        this->tail = NULL;
    }
    T get(int index) {
        /* Give the data of the element at given index in the list. */
        if (index < 0 || index >= this->size()) {
            return T();
        }

        Node* copy = this->head;
        for (int i = 0; i < index; i++) {
            copy = copy->next;
        }
        return copy->data;
    }
    void set(int index, const T& e){
        /* Assign new value for element at given index in the list */
        if (index < 0 || index >= this->size()) {
            throw std::out_of_range("segmentation fault");
        }

        Node* copy = this->head;
        for (int i = 0; i < index; i++) {
            copy = copy->next;
        }
        copy->data = e;
    }
    int indexOf(const T& item){
        /* Return the first index wheter item appears in list, otherwise return -1 */
        int index = 0;
        Node* copy = this->head;
        while (copy) {
            if (copy->data == item) {
                return index;
            }
            else {
                ++index;
                copy = copy->next;
            }
        }
        return -1;
    }
    bool contains(const T& item){
        /* Check if item appears in the list */
        Node* copy = this->head;
        while (copy) {
            if (copy->data == item) {
                return true;
            }
            else {
                copy = copy->next;
            }
        }
        return false;
    }
    string toString() {
        return "";
    }
    SLinkedList(const SLinkedList& list)
    {
        this->count = 0;
        this->head = NULL;
        this->tail = NULL;
    }
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
        friend class SLinkedList<T>;
    public:
        Node()
        {
            next = 0;
        }
        Node(Node* next)
        {
            this->next = next;
        }
        Node(T data, Node* next = NULL)
        {
            this->data = data;
            this->next = next;
        }
    };
    class Iterator
    {
    private:
        SLinkedList<T>* pList;
        Node* current;
        int index; // corresponding with current node
    public:
        Iterator() {
            pList = NULL;
            current = NULL;
            index = 0;
        }
        Iterator(SLinkedList<T>* pList, bool begin) {
            /*
                Constructor of iterator
                * Set pList to pList
                * begin = true:
            **Set current(index = 0) to pList's head if pList is not NULL
                * *Otherwise set to NULL(index = -1)
                * begin = false :
                **Always set current to NULL
                * *Set index to pList's size if pList is not NULL, otherwise 0
                */
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
        Iterator& operator=(const Iterator& iterator) {
            /*
        Assignment operator
        * Set this current, index, pList to iterator corresponding elements.
            */
            this->current = iterator.current;
            this->index = iterator.index;
            this->pList = iterator.pList;

            return *this;
        }
        void set(const T& e) {
            /*
        Set the new value for current node
        * Exception: throw std::out_of_range("Segmentation fault!") if current is NULL
            */
            if (this->current == NULL) {
                throw std::out_of_range("Segmentation fault!");
            }
            this->current->data = e;
        }
        void remove();
        T& operator*() {
            /*
        Get data stored in current node
        * Exception: throw std::out_of_range("Segmentation fault!") if current is NULL
    */
            if (this->current == NULL) {
                throw std::out_of_range("Segmentation fault!");
            }
            return this->current->data;
        }
        bool operator!=(const Iterator& iterator) {
            return this->current == iterator.current && this->index == iterator.index;
        }

        // Prefix ++ overload
        Iterator& operator++() {
            if (this->current->next == NULL) {
                throw std::out_of_range("Segmentation fault!");
            }
            Node* copy = this->pList->head;
            while (copy) {
                if (copy == this->current) {
                    this->current = copy->next;
                }
                else {
                    copy = copy->next;
                }
            }
            return *this;
        }

        // Postfix ++ overload
        Iterator operator++(int) {
            if (this->current->next == NULL) {
                throw std::out_of_range("Segmentation fault!");
            }
            Node* copy = this->pList->head;
            while (copy) {
                if (copy == this->current) {
                    this->current = copy->next;
                }
                else {
                    copy = copy->next;
                }
            }
            return *this;
        }
    };
};



class Polynomial;
class Term {
private:
    double coeff;
    int exp;
    friend class Polynomial;
public:
    Term(double coeff = 0.0, int exp = 0) {
        this->coeff = coeff;
        this->exp = exp;
    }
    bool operator==(const Term& rhs) const {
        return this->coeff == rhs.coeff && this->exp == rhs.exp;
    }
    friend std::ostream& operator<<(std::ostream& os, const Term& term) {
        std::cout << std::endl;
        std::cout << "Term: " << "(" << term.coeff << " " << term.exp << ")";
        return os;
    }
};
class Polynomial {
private:
    SLinkedList<Term>* terms;
public:
    Polynomial() {
        this->terms = new SLinkedList<Term>();
    }
    ~Polynomial() {
        this->terms->clear();
    }
    void insertTerm(const Term& term){
        if (this->terms->empty()) {
            this->terms->add(term);
        }
        else {
            //make a linked list of exp
            SLinkedList<int>* integer = new SLinkedList<int>();
            for (int i = 0; i < this->terms->size(); i++) {
                Term tmp = this->terms->get(i);
                integer->add(tmp.exp);
            }
            if (integer->contains(term.exp)) {
                int index = integer->indexOf(term.exp);
                Term tmp = this->terms->get(index);
                int finalCoeff = tmp.coeff + term.coeff;
                this->terms->set(integer->indexOf(term.exp), Term(finalCoeff, term.exp));
            }
            else {
                int i = 0;
                while (i < integer->size() && term.exp < integer->get(i)) {
                    i++;
                }
                integer->add(i, term.exp);
                this->terms->add(i, term);
            }
        }
        Term tmp = Term(0.0, term.exp);
        if (this->terms->contains(tmp)) {
            this->terms->removeItem(tmp);
        }
    }
    void insertTerm(double coeff, int exp) {
        Term tmp = Term(coeff, exp);
        insertTerm(tmp);
    }
    void print() {
        SLinkedList<Term>::Iterator it;
        std::cout << "[";
        for (it = this->terms->begin(); it != this->terms->end(); it++) {
            std::cout << (*it);
        }
        std::cout << std::endl << "]";
    }
};
#endif
