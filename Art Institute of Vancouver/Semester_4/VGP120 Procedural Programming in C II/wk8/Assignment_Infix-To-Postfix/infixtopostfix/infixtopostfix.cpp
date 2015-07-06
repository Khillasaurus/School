//--------------------------------
// File:		infixtopostfix.cpp
// Created:		2012/05/10
// Copyright:	Daniel Schenker
//--------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cctype>

struct cNode
{
	char data;
	cNode* beneath;
};

//=---Function Prototypes---=
 //-Program Specific-
void ToPostfix(char*&, const int, char*&, const int, cNode*&);	//Original Function Prototype: void convertToPostfix(char infix[], char postfix[]);
bool IsOp(const char);											//Original Function Prototype: int isOperator(char c);
int OpPrecedenceVal(const char);
int OpPrecedence(const char, const char);						//Original Function Prototype: int precedence(char operator1, char operator2);
//void push(StackNode** topPtr, char value);					//Use Utility: Stack Push() functions instead
//char pop(StackNode** topPtr);									//Use Utility: Stack Pop() function instead
char StackTop(const cNode* const);								//Original Function Prototype: char stackTop(StackNode* topPtr);
//int isEmpty(StackNode* topPtr);								//Use Utility: Stack IsEmpty() function instead
//void printStack(StackNode* topPtr);							//Use Utility: Stack PrintStack() function instead
 //-Utility: Stack-
void Push(cNode*&);
void Push(cNode*&, const char);
void Pop(cNode*&);
void PrintStack(cNode*);
int StackLength(cNode* const);
bool IsEmpty(const cNode* const);
void CleanUp(cNode* pTop);

int main()
{
	const int kBufLen = 128;
	char infix[kBufLen] = "";
	char* pInfix = &infix[0];
	char postfix[kBufLen] = "";
	char* pPostfix = &postfix[0];
	cNode* pTop = NULL;

	printf("Using the following operands only: + - * / % ( ) and no spaces,\n");
	printf("enter the arithmetic expression in infix notation:\n");
	scanf("%s", &infix);

	ToPostfix(pInfix, kBufLen, pPostfix, kBufLen, pTop);

	printf("The expression in postfix notation: %s\n", postfix);
	
	CleanUp(pTop);

	return 0;
}

//Program Specific-------------------------------------------------------------

void ToPostfix(char*& pInfix, const int kBufLenOfInfix, char*& pPostfix, const int kBufLenOfPostfix, cNode*& pStack)
{
	int infixPos = 0;
	char hold[2] = "";
	char* pHold = &hold[0];

	 //Being Algorithm:
	//1) Push a left parenthesis onto the stack
	Push(pStack, '(');
	//2) Append a right parenthesis to the end of infix
	strcat(pInfix, ")");
	//3) While the stack is not empty, read infix from left to right and do the following:
	while(pStack)
	{
		//3.1a) If the current character in infix is a digit
		if(isdigit(pInfix[infixPos]))
		{
			//3.1b) Copy current character to next element of postfix
			pHold[0] = pInfix[infixPos];
			pHold[1] = '\0';
			strcat(pPostfix, pHold);
		}
		//3.2a) If the current character in infix is a left parenthesis
		else if(pInfix[infixPos] == '(')
		{
			//3.2b) Push the current character onto the stack
			Push(pStack, '(');
		}
		//3.3a) If the current character in infix is an operator
		else if(IsOp(pInfix[infixPos]))
		{
			//3.3b) Pop operators (if there are any) at the top of the stack
			// while they have equal or higher precedence than the current operator
			while(OpPrecedence(StackTop(pStack), pInfix[infixPos]) > -1)
			{
				//3.3c) Insert the popped operators in postfix
				pHold[0] = StackTop(pStack);
				pHold[1] = '\0';
				strcat(pPostfix, pHold);
				Pop(pStack);
			}
			//3.3d) Push the current character in infix onto the stack
			Push(pStack, pInfix[infixPos]);
		}
		//3.4a) If the current character in infix is a right parenthesis
		else if(pInfix[infixPos] == ')')
		{
			//3.4b) Until a left parenthesis is at the top of the stack
			while(StackTop(pStack) != '(')
			{
				//Insert operator into postfix
				pHold[0] = StackTop(pStack);
				pHold[1] = '\0';
				strcat(pPostfix, pHold);
				//Pop operators from the top of the stack
				Pop(pStack);
			}
			//3.4c) Pop the left parenthesis from the stack
			Pop(pStack);
		}
		++infixPos;
	}
}

bool IsOp(const char testOp)
{
	if(testOp == '+' || testOp == '-' || testOp == '*' || testOp == '/' || testOp == '%')
	{
		return true;
	}
	else
	{
		return false;
	}
}

int OpPrecedenceVal(const char op)
{
	int value = -1;

	if(op == '+' || op == '-')
	{
		value = 1;
	}
	else if(op == '*' || op == '/')
	{
		value = 2;
	}
	else if(op == '*' || op == '/' || op == '%')
	{
		value = 3;
	}

	return value;
}

//Determine if the precedence
int OpPrecedence(const char opFirst, const char opSecond)
{
	int opA = OpPrecedenceVal(opFirst);
	int opB = OpPrecedenceVal(opSecond);

	if(opA < opB)
	{
		return -1;
	}
	else if(opA == opB)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

char StackTop(const cNode* const pTop)
{
	//If the stack is empty
	if(!pTop)
	{
		printf("ERROR:\tCould not return top value of stack as the stack is empty.\n");
		printf("\t\tPlease check if the stack is empty first by using the IsEmpty(const cNode* const) function.\n");
		printf("- StackTop(cNode*& pTop)\n)");
	}
	else
	{
		return pTop->data;
	}
	return '\0';
}

//Utility: Stack---------------------------------------------------------------

void Push(cNode*& pTop)
{
	cNode* pTemp = (cNode*)malloc(sizeof(cNode));
	pTemp->beneath = pTop;
	pTop = pTemp;

	printf("Enter the char that you would you like to add:\n");
	scanf_s("%c", &(pTop->data));
}

void Push(cNode*& pTop, const char value)
{
	cNode* pTemp = (cNode*)malloc(sizeof(cNode));
	pTemp->beneath = pTop;
	pTop = pTemp;
	pTop->data = value;
}

void Pop(cNode*& pTop)
{
	//If the stack is empty
	if(!pTop)
	{
		printf("ERROR: Could not pop from the top of the stack as the stack pointer equals NULL. - Pop(cNode*& pTop)\n");
	}
	else
	{
		cNode* pTemp = pTop->beneath;
		free(pTop);
		pTop = pTemp;
	}
}

int StackLength(cNode* const pTop)
{
	cNode* pTemp = pTop;
	int stackLength = 0;

	//while pTemp has not reached the bottom of the stack
	while(pTemp)
	{
		++stackLength;
		//if pTemp is not at the bottom of the stack
		if(pTemp->beneath)
		{
			pTemp = pTemp->beneath;
		}
		else
		{
			return stackLength;
		}
	}
	return stackLength;
}

void PrintStack(cNode* const pTop)
{
	cNode* pTemp = pTop;
	bool isEmpty = true;

	printf("The stack:");
	if(!pTemp)
	{
		if(isEmpty)
		{
			printf(" empty.\n");
		}
		return;
	}
	else
	{
		isEmpty = false;
		printf("\n");
	}

	//while pTemp is not pointing to the bottom of the stack
	while(pTemp->beneath)
	{
		printf("%c\n", pTemp->data);
		pTemp = pTemp->beneath;
	}
	printf("%c\n", pTemp->data);
}

bool IsEmpty(const cNode* const pTop)
{
	//If the stack exists
	if(pTop)
	{
		return false;
	}
	else//the stack is empty
	{
		return true;
	}
}

void CleanUp(cNode* pTop)
{
	cNode* pTemp;

	//while the stack is not empty
	while(pTop)
	{
		pTemp = pTop;
		pTop = pTop->beneath;
		free(pTemp);
	}
}