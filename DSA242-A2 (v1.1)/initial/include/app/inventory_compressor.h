#ifndef INVENTORY_COMPRESSOR_H
#define INVENTORY_COMPRESSOR_H

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <utility>
#include "inventory.h"
#include "hash/xMap.h"
#include "heap/Heap.h"
#include "list/XArrayList.h"


template<int treeOrder>
class HuffmanTree {
public:
    struct HuffmanNode {
        char symbol;
        int freq;
        XArrayList<HuffmanNode*> children;

        HuffmanNode(char s, int f); //Leaf node
        HuffmanNode(int f, const XArrayList<HuffmanNode*>& childs); //Internal node
    };

    HuffmanTree();
    ~HuffmanTree();

    void build(XArrayList<pair<char, int>>& symbolsFreqs);
    void generateCodes(xMap<char, std::string>& table);
    std::string decode(const std::string& huffmanCode);

private:
    HuffmanNode* root;
};

template<int treeOrder>
class InventoryCompressor {
public:
    InventoryCompressor(InventoryManager* manager);
    ~InventoryCompressor();

    void buildHuffman();
    void printHuffmanTable();
    std::string productToString(const List1D<InventoryAttribute>& attributes, const std::string& name);
    std::string encodeHuffman(const List1D<InventoryAttribute>& attributes, const std::string& name);
    std::string decodeHuffman(const std::string& huffmanCode, List1D<InventoryAttribute>& attributesOutput, std::string& nameOutput);

private:
    xMap<char, std::string>* huffmanTable;
    InventoryManager* invManager;
    HuffmanTree<treeOrder>* tree;
};


#endif // INVENTORY_COMPRESSOR_H
template <int treeOrder>
HuffmanTree<treeOrder>::HuffmanTree()
{
}

template <int treeOrder>
HuffmanTree<treeOrder>::~HuffmanTree()
{
    //TODO
}

template <int treeOrder>
void HuffmanTree<treeOrder>::build(XArrayList<pair<char, int>>& symbolsFreqs)
{
    //TODO
	Heap<HuffmanNode*> huffmanNodeHeap;
	for(int i = 0; i < symbolsFreqs.size(); i++){
		pair<char, int> p = symbolsFreqs.get(i);
		huffmanNodeHeap.push(new HuffmanNode(p.first, p.second));
	}
    	int L =  huffmanNodeHeap.size();
	int n = treeOrder;
	int cond = (L - 1) % (n - 1); 
	int d = (cond != 0) ? (n - 1) - cond : 0;
	for(int i = 0; i < d; i++){
		huffmanNodeHeap.push(new HuffmanNode('\0', 0));
	}

	while(huffmanNodeHeap.size() > 1){
		XArrayList<HuffmanNode*> childList;
		int fre = 0;
		for(int i = 0; i < treeOrder; i++){
			HuffmanNode* child = huffmanNodeHeap.pop();
			fre += child->freq;
			childList.add(child);
		}
		huffmanNodeHeap.push(new HuffmanNode(fre, childList));
	}

	this->root = huffmanNodeHeap.pop();
}

template <int treeOrder>
void HuffmanTree<treeOrder>::generateCodes(xMap<char, std::string> &table)
{
    //TODO
    	XArrayList<pair<HuffmanNode*, std::string>> stack;	
	stack.add({this->root, ""});
	while(!stack.empty()){
		pair<HuffmanNode*, string> curr = stack.removeAt(stack.size()-1);

		if(curr.first->children.empty()){ //leaf node
			if(curr.first->symbol != '\0'){
				table.put(curr.first->symbol, curr.second);
			}
		} else{ //internal node
			for(int i = 0; i <curr.first->children.size(); i++){
				string code = curr.second + to_string(i);
				stack.add({curr.first->children.get(i), code});
			}
		}
	}
}

template <int treeOrder>
std::string HuffmanTree<treeOrder>::decode(const std::string &huffmanCode)
{
    //TODO
	std::string decodeStr = "";
	HuffmanNode* curr = this->root;

	for(char bit : huffmanCode){
		int index = bit - '0';

	 	curr = curr->children.get(index);
		if(curr->children.empty()){ //leaf node
			if(curr->symbol != '\0'){
				decodeStr += curr->symbol;
			}
			curr = this->root;
		}
	}
    return decodeStr;
}

template <int treeOrder>
InventoryCompressor<treeOrder>::InventoryCompressor(InventoryManager *manager)
{
    //TODO
}

template <int treeOrder>
InventoryCompressor<treeOrder>::~InventoryCompressor()
{
    //TODO
}

template <int treeOrder>
void InventoryCompressor<treeOrder>::buildHuffman()
{
    //TODO
    	
}

template <int treeOrder>
void InventoryCompressor<treeOrder>::printHuffmanTable() {
    DLinkedList<char> keys = huffmanTable->keys();
    for (char ch : keys) {
        std::cout << "'" << ch << "' : " << huffmanTable->get(ch) << std::endl;
    }
}

template <int treeOrder>
std::string InventoryCompressor<treeOrder>::productToString(const List1D<InventoryAttribute> &attributes, const std::string &name)
{
    //TODO
    	stringstream ss;
	ss << name << ":";
	for(int i = 0; i < attributes.size(); i++){
		if(i > 0) ss << ",";

		ss << "(";
		ss << attributes.get(i).name << ":" << attributes.get(i).value;
		ss << ")";
	}

    return ss.str();
}

template <int treeOrder>
std::string InventoryCompressor<treeOrder>::encodeHuffman(const List1D<InventoryAttribute> &attributes, const std::string &name)
{
    //TODO
    return std::string();
}

template <int treeOrder>
std::string InventoryCompressor<treeOrder>::decodeHuffman(const std::string &huffmanCode, List1D<InventoryAttribute> &attributesOutput, std::string &nameOutput)
{
    //TODO
    return std::string();
}
