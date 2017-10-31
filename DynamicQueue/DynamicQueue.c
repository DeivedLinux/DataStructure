#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Element
{
	int data;
	struct Element* next;
}*ptrElement;

typedef struct Queue
{
 	ptrElement start;
 	ptrElement end;
 	unsigned size;
}*ptrQueue;

typedef struct Queue Queue;
typedef struct Element Element;

ptrQueue newQueue(void);
bool isEmpty(ptrQueue queue);
bool destroyQueue(ptrQueue queue);
bool insertQueue(ptrQueue queue, int data);
int removeQueue(ptrQueue queue);

ptrQueue newQueue(void)
{
	ptrQueue queue = NULL;

	queue = (ptrQueue)malloc(sizeof(Queue));
	if(queue != NULL)
	{
		queue->start = NULL;
		queue->end = NULL;
		queue->size = 0;
	}

	return queue;
}

bool destroyQueue(ptrQueue queue)
{
	ptrElement scroollQueue;

	if(queue == NULL)
		return false;

	if(queue->start == NULL)
	{
		free(queue);
		return true;	
	}

	while(queue->start != NULL)
	{
		scroollQueue = queue->start;
		queue->start = queue->start->next;
		free(scroollQueue);
	}
	free(queue);

	return true;
}

bool isEmpty(ptrQueue queue)
{
	if(queue == NULL)
		return true;
	if(queue->start == NULL)
		return true;

	return false;
}

bool insertQueue(ptrQueue queue, int data)
{
	ptrElement newElement = NULL;

	if(queue == NULL)
		return false;

	newElement = (ptrElement)malloc(sizeof(Element));
	if(newElement == NULL)
		return false;

	newElement->data = data;
	newElement->next = NULL;

	if(queue->start == NULL)
	{
		queue->start = newElement;
		queue->end = newElement;
		queue->size++;
	}
	else
	{
		queue->end->next = newElement;
		queue->end = newElement;
		queue->size++;
	}

	return true;
}

int removeQueue(ptrQueue queue)
{
	ptrElement resElement;
	int res;

	if(queue->start == NULL)
	{
		puts("Empty Queue");
		return 0;
	}

	resElement = queue->start;
	queue->start = queue->start->next;
	queue->size--;
	res = resElement->data;
	free(resElement);

	return res;
}

int main(int argc, char const *argv[])
{
	ptrQueue queue;

	queue = newQueue();

	insertQueue(queue,0);
	insertQueue(queue,1);
	insertQueue(queue,2);
	insertQueue(queue,3);
	insertQueue(queue,4);

	printf("%i\n",queue->size);

	printf("%i\n",removeQueue(queue));
	printf("%i\n",removeQueue(queue));
	printf("%i\n",removeQueue(queue));
	printf("%i\n",removeQueue(queue));
	printf("%i\n",removeQueue(queue));
	printf("%i\n",removeQueue(queue));

	
	return 0;
}