#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include "test/tc_xmap.h"
#include "test/tc_heap.h"
#include "test/tc_compressor.h"

using namespace std;

/*
void (*func_ptr[17])() = {
    hashDemo1,
    hashDemo2,
    hashDemo3,
    hashDemo4,
    hashDemo5,
    hashDemo6,
    hashDemo7,
    heapDemo1,
    heapDemo2,
    heapDemo3,
    tc_huffman1001,
    tc_huffman1002,
    tc_huffman1003,
    tc_huffman1004,
    tc_huffman1005,
    tc_compressor1001,
    tc_compressor1002
};
void (*func_ptr[3])() = {
    heapDemo1,
    heapDemo2,
    heapDemo3
};

void (*func_ptr[7])() = {
    hashDemo1,
    hashDemo2,
    hashDemo3,
    hashDemo4,
    hashDemo5,
    hashDemo6,
    hashDemo7,
};

*/

void (*func_ptr[7])() = {
    tc_huffman1001,
    tc_huffman1002,
    tc_huffman1003,
    tc_huffman1004,
    tc_huffman1005,
    tc_compressor1001,
    tc_compressor1002
};

void run(int func_idx)
{
    func_ptr[func_idx]();
}

int main(int argc, char **argv)
{
    // cout << "Assignment-2" << endl;
    if (argc == 1) {
    tc_huffman1001();
    }
    
    return 0;
}
