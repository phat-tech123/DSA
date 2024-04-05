#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <stack>
#include <vector>
#include<sstream>

using namespace std;
//Question 1
int baseballScore(std::string ops);

//Question 3
std::vector<int> nextGreater(std::vector<int>& arr);

//Question 4
int evaluatePostfix(std::string expr);

//Question 5
class node {
public:
    int x, y;
    int dir;
    node(int i, int j)
    {
        x = i;
        y = j;

        // Initially direction
        // set to 0
        dir = 0;
    }
};
bool canEatFood(int maze[5][5], int fx, int fy);

//Question 6
std::string removeDuplicates(std:: string S);

//Question 7
std::vector<int> stock_span(const std::vector<int>& ns);

//Question 8
bool isValidParentheses(std::string s);