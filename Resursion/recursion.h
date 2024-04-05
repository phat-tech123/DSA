#include<iostream>
#include<cstring>

using namespace std;

/*
Please note that you can't using key work for, while, goto (even in variable names, comment).

For this exercise, we have #include <iostream> and using namespace std;
*/

//Question 1
void printArray(int n);
//to print 0, 1, 2, ..., n (n is positive integer and has no space at the end).

//Question 2
void printPattern(int n);
//We basically first reduce 5 one by one until we reach a negative or 0. After we reach 0 or negative, we one add 5 until we reach n.

//Question 3
int findMax(int* arr, int length);
//to find the largest element using recursion (with length is the number of elements in integer array arr).

//Question 4
bool isPalindrome(string str);
//to check if the given non empty string is palindrome, else not palindrome using recursion.

//Question 5
int findGCD(int a, int b);
//to find GCD (Greatest Common Divisor) of a and b using recursion.

//Question 6
string expand(string s);
/*
String s contains lowercase letters, digits, "(" and ")", satisfying the following rules:

- Two digits cannot be adjacent.

- Two "(" cannot be adjacent.

- One "(" and one ")" cannot be adjacent.

- After any digit, there must be "(".

- The quantities of "(" and ")" are equal.

Change string s until new string t created, t contains only lowercase letters. These are changing rules:

- Sub-strings with form "n(p)", can change to "pp...p" (n times p), where n is a digit and p is a string.

- If p still contains "(", ")" or digits, continue to implement the above changing method.  
*/

//Question 7
void printHailstone(int number);
/*
to print the Hailstone Sequence of a given number upto 1 (no space at the end).

Hailstone Sequences follow these rules: 

If a number is even, divide it by 2 
If a number is odd, multiply it by 3 and add 
*/

//Question 8
int myArrayToInt(char* str, int n);
//takes a string str (which represents an positive decimal number), n is the number of elements in the string as arguments and returns its value.

//Question 9
int findLCM(int a, int b);
//to find LCM (Lowest Common Multiple) of a and b using recursion.

//Question 10
int mininumBracketAdd(string s);
/*
The function returns the mininum number of brackets needed to be inserted to s so that the brackets are balanced.

More info:
A sequence of brackets is balanced when there are no unmatched brackets.
Example: ()(()) is balanced, but ))() is not.
*/

//Question 11
string reverseSentence(string s);
/*
The function returns the reverse sentence of sentence s.
The testcases ensure that there is only one space character between two adjacent words, and the sentences do not begin or end with any space characters.

Example:
- Test:
cout << reverseSentence("data structure and algorithm is scary");
- result:
scary is algorithm and structure data
*/

//Question 12
int strLen(char* str);
//to calculate length of the string using recursion.



