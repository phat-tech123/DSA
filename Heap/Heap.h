#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

#define SEPARATOR "#<ab@17943918#@>#"

template<class T>
class Heap {
protected:
    T* elements;
    int capacity;
    int count;
public:
    Heap()
    {
        this->capacity = 10;
        this->count = 0;
        this->elements = new T[capacity];
    }
    ~Heap()
    {
        delete[]elements;
    }
    void push(T item);
    int getItem(T item);
    void remove(T item);
    void clear();

    bool isEmpty();
    bool contains(T item);
    T peek();
    bool pop();
    int size();
    //
    void printHeap()
    {
        cout << "Max Heap [ ";
        for (int i = 0; i < count; i++)
            cout << elements[i] << " ";
        cout << "]\n";
    }
private:
    void ensureCapacity(int minCapacity);
    void reheapUp(int position);
    void reheapDown(int position);
};
//Your code goes here
template<class T>
int Heap<T>::size() {
    return this->count;
}

template<class T>
bool Heap<T>::isEmpty() {
    return this->count == 0;
}

template<class T>
T Heap<T>::peek() {
    if (this->count == 0) return T();
    return this->elements[0];
}

template<class T>
bool Heap<T>::contains(T item) {
    for (int i = 0; i < this->count; i++) {
        if (this->elements[i] == item) return true;
    }
    return false;
}

template<class T>
bool Heap<T>::pop() {
    if (this->count == 0) return false;
    //
    this->elements[0] = this->elements[this->count - 1];
    this->count--;
    this->reheapDown(0);
    return true;
}

//Use to push

template<class T>
void Heap<T>::push(T item) {
    ensureCapacity(this->count + 1);
    this->elements[this->count] = item;
    this->count++;
    reheapUp(this->count - 1);
}

template<class T>
void Heap<T>::ensureCapacity(int minCapacity) {
    if (minCapacity > this->capacity) {
        int newCapacity = (int)(1.5 * (double)this->capacity);
        T* newElements = new T[newCapacity];
        for (int i = 0; i < this->capacity; i++) {
            newElements[i] = this->elements[i];
        }
        delete[] this->elements;
        this->elements = newElements;
        this->capacity = newCapacity;
    }
}

template<class T>
void Heap<T>::reheapUp(int position) {
    while (position > 0) {
        int newposition = (position - 1) / 2;
        if (this->elements[position] > this->elements[newposition]) {
            std::swap(this->elements[position], this->elements[newposition]);
            position = newposition;
        }
        else {
            return;
        }
    }
}

//Out of class
void reheapDown(int maxHeap[], int numberOfElements, int index);//Forward declaration
void reheapUp(int maxHeap[], int numberOfElements, int index);//Forward declaration

void reheapDown(int maxHeap[], int numberOfElements, int index)
{
    while (2 * index + 1 < numberOfElements) {
        int newIdx1 = 2 * index + 1;
        int newIdx2 = 2 * index + 2;
        if (newIdx2 >= numberOfElements) {
            if (maxHeap[index] < maxHeap[newIdx1]) {
                std::swap(maxHeap[index], maxHeap[newIdx1]);
                index = newIdx1;
            }
            else {
                return;
            }
        }
        else {
            if (maxHeap[index] >= maxHeap[newIdx1] && maxHeap[index] >= maxHeap[newIdx2]) {
                break;
            }
            else {
                if (maxHeap[newIdx1] > maxHeap[newIdx2]) {
                    std::swap(maxHeap[newIdx1], maxHeap[index]);
                    index = newIdx1;
                }
                else {
                    std::swap(maxHeap[newIdx2], maxHeap[index]);
                    index = newIdx2;
                }
            }
        }
    }
}
void reheapUp(int maxHeap[], int numberOfElements, int index)
{
    while (index > 0) {
        int newIdx = (index - 1) / 2;
        if (maxHeap[index] > maxHeap[newIdx]) {
            std::swap(maxHeap[newIdx], maxHeap[index]);
            index = newIdx;
        }
        else
            return;
    }
}

template<class T>
int Heap<T>::getItem(T item) {
    // TODO: return the index of item in heap
    for (int i = 0; i < this->count; i++) {
        if (this->elements[i] == item) {
            return i;
        }
    }
    return -1;
}

template<class T>
void Heap<T>::remove(T item) {
    // TODO: remove the element with value equal to item
    int itemIdx = this->getItem(item);
    if (itemIdx == -1) return;
    int parentIndex = (itemIdx - 1) / 2;
    std::swap(this->elements[itemIdx], this->elements[this->count - 1]);
    this->count--;
    if (this->elements[itemIdx] > this->elements[parentIndex])
    {
        this->reheapUp(itemIdx);
    }
    else
    {
        this->reheapDown(itemIdx);
    }
}

template<class T>
void Heap<T>::clear() {
    // TODO: delete all elements in heap
    // then reallocate memory as initial state
    this->capacity = 10;
    this->count = 0;
    delete[] this->elements;
    this->elements = new T[capacity];
}

#include<queue>
template <class T>
class Sorting {
public:
    /* Function to print an array */
    static void printArray(T* start, T* end)
    {
        long size = end - start;
        for (int i = 0; i < size - 1; i++)
            cout << start[i] << ", ";
        cout << start[size - 1];
        cout << endl;
    }
    //Helping functions go here

    static void reheapDown(T* maxHeap, int numberOfElements, int index)
    {
        while (2 * index + 1 < numberOfElements) {
            int newIdx1 = 2 * index + 1;
            int newIdx2 = 2 * index + 2;
            if (newIdx2 >= numberOfElements) {
                if (maxHeap[index] < maxHeap[newIdx1]) {
                    swap(maxHeap[index], maxHeap[newIdx1]);
                    index = newIdx1;
                }
                else {
                    return;
                }
            }
            else {
                if (maxHeap[index] >= maxHeap[newIdx1] && maxHeap[index] >= maxHeap[newIdx2]) {
                    break;
                }
                else {
                    if (maxHeap[newIdx1] > maxHeap[newIdx2]) {
                        swap(maxHeap[newIdx1], maxHeap[index]);
                        index = newIdx1;
                    }
                    else {
                        swap(maxHeap[newIdx2], maxHeap[index]);
                        index = newIdx2;
                    }
                }
            }
        }
    }

    static void buildHeap(T* start, T* end) {
        int size = end - start;
        int lastNonLeafIdx = size / 2 - 1;
        for (int i = lastNonLeafIdx; i >= 0; i--) {
            Sorting<T>::reheapDown(start, size, i);
        }
    }

    static void heapSort(T* start, T* end) {
        //TODO
        Sorting<T>::buildHeap(start, end);
        int size = end - start;
        while (size > 0) {
            swap(start[0], start[size - 1]);
            size--;
            reheapDown(start, size, 0);
        }
        Sorting<T>::printArray(start, end);
    }
};

//
class PrinterQueue
{
private:
    struct PrintRequest {
        int priority;
        string fileName;
    };
    vector<PrintRequest> list;

    void reHeapUp(int position) {
        while (position > 0) {
            int newposition = (position - 1) / 2;
            if (this->list[position].priority > this->list[newposition].priority) {
                std::swap(this->list[position], this->list[newposition]);
                position = newposition;
            }
            else {
                return;
            }
        }
    }
    void reheapDown(int index) {
        int size = this->list.size();
        while (2 * index + 1 < size) {
            int newIdx1 = 2 * index + 1;
            int newIdx2 = 2 * index + 2;
            if (newIdx2 >= size) {
                if (this->list[index].priority < this->list[newIdx1].priority) {
                    std:: swap(this->list[index], this->list[newIdx1]);
                    index = newIdx1;
                }
                else {
                    return;
                }
            }
            else {
                if (this->list[index].priority >= this->list[newIdx1].priority &&
                    this->list[index].priority >= this->list[newIdx2].priority) {
                    break;
                }
                else {
                    if (this->list[newIdx1].priority > this->list[newIdx2].priority) {
                        std::swap(this->list[newIdx1], this->list[index]);
                        index = newIdx1;
                    }
                    else {
                        std::swap(this->list[newIdx2], this->list[index]);
                        index = newIdx2;
                    }
                }
            }
        }
    }

public:
    void push(PrintRequest item) {
        this->list.push_back(item);
        this->reHeapUp(this->list.size() - 1);
    }
    void pop() {
        int size = this->list.size();
        if (size == 0) return;
        this->list[0] = this->list[size - 1];
        this->list.pop_back();
        this->reheapDown(0);
    }

    void addNewRequest(int priority, string fileName)
    {
        // your code here
        //create new request
        PrintRequest newRequest;
        newRequest.priority = priority * 1000 + (1000 - this->list.size());
        newRequest.fileName = fileName;
        //push
        this->push(newRequest);
    }
    void print()
    {
        // your code here
        // After some logic code, you have to print fileName with endline

        if (this->list.size() == 0) {
            cout << "No file to print" << endl;
        }
        else if (this->list.size() > 0) {
            cout << this->list[0].fileName << endl;
            this->pop();
        }
    }
};

//
void reheapUp(vector<int>& maxHeap, int numberOfElements, int index)
{
    while (index > 0) {
        int newIdx = (index - 1) / 2;
        if (maxHeap[index] > maxHeap[newIdx]) {
            std::swap(maxHeap[newIdx], maxHeap[index]);
            index = newIdx;
        }
        else
            return;
    }
}


//alsmot right version
void reheapDown(vector<int>& maxHeap,int numberOfElements, int index) {
    while (2 * index + 1 < numberOfElements) {
        int newIdx1 = 2 * index + 1;
        int newIdx2 = 2 * index + 2;
        if (newIdx2 >= numberOfElements) {
            if (maxHeap[index] < maxHeap[newIdx1]) {
                std::swap(maxHeap[index], maxHeap[newIdx1]);
                index = newIdx1;
            }
            else {
                return;
            }
        }
        else {
            if (maxHeap[index] >= maxHeap[newIdx1] && maxHeap[index] >= maxHeap[newIdx2]) {
                break;
            }
            else {
                if (maxHeap[newIdx1] > maxHeap[newIdx2]) {
                    std::swap(maxHeap[newIdx1], maxHeap[index]);
                    index = newIdx1;
                }
                else {
                    std::swap(maxHeap[newIdx2], maxHeap[index]);
                    index = newIdx2; 
                }
            }
        }
    }
}

void buldHeap(vector<int>& arr) {
    int size = arr.size();
    int lastNonLeafIdx = size / 2 - 1;
    for (int i = lastNonLeafIdx; i >= 0; i--) {
        reheapDown(arr,size, i);
    }
}

void HeapSort(vector<int>& arr) {
    buldHeap(arr); // 7 3 5 2
    int size = arr.size(); //4
    while (size > 0) {
        std::swap(arr[0], arr[size - 1]);
        size--; //3
        reheapDown(arr, size, 0);
    }
}

int leastAfter(vector<int>& nums, int k) {
    // STUDENT ANSWER
    HeapSort(nums);
    while (k--) {
        nums[0] *= 2;
        HeapSort(nums);
    }
    return nums[0];
} 

//right version
int leastAfter(vector<int>& nums, int k) {
    // STUDENT ANSWER
    priority_queue<int, vector<int>, greater<int>> min_heap;
    for (int i = 0; i < (int)nums.size(); i++)
    {
        min_heap.push(nums.at(i));
    }
    while (k--)
    {
        int a = min_heap.top() * 2;
        min_heap.pop();
        min_heap.push(a);
    }
    return min_heap.top();
}