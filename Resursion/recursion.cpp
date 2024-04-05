#include "recursion.h"

//Question 1
void printArray(int n) {
	if (n == 0) {
		cout << n;
	}
	else {
		printArray(n - 1);
		cout << ", " << n;
	}
}

//Question 2
void printPattern(int n) {
	if (n <= 0) {
		cout << n;
	}
	else {
		cout << n << " ";
		printPattern(n - 5);
		cout << " " << n;
	}
}

//Question 3
int findMax(int* arr, int length) {
	if (length == 0) return arr[0];

	if (arr[length - 1] > arr[0]) 
		swap(arr[length - 1], arr[0]);

	return findMax(arr, length - 1);
}

//Question 4
bool isPalindrome(string str) {
	if (str.length() <= 1) 
		return 1;
	if (str[0] == ' ') 
		return isPalindrome(str.substr(1));
	if (str[str.length() - 1] == ' ') 
		return isPalindrome(str.substr(0, str.length() - 1));
	if (str[str.length() - 1] != str[0]) 
		return 0;
	return isPalindrome(str.substr(1, str.length() - 2));
}

//Question 5
int findGCD(int a, int b) {
	if (b == 0) 
		return a;
	return findGCD(b, a % b);
}

//Question 6
string expand(string s) {

}

//Question 7
void printHailstone(int number) {
	if (number == 1) {
		cout << number;
		return;
	}
	cout << number << " ";
	if (number % 2 == 0)
		return printHailstone(number / 2);
	else
		return printHailstone(number * 3 + 1);
}

//Question 8
int myArrayToInt(char* str, int n) {
	if (n == 1) return str[0] - '0';
	return (str[0] - '0') * pow(10, n - 1) + myArrayToInt(str + 1, n - 1);
}

//Questions 9
int findLCM(int a, int b) {
	return a * b / findGCD(a, b);
}

//Question 10

//Question 11
string reverseFromArray(string arr[]) {

}
string reverseSentence(string s) {
	string tmp = "";
	if (s[s.length() - 1] != ' ') {

	}
}

//Question 12
int strLen(char* str) {
	if (*str == '\0') return 0;
	return 1 + strLen(str + 1);
}