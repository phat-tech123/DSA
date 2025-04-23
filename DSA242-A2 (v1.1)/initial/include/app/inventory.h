#ifndef INVENTORY_MANAGER_H
#define INVENTORY_MANAGER_H

#include "list/XArrayList.h"
#include "list/DLinkedList.h"
#include <sstream>
#include <string>
#include <iostream>
#include <iomanip>
#include <stdexcept>

using namespace std;

// -------------------- List1D --------------------
template <typename T>
class List1D
{
private:
    IList<T> *pList;

public:
    List1D();
    List1D(int num_elements);
    List1D(const T *array, int num_elements);
    List1D(const List1D<T> &other);
    virtual ~List1D();

    int size() const;
    T get(int index) const;
    void set(int index, T value);
    void add(const T &value);
    string toString() const;

    void add(int index, const T &value);
    void removeAt(int index);


    //friend ostream &operator<<(ostream &os, const List1D<T> &list);
    template <typename U>
    friend ostream &operator<<(ostream &os, const List1D<U> &list);
};

// -------------------- List2D --------------------
template <typename T>
class List2D
{
private:
    IList<IList<T> *> *pMatrix;

public:
    List2D();
    List2D(List1D<T> *array, int num_rows);
    List2D(const List2D<T> &other);
    virtual ~List2D();

    int rows() const;
    void setRow(int rowIndex, const List1D<T> &row);
    T get(int rowIndex, int colIndex) const;
    List1D<T> getRow(int rowIndex) const;
    string toString() const;
    
    void addRow(const List1D<T> &row);
    void removeAt(int index);

    //friend ostream &operator<<(ostream &os, const List2D<T> &matrix);
    template <typename U>
    friend ostream &operator<<(ostream &os, const List2D<U> &matrix);

};

struct InventoryAttribute
{
    string name;
    double value;
    InventoryAttribute() : name(""), value(0.0) {}
    InventoryAttribute(const string &name, double value) : name(name), value(value) {}
    string toString() const { return name + ": " + to_string(value); }
    bool operator==(const InventoryAttribute& other) const {
    	return name == other.name && value == other.value;
    }
    friend ostream& operator<<(ostream& os, const InventoryAttribute& attr);
};
ostream& operator<<(ostream& os, const InventoryAttribute& attr) {
    os << attr.toString();
    return os;
}

// -------------------- InventoryManager --------------------
class InventoryManager
{
private:
    List2D<InventoryAttribute> attributesMatrix;
    List1D<string> productNames;
    List1D<int> quantities;

public:
    InventoryManager();
    InventoryManager(const List2D<InventoryAttribute> &matrix,
                     const List1D<string> &names,
                     const List1D<int> &quantities);
    InventoryManager(const InventoryManager &other);

    int size() const;
    List1D<InventoryAttribute> getProductAttributes(int index) const;
    string getProductName(int index) const;
    int getProductQuantity(int index) const;
    void updateQuantity(int index, int newQuantity);
    void addProduct(const List1D<InventoryAttribute> &attributes, const string &name, int quantity);
    void removeProduct(int index);

    List1D<string> query(string attributeName, const double &minValue,
                         const double &maxValue, int minQuantity, bool ascending) const;

    void removeDuplicates();

    static InventoryManager merge(const InventoryManager &inv1,
                                  const InventoryManager &inv2);

    void split(InventoryManager &section1,
               InventoryManager &section2,
               double ratio) const;

    List2D<InventoryAttribute> getAttributesMatrix() const;
    List1D<string> getProductNames() const;
    List1D<int> getQuantities() const;
    string toString() const;
};

// -------------------- List1D Method Definitions --------------------
template <typename T>
List1D<T>::List1D()
{
	this->pList = new XArrayList<T>();
}

template <typename T>
List1D<T>::List1D(int num_elements)
{
	this->pList = new XArrayList<T>();
	for(int i = 0; i< num_elements; i++){
		this->pList->add(0);
	}
}

template <typename T>
List1D<T>::List1D(const T *array, int num_elements)
{
	this->pList = new XArrayList<T>();
	for(int i = 0; i< num_elements; i++){
		this->pList->add(array[i]);
	}
}

template<typename T>
List1D<T>::List1D(const List1D<T> &other){
	this->pList = new XArrayList<T>();
	for (int i = 0; i < other.size(); i++) {
		this->pList->add(other.get(i));
	}
}

template <typename T>
List1D<T>::~List1D()
{
	delete pList;
}

template <typename T>
int List1D<T>::size() const
{
	return pList->size();
}

template <typename T>
T List1D<T>::get(int index) const
{
	return pList->get(index);
}

template <typename T>
void List1D<T>::set(int index, T value)
{
	if(index < 0 || index >= pList->size()){
		throw std::out_of_range("Index is out of range!");
	}
	XArrayList<T> * tmp = new XArrayList<T>(); 
	for(int i = 0; i < this->pList->size(); i++){
		tmp->add(pList->get(i));
	}
	tmp->set(index, value);
	this->pList = tmp;
}

template <typename T>
void List1D<T>::add(const T &value)
{
	pList->add(value);
}

template <typename T>
void List1D<T>::add(int index, const T &value)
{
	pList->add(index, value);
}
template <typename T>   
void List1D<T>::removeAt(int index){
	pList->removeAt(index);
}

template <typename T>
string List1D<T>::toString() const
{

	return pList->toString();
}

template <typename T>
ostream &operator<<(ostream &os, const List1D<T> &list)
{
	os << "[";
	for (int i = 0; i < list.size(); i++)
	{
	os << list.get(i);
	if (i < list.size() - 1)
	    os << ", "; 
	}
	os << "]";
	return os;
}


// -------------------- List2D Method Definitions --------------------
template <typename T>
List2D<T>::List2D()
{
	pMatrix = new DLinkedList<IList<T>*>();
}

template <typename T>
List2D<T>::List2D(List1D<T> *array, int num_rows)
{
	this->pMatrix = new DLinkedList<IList<T>*>;
	for(int i = 0; i < num_rows; i++){
		IList<T>* tmp = new DLinkedList<T>();
		for(int j = 0; j < array[i].size(); j++){
			tmp->add(array[i].get(j));
		}
		this->pMatrix->add(tmp);
	}
}

template <typename T>
List2D<T>::List2D(const List2D<T> &other)
{
	this->pMatrix = new DLinkedList<IList<T>*>();
    	for (int i = 0; i < other.rows(); i++) {
        	// Create a new row list and copy all elements
        	IList<T>* newRow = new DLinkedList<T>();
		List1D<T> otherRow = other.getRow(i); 
        	for (int j = 0; j < otherRow.size(); j++) {
            		newRow->add(otherRow.get(j));
        	}
        	this->pMatrix->add(newRow);
    	}
}

template <typename T>
List2D<T>::~List2D()
{
	while(pMatrix->empty()){
		delete pMatrix->removeAt(0);
	}
	delete pMatrix;
}

template <typename T>
int List2D<T>::rows() const
{
	return pMatrix->size();
}

template <typename T>
void List2D<T>::setRow(int rowIndex, const List1D<T> &row)
{
	if(rowIndex < 0 || rowIndex >= pMatrix->size()){
		throw std::out_of_range("Index is out of range!");
	}
	DLinkedList<DLinkedList<T>*> * tmp = new DLinkedList<DLinkedList<T>*>(); 
	for(int i = 0; i < this->pList->size(); i++){
		DLinkedList<T> * subtmp = new DLinkedList<T>(); 
		if(i == rowIndex){
			for(int j = 0; j< row.size(); j++){
				subtmp->add(row.get(j));
			}
		}
		else{
			List1D<T> list = this->pMatrix->get(i);
			for(int j = 0; j< row.size(); j++){
				subtmp->add(list.get(j));
			}
		}
		tmp->add(subtmp);
	}
	this->pMatrix = tmp;
}

template <typename T>   
void List2D<T>::removeAt(int index){
	pMatrix->removeAt(index);
}

template <typename T>
void List2D<T>::addRow(const List1D<T> &row)
{
	IList<T>* tmp = new DLinkedList<T>();
	for(int i = 0; i < row.size(); i++){
		tmp->add(row.get(i));
	}
	pMatrix->add(tmp);
}

template <typename T>
T List2D<T>::get(int rowIndex, int colIndex) const
{
	return pMatrix->get(rowIndex)->get(colIndex);
}

template <typename T>
List1D<T> List2D<T>::getRow(int rowIndex) const
{
	if (rowIndex < 0 || rowIndex >= pMatrix->size()) {
		throw std::out_of_range("Index is out of range!");
	}

	IList<T>* rowList = pMatrix->get(rowIndex);

	List1D<T> products;

	for (int i = 0; i < rowList->size(); i++) {
	products.add(rowList->get(i));
	}

	return products;
}

template <typename T>
string List2D<T>::toString() const
{
	stringstream ss;
	ss << "[";
	for(int i = 0; i < rows(); i++){
		ss << getRow(i).toString();
		
		if(i < rows() - 1) ss << ", ";
	}

	ss << "]";
	return ss.str();
}

template <typename T>
ostream &operator<<(ostream &os, const List2D<T> &matrix)
{
	os << "[";
	for(int i = 0; i < matrix.rows(); i++){
		os << matrix.getRow(i).toString();
		if(i < matrix.rows() - 1)
			os << ",";
	}
	os << "]";
    	return os;
}

// -------------------- InventoryManager Method Definitions --------------------
InventoryManager::InventoryManager()
{
	this->attributesMatrix = List2D<InventoryAttribute>();
	this->productNames = List1D<string>();
	this->quantities = List1D<int>();
}

InventoryManager::InventoryManager(const List2D<InventoryAttribute> &matrix,
                                   const List1D<string> &names,
                                   const List1D<int> &quantities)
	: attributesMatrix(matrix),  
	  productNames(names),
	  quantities(quantities) 
{}

InventoryManager::InventoryManager(const InventoryManager &other)
{
	this->attributesMatrix = List2D<InventoryAttribute>(other.getAttributesMatrix());
	this->productNames = List1D<string>(other.getProductNames());
	this->quantities = List1D<int>(other.getQuantities());
}

int InventoryManager::size() const
{
	return this->productNames.size();
}

List1D<InventoryAttribute> InventoryManager::getProductAttributes(int index) const
{
	if(index < 0 || index >= this->attributesMatrix.rows()){
		throw std::out_of_range("Index is invalid");
	}
	return this->attributesMatrix.getRow(index);
}

string InventoryManager::getProductName(int index) const
{
	if(index < 0 || index >= this->productNames.size()){
		throw std::out_of_range("Index is out of range!");
	}
	return this->productNames.get(index);
}

int InventoryManager::getProductQuantity(int index) const
{
	if(index < 0 || index >= this->quantities.size()){
		throw std::out_of_range("Index is out of range!");
	}
	return this->quantities.get(index);
}

void InventoryManager::updateQuantity(int index, int newQuantity)
{
	if(index < 0 || index >= this->size()){
		throw std::out_of_range("Index is invalid");
	}
	this->quantities.set(index, newQuantity);
}

void InventoryManager::addProduct(const List1D<InventoryAttribute> &attributes, const string &name, int quantity)
{
	this->attributesMatrix.addRow(attributes);
	this->productNames.add(name);
	this->quantities.add(quantity);
}

void InventoryManager::removeProduct(int index)
{
	this->attributesMatrix.removeAt(index);		
	this->productNames.removeAt(index);
	this->quantities.removeAt(index);
}

List1D<string> InventoryManager::query(string attributeName, const double &minValue,
                                       const double &maxValue, int minQuantity, bool ascending) const
{
	List1D<string> query_products;
	for(int i = 0; i < this->size(); i++){
		if(getProductQuantity(i) < minQuantity){
			continue;
		}

 		List1D<InventoryAttribute> attributes = getProductAttributes(i);
		bool flag = false;
		for(int j = 0; j < attributes.size(); j++){
			InventoryAttribute attribute = attributes.get(j);
			if(attribute.name == attributeName && attribute.value >= minValue && attribute.value <= maxValue){
				flag = true;
				break;
			}
		}

		if(flag) query_products.add(getProductName(i));
	}


	if(ascending){
		for(int i = 0; i < query_products.size(); i++){
			bool flag = false;
			for(int j = 0; j < query_products.size() - i - 1; j++){
				if(query_products.get(j) > query_products.get(j+1)){
					string tmp = query_products.get(j);
					query_products.set(j, query_products.get(j+1));
					query_products.set(j+1, tmp);
					flag = true;
				}
			}
			if(!flag) break;
		}
	}
	else{
		for(int i = 0; i < query_products.size(); i++){
			bool flag = false;
			for(int j = 0; j < query_products.size() - i - 1; j++){
				if(query_products.get(j) < query_products.get(j+1)){
					string tmp = query_products.get(j);
					query_products.set(j, query_products.get(j+1));
					query_products.set(j+1, tmp);
					flag = true;
				}
			}
			if(!flag) break;
		}
	}
	
	return query_products;
}

void InventoryManager::removeDuplicates()
{
	for(int i = 0; i < this->size(); i++){
		for(int j = i+1; j < this->size(); j++){
			if(getProductName(i) != getProductName(j)) continue;
			if(getProductAttributes(j).toString() != getProductAttributes(i).toString()) continue;
				
			this->quantities.set(i, getProductQuantity(i)+getProductQuantity(j));
			this->removeProduct(j);
		}
	}
}

InventoryManager InventoryManager::merge(const InventoryManager &inv1,
                                         const InventoryManager &inv2)
{
	InventoryManager invMerge;
    
    	for (int i = 0; i < inv1.size(); i++) {
        	invMerge.addProduct(inv1.getProductAttributes(i), inv1.getProductName(i), inv1.getProductQuantity(i));
    	}
    
    	for (int i = 0; i < inv2.size(); i++) {
        	invMerge.addProduct(inv2.getProductAttributes(i), inv2.getProductName(i), inv2.getProductQuantity(i));
    	}
    
    	invMerge.removeDuplicates();
    
    	return invMerge;
}

int myCeil(double x) {
    int xi = (int)x;
    return (x == (double)xi) ? xi : xi + ((x > 0) ? 1 : 0);
}

void InventoryManager::split(InventoryManager &section1,
                             InventoryManager &section2,
                             double ratio) const
{
	int num = myCeil(ratio * double(this->size()));
	for(int i = 0; i < num; i++){
		section1.addProduct(this->getProductAttributes(i), this->getProductName(i), this->getProductQuantity(i));
	}
	for(int i = num; i < this->size(); i++){
		section2.addProduct(this->getProductAttributes(i), this->getProductName(i), this->getProductQuantity(i));
	}
}

List2D<InventoryAttribute> InventoryManager::getAttributesMatrix() const
{
	return this->attributesMatrix;
}

List1D<string> InventoryManager::getProductNames() const
{
	return this->productNames;
}

List1D<int> InventoryManager::getQuantities() const
{
	return this->quantities;
}

string InventoryManager::toString() const
{
	stringstream ss;
	ss << "InventoryManager[\n";
	ss << "  AttributesMatrix: ";
	ss << this->attributesMatrix.toString();
	ss << ",\n";
	ss << "  ProductNames: ";
	ss << this->productNames.toString();
	ss << ",\n";
	ss << "  Quantities: ";
	ss << this->quantities.toString();
	ss << "\n]";
	return ss.str();
}

#endif /* INVENTORY_MANAGER_H */

