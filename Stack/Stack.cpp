#include"Stack.h"

//Question 1
/*
You are keeping score for a basketball game with some new rules. The game consists of several rounds, where the scores of past rounds may affect future rounds' scores.

At the beginning of the game, you start with an empty record. You are given a list of strings ops, where ops[i] is the operation you must apply to the record, with the following rules:

A non-negative integer x (from 0 to 9) - record a new score of x
'+' - Record a new score that is the sum of the previous two scores. It is guaranteed there will always be two previous scores.
'D' - Record a new score that is double the previous score. It is guaranteed there will always be a previous score.
'C' - Invalidate the previous score, removing it from the record. It is guaranteed there will always be a previous score.
Finally, return the sum of all scores in the record.

For example:

ops = "52CD+"

'5' - add to the record. Record now is [5]
'2' - add to the record. Record now is [5,2]
'C' - invalid the previous score (2). Record now is [5]
'D' - Record new score that is double of previous score (5*2). Record now is [5,10]
'+' - Record a new score that is the sum of the previous two scores. Record now is [5,10,15]
Return the sum: 5+10+15 = 30
*/
int baseballScore(std::string ops) {
    std::stack<int> score;
    for (char x : ops) {
        if (x >= '0' && x <= '9') {
            score.push(x - '0');
        }
        else if (x == 'C') {
            score.pop();
        }
        else if (x == 'D') {
            score.push(score.top() * 2);
        }
        else if (x == '+') {
            int a = score.top();
            score.pop();
            int b = score.top();
            score.push(a);
            score.push(a + b);
        }
    }
    int sum = 0;
    while (!score.empty()) {
        sum += score.top();
        score.pop();
    }
    return sum;
}

//Question 3
/*
Given an array nums[] of size N having distinct elements, the task is to find the next greater element for each element of the array
Next greater element of an element in the array is the nearest element on the right which is greater than the current element.
If there does not exist a next greater of a element, the next greater element for it is -1

Note: iostream, stack and vector are already included

Constraints:
1 <= nums.length <= 10^5
0 <= nums[i] <= 10^9

Example 1:
Input:
nums = {15, 2, 4, 10}
Output:
{-1, 4, 10, -1}

Example 2:
Input:
nums = {1, 4, 6, 9, 6}
Output:
{4, 6, 9, -1, -1}
*/
std::vector<int> nextGreater(std::vector<int>& arr) {
    std::stack<int> st;
    std::vector<int> result(arr.size(), -1);
    for (int i = 0; i < arr.size(); i++) {
        while (!st.empty() && arr[i] > arr[st.top()]) {
            result[st.top()] = arr[i];
            st.pop();
        }
        st.push(i);
    }
    return result;
}

//Question 4
/*
Given string S representing a postfix expression, the task is to evaluate the expression and find the final value. Operators will only include the basic arithmetic operators like *, /, + and -.

Postfix expression: The expression of the form “a b operator” (ab+) i.e., when a pair of operands is followed by an operator.

For example: Given string S is  "2 3 1 * + 9 -". If the expression is converted into an infix expression, it will be 2 + (3 * 1) – 9 = 5 – 9 = -4.

Requirement: Write the function to evaluate the value of postfix expression.
*/
bool checkInt(std::string s) {
    for (char x : s) {
        if (x < '0' || x>'9') return 0;
    }
    return 1;
}
int evaluatePostfix(std::string expr) {
    /*TODO*/
    std::stack<int> st;
    std::stringstream ss(expr);
    std::string x;
    while (ss >> x) {
        if (checkInt(x)) {
            st.push(std::stoi(x));
        }
        else {
            if (x == " ") continue;
            int a = st.top();
            st.pop();
            int b = st.top();
            st.pop();
            switch (x[0])
            {
            case '+':
                st.push(b + a);
                break;
            case '-':
                st.push(b - a);
                break;
            case '*':
                st.push(b * a);
                break;
            case '/':
                st.push(b / a);
                break;
            default:
                break;
            }
        }
    }
    return st.top();
}

//Question 5
/*
A Maze is given as 5*5 binary matrix of blocks and there is a rat initially at the upper left most block i.e., maze[0][0] and the rat wants to eat food which is present at some given block in the maze (fx, fy). In a maze matrix, 0 means that the block is a dead end and 1 means that the block can be used in the path from source to destination. The rat can move in any direction (not diagonally) to any block provided the block is not a dead end.

Your task is to implement a function with following prototype to check if there exists any path so that the rat can reach the food or not:
bool canEatFood(int maze[5][5], int fx, int fy);

For example:
- Test:
// Maze matrix
int maze[5][5] = {
	{ 1, 0, 1, 1, 0 },
	{ 1, 1, 1, 0, 1 },
	{ 0, 1, 0, 1, 1 },
	{ 1, 1, 1, 1, 0 },
	{ 1, 0, 0, 1, 0 }
};

// Food coordinates
int fx = 1, fy = 4;

cout << canEatFood(maze, fx, fy)
- Result:
1
*/
void go(node& p, int** mark) {
    if (p.dir == 0) {
        p.y -= 1;
    }
    else if (p.dir == 1) {
        p.x -= 1;
    }
    else if (p.dir == 2) {
        p.y += 1;
    }
    else if (p.dir == 3) {
        p.x += 1;
    };
    mark[p.y][p.x] = 1;
};
void findDir(int maze[5][5], int** mark, node& p) {
    if (p.x < 0 || p.y < 0 || p.x > 4 || p.y > 4) p.dir = -1;
    // up
    if (p.y - 1 >= 0 && mark[p.y - 1][p.x] == 0 && maze[p.y - 1][p.x] == 1) { p.dir = 0; return; };
    // left
    if (p.x - 1 >= 0 && mark[p.y][p.x - 1] == 0 && maze[p.y][p.x - 1] == 1) { p.dir = 1; return; };
    // down
    if ((p.y + 1 <= 4) && (mark[p.y + 1][p.x] == 0) && (maze[p.y + 1][p.x] == 1)) { p.dir = 2; return; };
    // right
    if (p.x + 1 <= 4 && mark[p.y][p.x + 1] == 0 && maze[p.y][p.x + 1] == 1) { p.dir = 3; return; };

    p.dir = -1;
}
bool canEatFood(int maze[5][5], int fx, int fy) {
    // init 
    fx -= 1; fy -= 1;
    if (fx > 4 || fy > 4 || fx < 0 || fy < 0) return false;
    if (maze[fx][fy] == 0) return true;
    if (fx == 0 && fy == 0) return true;

    std::stack<node> s;
    node fp(0, 0); // node dau tien // footprint

    int** mark = new int* [5];
    for (int i = 0; i < 5; i++) {
        mark[i] = new int[5];
    };
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            mark[i][j] = 0;
        };
    };
    mark[0][0] = 1;
    while (1) {
        if (fp.x == fx && fp.y == fy) return true;
        findDir(maze, mark, fp);
        if (fp.dir == -1 && s.empty()) return false;
        if (fp.dir == -1) {
            s.pop();
            if (s.empty()) return false;
            fp = s.top();
            continue;
        }
        else {
            s.push(fp);
            go(fp, mark);
            s.push(fp);
        };
    };
    return true;
};


//Question 6
/*
Given a string S of characters, a duplicate removal consists of choosing two adjacent and equal letters, and removing them.

We repeatedly make duplicate removals on S until we no longer can.

Return the final string after all such duplicate removals have been made.
*/
string charToString(char c) {
    string s = "a";
    s[0] = c;
    return s;
}
string removeDuplicates(string S) {
    /*TODO*/
    stack<char> st;
    for (char x : S) {
        if (!st.empty() && st.top() == x) {
            st.pop();
        }
        else {
            st.push(x);
        }
    }
    string result = "";
    while (!st.empty()) {
        result = charToString(st.top()) + result;
        st.pop();
    }
    return result;
}

//Question 7
/*
The stock span problem is a financial problem where we have a series of daily price quotes for a stock and we need to calculate the span of the stock’s price for each day.

The span Si of the stock’s price on a given day i is defined as the maximum number of consecutive days just before the given day, for which the price of the stock on the current day is less than its price on the given day, plus 1 (for itself).

For example: take the stock's price sequence [100, 80, 60, 70, 60, 75, 85]. (See image above)

The given input span for 100 will be 1, 80 is smaller than 100 so the span is 1, 60 is smaller than 80 so the span is 1, 70 is greater than 60 so the span is 2 and so on.

Hence the output will be [1, 1, 1, 2, 1, 4, 6].



Requirement. Write a program to calculate the spans from the stock's prices.

Input. A list of whitespace-delimited stock's prices read from standard input.

Output. A list of space-delimited span values printed to standard output.

For example:
- Test:
100 80 60 70 60 75 85
- Result:
1 1 1 2 1 4 6
*/
std::vector<int> stock_span(const std::vector<int>& ns) {
    // STUDENT ANSWER
    std::stack<int> st;
    st.push(0);
    std::vector<int> S(ns.size());
    // Span value of first element is always 1
    S[0] = 1;

    // Calculate span values for rest of the elements
    for (int i = 1; i < ns.size(); i++) {
        // Pop elements from stack while stack is not
        // empty and top of stack is smaller than
        // price[i]
        while (!st.empty() && ns[st.top()] < ns[i])
            st.pop();

        // If stack becomes empty, then price[i] is
        // greater than all elements on left of it,
        // i.e., price[0], price[1], ..price[i-1].  Else
        // price[i] is greater than elements after
        // top of stack
        S[i] = (st.empty()) ? (i + 1) : (i - st.top());

        // Push this element to stack
        st.push(i);
    }
    return S;
}



//Question 8
/*
Given a string s containing just the characters '(', ')', '[', ']', '{', and '}'. Check if the input string is valid based on following rules:

Open brackets must be closed by the same type of brackets.
Open brackets must be closed in the correct order.
For example:

String "[]()" is a valid string, also "[()]".
String "[])" is not a valid string.
*/
bool isValidParentheses(string s) {
    /*TODO*/
    stack<char> st;
    for (char x : s) {
        if (x == '(' || x == '[' || x == '{') {
            st.push(x);
        }
        else {
            if (st.empty()) return 0;
            else {
                char a = st.top();
                if ((a == '(' && x == ')') || (a == '[' && x == ']') || (a == '{' && x == '}')) {
                    st.pop();
                }
                else {
                    return 0;
                }
            }
        }
    }
    return st.empty();
}