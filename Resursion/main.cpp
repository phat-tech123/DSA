#include<iostream>
#include<cstring>
#include "recursion.h"

using namespace std;

int main() {
	printArray(5);
	cout << endl;

	printPattern(16);
	cout << endl;

	int arr[] = { 10, 5, 7, 9, 15, 6, 11, 8, 12, 2 };
	cout << findMax(arr, 10) << endl;

	cout << isPalindrome("do geese see god") << endl;

	cout << findGCD(124, 32) << endl;

	printHailstone(32);
	cout << endl;

	char str[] = "2020";
	printf("%d", myArrayToInt(str, 4));
	cout << endl;

	cout << findLCM(10, 102) << endl;


}