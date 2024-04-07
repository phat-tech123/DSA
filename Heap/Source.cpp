#include "Heap.h"

int main() {

	int arr[] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 };
	int size = sizeof(arr) / sizeof(arr[0]);
	reheapUp(arr, size, 13);
	reheapUp(arr, size, 12);
	cout << "[ ";
	for (int i = 0; i < size; i++)
		cout << arr[i] << " ";
	cout << "]";
	

	
	//7
	vector<int> nums{ 2, 3, 5, 7 };
	int k = 3;
	cout << leastAfter(nums, k);
}