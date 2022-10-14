//Author: Adam Princiotta
/*
 * expression.cc - Implementation of a class representing simple arithmetic
 *                 expressions, as declared in expression.h.  Part of CPS222
 *                 Project 2.
 *
 * Skeleton copyright (c) 2001, 2013 - Russell C. Bjork
 *
 */

#include <stack>
#include <iostream>
#include <string>
#include "expression.h"
#include <ctype.h>
using std::cin;
using std::cout;
using std::endl;
using std::stack;
using std::string;



//Converts a given infix expressions to postfix and returns it as a string
string Expression::convertToPostfix(string infix) throw (SyntaxError)
{ 
	string post;
	stack <char> ops;
	stack <int> ints;
	int length = infix.length();
	
	for(int i = 0; i < length; i++){
	
		if(isdigit(infix[i])){
			post += infix[i];
		}

		else if(infix[i] == '('){
			ops.push(infix[i]);
		}

		else if(infix[i] == ')'){
			while(ops.top() != '('){
				post += ops.top();
				ops.pop();
			}
			ops.pop();
		}

		else {
			while(!ops.empty() && precedence(infix[i]) <= precedence(ops.top())){
				post += ops.top();
				ops.pop();
			}
			ops.push(infix[i]);
		}
	}	

	while(!ops.empty()){
			post += ops.top();
			ops.pop();
		}

	return post; 
	
}

//Returns the precedence of operations to help convertToPostfix decide the positioning of
//operations
int Expression::precedence(char op){
	if(op == '('){
		return 0;
	}
	
	else if(op == '+' || op == '-'){
		return 1;
	}
	
	else if (op == '*' || op == '/'){
		return 2;
	}
	
	else{
		return -1;
	}
}

//Evaluates the postfix expression and returns the integer value
int Expression::evaluate(string postfix) throw (DivideByZeroError)
{ 
	stack <char> ops;
	stack <int> ints;
	int length = postfix.length();
	int firstOff;
	int secondOff;	


	for(int i = 0; i < length; i++){
		if(isdigit(postfix[i])){
			//substract ascii 0 to get integer value
			ints.push(postfix[i] - '0');
		}
		
		else{
			firstOff = ints.top();
			ints.pop();
			secondOff = ints.top();
			ints.pop();
			
			if(postfix[i] == '+'){
				ints.push(firstOff + secondOff);
			}
			
			else if(postfix[i] == '*'){
				ints.push(firstOff * secondOff);
			}
			
			else if(postfix[i] == '-'){
				ints.push(secondOff - firstOff);
			}			
			
			else if(postfix[i] == '/' && firstOff != 0){
				ints.push(secondOff / firstOff);
			}
			
			else if(postfix[i] == '/' && firstOff == 0){
				throw(DivideByZeroError(i));
			}
				
		}
	}

	return ints.top();
}        

//Converts a given postfix expression to prefix
string Expression::convertToPrefix(string postfix)
{
	string pre;
	int operandsNeeded = 1;
	
	
	if(isdigit(postfix[postfix.length() - 1])){
		//stores as string instead of char
		pre = postfix[postfix.length() - 1];
		return pre;
	}
	
	else if(!isdigit(postfix[postfix.length() - 1])){
		char lastOp = postfix[postfix.length() - 1];
		for(int i = postfix.length() - 2; i > 0; i--){
			if(isdigit(postfix[i])){
				operandsNeeded--;
			}
			
			else{
				operandsNeeded++;
			}
			
			if(operandsNeeded == 0){
				return lastOp + convertToPrefix(postfix.substr(0, i)) + 				convertToPrefix(postfix.substr(i, postfix.length() - i - 1)); 
			}	
		}
	}	

}






