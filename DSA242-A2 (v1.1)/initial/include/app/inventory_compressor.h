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

// Leaf node constructor
template<int treeOrder>
HuffmanTree<treeOrder>::HuffmanNode::HuffmanNode(char s, int f)
    : symbol(s), freq(f), children() {}

// Internal node constructor
template<int treeOrder>
HuffmanTree<treeOrder>::HuffmanNode::HuffmanNode(int f, const XArrayList<HuffmanNode*>& childs)
    : symbol('|'), freq(f), children(childs) {}


template <int treeOrder>
HuffmanTree<treeOrder>::HuffmanTree()
{
}

template <int treeOrder>
HuffmanTree<treeOrder>::~HuffmanTree()
{
    //TODO
    if (this->root) {
        // Need to recursively delete all nodes
        XArrayList<HuffmanNode*> nodesToDelete;
        nodesToDelete.add(this->root);
        
        while (!nodesToDelete.empty()) {
            HuffmanNode* current = nodesToDelete.removeAt(nodesToDelete.size() - 1);
            for (int i = 0; i < current->children.size(); ++i) {
                nodesToDelete.add(current->children.get(i));
            }
            delete current;
        }
    }}


template <int treeOrder>
void HuffmanTree<treeOrder>::build(XArrayList<pair<char, int>>& symbolsFreqs)
{
    //TODO
    	auto comparator = [](HuffmanNode*& a, HuffmanNode*& b) -> int {
        	if(a->freq < b->freq) return -1;
        	if(a->freq > b->freq) return 1;
		if(a->freq == b->freq){
			if(a->symbol < b->symbol) return -1;
			if(a->symbol > b->symbol) return 1;
		}
    		return 0;
	};
    	Heap<HuffmanNode*> huffmanNodeHeap(comparator);

    	for (int i = symbolsFreqs.size() - 1; i >= 0; --i) {
		pair<char, int> p = symbolsFreqs.get(i);
	   	huffmanNodeHeap.push(new HuffmanNode(p.first, p.second));
    	}

    	int L = huffmanNodeHeap.size();
   	int n = treeOrder;
    	int cond = (L - 1) % (n - 1); 
    	int d = (cond != 0) ? (n - 1) - cond : 0;
    	for (int i = 0; i < d; ++i) {
		huffmanNodeHeap.push(new HuffmanNode('\0', 0));
    	}

   	while (huffmanNodeHeap.size() > 1) {
        	XArrayList<HuffmanNode*> children;
        	int totalFreq = 0;
        
        	for (int i = 0; i < treeOrder; i++) {
            		HuffmanNode* child = huffmanNodeHeap.pop();
            		totalFreq += child->freq;
            		children.add(child);
        	}
		huffmanNodeHeap.push(new HuffmanNode(totalFreq, children));
    	}

    	this->root = huffmanNodeHeap.pop();
}

template <int treeOrder>
void HuffmanTree<treeOrder>::generateCodes(xMap<char, std::string> &table)
{
    //TODO
    	XArrayList<HuffmanNode*> nodeStack;	
	XArrayList<std::string> strStack;
	nodeStack.add(this->root);
	strStack.add("");
	while(!nodeStack.empty() && !strStack.empty()){
		HuffmanNode* nodeCurr = nodeStack.removeAt(nodeStack.size()-1);
		std::string strCurr = strStack.removeAt(strStack.size()-1);

		if(nodeCurr->children.empty()){ //leaf node
			table.put(nodeCurr->symbol, strCurr);
		} else{ //internal node
			for(int i = nodeCurr->children.size()-1; i >= 0; i--){
				string code = strCurr + to_string(i);
				nodeStack.add(nodeCurr->children.get(i));
				strStack.add(code);
    			}
		}
	}
}
template <int treeOrder>
std::string HuffmanTree<treeOrder>::decode(const std::string &huffmanCode)
{
	std::string decodeStr = "";
	HuffmanNode* curr = this->root;

	if (huffmanCode.empty() && curr) {
		if (curr->symbol == '\0') {
			decodeStr += "\\x00";
		} else {
			decodeStr += curr->symbol;
		}
		return decodeStr;
	}

	for (char bit : huffmanCode) {
		int index = bit - '0';

		if (index < 0 || index >= curr->children.size()) {
			continue;
		}

		curr = curr->children.get(index);
		if (curr->children.empty()) { 
			if (curr->symbol == '\0') {
				decodeStr += "\\x00";
			} else {
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
    	this->invManager = new InventoryManager();
    	int n = manager->getProductNames().size();
	for(int i = 0; i < n; i++){
		this->invManager->addProduct( 	manager->getProductAttributes(i), 
						manager->getProductName(i),
						manager->getProductQuantity(i));
	}
	
    	this->tree = new HuffmanTree<treeOrder>();

   	auto hashFunc = [](char& key, int size) -> int {
        	return (int)key % size;
    	};
    	this->huffmanTable = new xMap<char, std::string>(hashFunc);
}

template <int treeOrder>
InventoryCompressor<treeOrder>::~InventoryCompressor()
{
    //TODO
    	delete this->invManager;
	if(this->tree){
		delete this->tree;
	}
	if(this->huffmanTable){
		this->huffmanTable->clear();
	}
}

template<int treeOrder>
void InventoryCompressor<treeOrder>::buildHuffman() {
	if (!invManager) return;
   	
	auto hashFunc = [](char& key, int size) -> int {
        	return (int)key % size;
    	};
    	xMap<char, int> freqMap(hashFunc);
    
    	for (int i = 0; i < this->invManager->getProductNames().size(); i++) {
        	string productStr = productToString(invManager->getProductAttributes(i), invManager->getProductName(i));
		for (char ch : productStr) {
			if (freqMap.containsKey(ch)) 
				freqMap.put(ch, freqMap.get(ch) + 1);
			else 
				freqMap.put(ch, 1);
		}
	}
    
    	XArrayList<pair<char, int>> symbolsFreqs;
    	DLinkedList<char> keys = freqMap.keys();
    	for (char key : keys) {
        	symbolsFreqs.add(make_pair(key, freqMap.get(key)));
    	}
    	this->tree->build(symbolsFreqs);
    	this->tree->generateCodes(*this->huffmanTable);
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
 	ss << std::fixed << std::setprecision(6); 
	ss << name << ":";
	for(int i = 0; i < attributes.size(); i++){
		if(i > 0) ss << ", ";

		ss << "(";
		ss << attributes.get(i).name << ": " << attributes.get(i).value;
		ss << ")";
	}

    	return ss.str();
}

template <int treeOrder>
std::string InventoryCompressor<treeOrder>::encodeHuffman(const List1D<InventoryAttribute> &attributes, const std::string &name){
	std::string productStr = productToString(attributes, name);
	std::string encodeStr = "";
	for(char ch : productStr){
		encodeStr = encodeStr + this->huffmanTable->get(ch);
	}
	return encodeStr;
}

template <int treeOrder>
std::string InventoryCompressor<treeOrder>::decodeHuffman(const std::string &huffmanCode, List1D<InventoryAttribute> &attributesOutput, std::string &nameOutput)
{
    //TODO
	std::string decodeStr = this->tree->decode(huffmanCode);

    	int colonPos = decodeStr.find(':');
    	if (colonPos == std::string::npos) {
        	return std::string();
    	}

    	nameOutput = decodeStr.substr(0, colonPos);

	std::string attributeStr = decodeStr.substr(colonPos + 1);
	int startPos = attributeStr.find('(');
	int endPos = attributeStr.find(')');

    	while (startPos != std::string::npos && endPos != std::string::npos && startPos < endPos) {
       		std::string attrString = attributeStr.substr(startPos + 1, endPos - startPos - 1);

        	colonPos = attrString.find(':');
        	if (colonPos == std::string::npos) {
            		startPos = attributeStr.find('(', endPos + 1);
            		endPos = attributeStr.find(')', endPos + 1);
            		continue;
        	}

        	std::string name = attrString.substr(0, colonPos);
        	std::string valueStr = attrString.substr(colonPos + 1);
            	double value = std::stod(valueStr);

        	startPos = attributeStr.find('(', endPos + 1);
        	endPos = attributeStr.find(')', endPos + 1);
    	}

    	return decodeStr; 
}
