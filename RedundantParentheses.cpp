// hw7.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <string>
#include <stack>
#include <map>
#include <iostream>
using namespace std;

bool isNum(char c) {
	return (c >= 'a' && c <= 'z');//whether it is a number
}

map<char, int> priority_infix;//create a relationship between operator and their priority
map<char, int> priority_sufix;


void InfixToSuffix(const char* source, string& result) {
	result.clear();
	string str;
	stack<char> st;
	int len = strlen(source);
	for (int i = 0; i < len; ++i)
	{
		char c = source[i];
		if (isNum(c))//if it is a number, put it into result directly
		{
			result.append(&c, 1);
		}
		else
		{
			switch (c)
			{
			case ')':
			{
				while (st.top() != '(') //put out things inside a pair of parentheses
				{
					result.append(&st.top(), 1);
					st.pop();
				}
				st.pop();//parentheses will not be written into stack
				break;
			}
			case'('://put the left parentheses into stack
			{
				st.push(c);
				break;
			}
			default://deal with operators
			{
				while (!st.empty() && priority_infix[st.top()] >= priority_infix[c])//if the priority of the top is larger than c, pop it out
				{
					result.append(&st.top(), 1); st.pop();
				}
				st.push(c);
				break;
			}

			}
		}
	
	}
	while (!st.empty())//pop the remaining things in stack
	{ 
		result.append(&st.top(), 1); 
		st.pop();
	}
}

typedef struct ITEM
{
	string str;
	int op;//store a string and its priority
	ITEM(string str) : str(str), op(0x7fffffff) {}//two ways to initialize an item//ensure that priority of number is larger than operator
	ITEM(string str, int op) : str(str), op(op) {}
}ITEM;


void SuffixToInfix(const char* source, string& result) {
	stack<ITEM> st;
	string  str, tmp1, tmp2;
	int len = strlen(source);
	for (int i = 0; i < len; ++i) 
	{
		char c = source[i];
		if (isNum(c)) //if it is a number, put it into stack
		{
			string str;
			str.assign(&c, 1);
			st.push(str);
		}
		else 
		{
			if (st.top().op < priority_sufix[c] || ((st.top().op == priority_sufix[c]) && (c == '-' || c == '/')))//if the priority of c is smaller than top or equal but it is '/' or '-'
			{//a-b-c !=a-(b-c)
				tmp2 = "(" + st.top().str + ")";//put it into parentheses
			}
			else
			{
				tmp2 = st.top().str;//right part of the expression
			}
			st.pop();
			if (st.top().op < priority_sufix[c])//a-b-c==(a-b)-c
			{
				tmp1 = "(" + st.top().str + ")";
			}
			else
			{
				tmp1 = st.top().str;//left part of expression
			}
			st.pop();
			tmp1.append(&c, 1);//add operator
			tmp1 += tmp2;//stick them together
			ITEM item(tmp1, priority_sufix[c]);//the priority of expression is the same as the operator
			st.push(item);//push expreesion into stack
		}
	}
	result.assign(st.top().str);//write expression into result
}

int main() {
	priority_infix['+'] = 1; priority_infix['-'] = 1; priority_infix['*'] = 2; priority_infix['/'] = 2; priority_infix['('] = 0; priority_infix[')'] = 0;
	priority_sufix['+'] = 1; priority_sufix['-'] = 1; priority_sufix['*'] = 2; priority_sufix['/'] = 2; priority_sufix['('] = 0; priority_sufix[')'] = 0;
	string str, suffix, infix;
	cin >> str;
	InfixToSuffix(str.c_str(), suffix);
	SuffixToInfix(suffix.c_str(), infix);
	cout << infix;
	
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
