#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Element
{
	struct Element* next;
	int data;
}*ptrElement;

typedef struct List
{
	ptrElement start;
	ptrElement end;
	unsigned size;
}*ptrList;

typedef struct List List;
typedef struct Element Element;

ptrList newList(void);
bool isEmpty(ptrList list);
bool removeTopList(ptrList list);
bool removeBottomList(ptrList list);
bool removeElement(ptrList list, int data);
bool insertTopList(ptrList list, int data);
bool insertBottomList(ptrList list, int data);
bool insertSorted(ptrList list, int data);
bool printList(ptrList list);
bool destroyList(ptrList list);
unsigned getSizeList(ptrList list);

ptrList newList(void)
{
	ptrList list = NULL;

	list = (ptrList)malloc(sizeof(List));
	if(list != NULL)
	{
		list->start = NULL;
		list->end = NULL;
		list->size = 0;
	}

	return list;
}

bool destroyList(ptrList list)
{
	ptrElement freeNode;

	if(list == NULL)
		return false;

	if(list != NULL)
	{
		while(list->start != NULL)
		{
			freeNode = list->start;
			list->start = list->start->next;
			free(freeNode);
		}
		free(freeNode);
	}
	return true;
}

unsigned getSizeList(ptrList list)
{
	if(list == NULL)
		return 0;

	return list->size;
}

bool insertTopList(ptrList list, int data)
{
	ptrElement newElement;

	if(list == NULL)
		return false;

	newElement = (ptrElement)malloc(sizeof(Element));
	if(newElement == NULL)
		return false;

	newElement->data = data;
	newElement->next = list->start;
	list->start = newElement;
	if(list->start == NULL)
		list->end = newElement;
	list->size++;

	return true;
}

bool insertBottomList(ptrList list, int data)
{
	ptrElement newElement;

	if(list == NULL)
		return false;

	newElement = (ptrElement)malloc(sizeof(Element));
	if(newElement == NULL)
		return false;

	newElement->data = data;
	newElement->next = NULL;
	if(list->start == NULL)
	{
		list->start = newElement;
	}
	else
	{
		list->end->next = newElement;
	}
	list->end = newElement;
	list->size++;

	return true;
}

bool insertSorted(ptrList list, int data)
{
	ptrElement newElement;
	ptrElement current;
	ptrElement previous;

	if(list == NULL)
		return false;

	newElement = (ptrElement)malloc(sizeof(Element));
	if(newElement == NULL)
		return false;

	newElement->data = data;

	if(list->start == NULL)
	{
		newElement->next = list->start;
		list->start = newElement;
		list->end = newElement;
		list->size++;
	}
	else if((list->start != NULL) && (data < list->start->data))
	{
		newElement->next = list->start;
		list->start = newElement;
		list->size++;
	}
	else if(data > list->end->data)
	{
		list->end->next = newElement;
		newElement->next = NULL;
		list->end = newElement;
		list->size++;
	}
	else
	{
		current = list->start;
		while(current != NULL && current->data < data)
		{
			previous = current;
			current = current->next;
		}
		if(current == list->start)
		{
			newElement->next = list->start;
			list->start = newElement;
		}
		else
		{
			newElement->next = previous->next;
			previous->next = newElement;
			if(current->next == NULL)
				list->end = newElement;
		}
		list->size++;
	}

	return true;
}

bool removeTopList(ptrList list)
{
	ptrElement freeNode;

	if(list == NULL)
		return false;
	if(list->start == NULL)
		return false;

	freeNode = list->start;
	list->start = freeNode->next;

	if(list->start == NULL)
		list->end = NULL;

	free(freeNode);
	list->size--;

	return true;
}

bool removeBottomList(ptrList list)
{
	ptrElement current;
	ptrElement previous;


	if(list == NULL)
		return false;
	if(list->start == NULL)
		return false;

    current = list->start;
	while(current->next != NULL)
	{
		previous = current;
		current = current->next;
	}

	if(current == list->start)
	{
		list->start = NULL;
		list->end = NULL;
	}
	else
	{
		previous->next = current->next;
		list->end = previous;
	}

	free(current);
	list->size--;

	return true;
}

bool removeElement(ptrList list, int data)
{
	ptrElement current;
	ptrElement previous;

	if(list == NULL)
		return false;
	if(list->start == NULL)
		return false;

	current = list->start;

	while(current->next != NULL && data != current->data)
	{
		previous = current;
		current = current->next;
	}
	if(current == list->start && current == list->end)
	{
		list->start = NULL;
		list->end = NULL;
	}
	else if(current == list->start)
	{
		list->start = list->start->next;
	}
	else
	{
		previous->next = current->next;
		list->end = previous;
	}
	free(current);
	list->size--;	
	
	return true;
}

bool isEmpty(ptrList list)
{
	if(list == NULL)
		return false;
	else if(list->start == NULL)
		return false;

	return true;
}

bool printList(ptrList list)
{
	ptrElement scrollElement;

	if(list == NULL)
		return false;

	scrollElement = list->start;

	while(scrollElement != NULL)
	{
		printf("%i\n", scrollElement->data);
		scrollElement = scrollElement->next;
	}

	return true;
}

int main(int argc, char const *argv[])
{
	ptrList list;

	list = newList();

	insertSorted(list,4);
	insertSorted(list,2);
	insertSorted(list,3);
	insertSorted(list,1);
	insertSorted(list,7);
	insertSorted(list,5);
	insertSorted(list,0);
 
    removeElement(list,2);
	printList(list);

	printf("\n%i\n",getSizeList(list));

	/* code */
	return 0;
}