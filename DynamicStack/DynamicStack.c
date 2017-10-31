#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define INFINITE 2147483648u


typedef struct Element
{
	struct Element* next;
	int data;
}*ptrElement;

typedef struct Stack
{
	ptrElement array;
	ptrElement top;
}*ptrStack;

typedef struct Stack Stack;
typedef struct Element Element;

ptrStack newStack(void);
bool insertDataStack(ptrStack stack, int data);
bool isEmpty(ptrStack stack);
int removeDataStack(ptrStack stack);

ptrStack newStack(void)
{
	ptrStack stack = NULL;

	stack = (ptrStack)malloc(sizeof(Stack));
	if(stack != NULL)
	{
		stack->array = NULL;
		stack->top = NULL;
	}

	return stack;
}

bool isEmpty(ptrStack stack)
{
	if(stack == NULL)
		return true;
	if(stack->top == NULL)
		return true;

	return false;
}

bool insertDataStack(ptrStack stack, int data)
{
	ptrElement newElement = NULL;

    if(stack == NULL)
    	return false;

	newElement = (ptrElement)malloc(sizeof(Element));
	if(newElement == NULL)
		return false;
	newElement->data = data;

	newElement->next = stack->array;
	stack->array = newElement;
	stack->top = stack->array;

	return true;
}

int removeDataStack(ptrStack stack)
{
	int res;
	ptrElement element;

	if(stack == NULL)
	{
		puts("Stack not created");
		return INFINITE;
	}
	if(stack->top == NULL)
	{
		puts("Stack is Empty");
		return INFINITE;
	}

	element = stack->top;
	res = stack->top->data;
	stack->array = stack->array->next;
	stack->top = stack->array;
	free(element);

	return res;
}

int main(int argc, char const *argv[])
{
	ptrStack stack;

	stack = newStack();

	insertDataStack(stack,0);
	insertDataStack(stack,1);
	insertDataStack(stack,2);
	insertDataStack(stack,3);
	insertDataStack(stack,4);

	printf("%i\n",removeDataStack(stack));
	printf("%i\n",removeDataStack(stack));
	printf("%i\n",removeDataStack(stack));
	printf("%i\n",removeDataStack(stack));
	printf("%i\n",removeDataStack(stack));
    printf("%i\n",removeDataStack(stack));
	

	return 0;
}