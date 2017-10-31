#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct DoubleList
{
	struct DoubleList* next;
	struct DoubleList* previous;
	int data;
}*ptrDoubleList;

typedef struct DoubleList DoubleList;
typedef ptrDoubleList* DoubleListHead;

DoubleListHead newList(void);
bool isEmpty(DoubleListHead listHead);
bool destroyList(DoubleListHead listHead);
bool insertSorted(DoubleListHead listHead, int data);
bool insertTopList(DoubleListHead listHead, int data);
bool insertBottomList(DoubleListHead listHead, int data);
bool removeTopList(DoubleListHead listHead);
bool removeBottomList(DoubleListHead listHead);
bool removeElement(DoubleListHead listHead, int data);
bool printList(DoubleListHead listHead);
unsigned getSizeList(DoubleListHead listHead);
bool searchList(DoubleListHead listHead, int data, int* out);

DoubleListHead newList()
{
	DoubleListHead listHead = NULL;

	listHead = (DoubleListHead)malloc(sizeof(ptrDoubleList));

	if(listHead != NULL)
		*listHead = NULL;

	return listHead;
}

bool isEmpty(DoubleListHead listHead)
{
	*listHead == NULL?true:false; 
}

bool destroyList(DoubleListHead listHead)
{
	ptrDoubleList aux;

	if(listHead == NULL || *listHead == NULL)
		return false;

	aux = *listHead;

	while(*listHead != NULL)
	{
		aux = *listHead;
		*listHead = (*listHead)->next;
		free(aux);
	}
	free(listHead);

	return true;
}

unsigned getSizeList(DoubleListHead listHead)
{
	unsigned counter = 0;
	ptrDoubleList auxNode;

	if(listHead == NULL || *listHead == NULL)
		return 0;

	auxNode = *listHead;

	while(auxNode != NULL)
	{
		counter++;
		auxNode = auxNode->next;
	}

	return counter;
}

bool insertTopList(DoubleListHead listHead, int data)
{
	ptrDoubleList newElement = NULL;

    if(listHead == NULL)
    	return false;

	newElement = (ptrDoubleList)malloc(sizeof(DoubleList));
	if(newElement == NULL)
		return false;

	newElement->data = data;
	newElement->previous = NULL;

	newElement->next = *listHead;

	if(*listHead != NULL)
		(*listHead)->previous = newElement;

	*listHead = newElement;

	return true;
}

bool insertBottomList(DoubleListHead listHead, int data)
{
	ptrDoubleList newElement = NULL;
	ptrDoubleList auxNode;

	if(listHead == NULL)
		return false;

	newElement = (ptrDoubleList)malloc(sizeof(DoubleList));
	newElement->data = data;
	newElement->next = NULL;

	if(*listHead == NULL)
	{
		*listHead = newElement;
	}
	else
	{
		auxNode = *listHead;

		while(auxNode->next != NULL)
		{
			auxNode = auxNode->next;
		}

		auxNode->next = newElement;
		newElement->previous = auxNode;
	}
	return true;
}

bool insertSorted(DoubleListHead listHead, int data)
{
	ptrDoubleList newElement = NULL;
	ptrDoubleList current;
	ptrDoubleList previous;

	if(listHead == NULL)
		return false;

	newElement = (ptrDoubleList)malloc(sizeof(DoubleList));
	newElement->data = data;

	if(*listHead == NULL)
	{
		newElement->next = NULL;
		newElement->previous = NULL;
		*listHead = newElement;
	}
	else
	{
		current = *listHead;
		while(current != NULL && current->data < data)
		{
			previous = current;
			current = current->next;
		}

		if(current == *listHead)
		{
			newElement->next = *listHead;
			(*listHead)->previous = newElement;
			*listHead = newElement;
		}
		else
		{
			newElement->next = previous->next;
			newElement->previous = previous;
			previous->next = newElement;
			if(current != NULL)
				current->previous = newElement;		
		}
	}
	return true;
}

bool removeTopList(DoubleListHead listHead)
{
	ptrDoubleList auxNode;

	if(listHead == NULL && *listHead == NULL)
		return false;

	auxNode = *listHead;
	*listHead = auxNode->next;

	if(auxNode->next != NULL)
		auxNode->next->previous = NULL;

	free(auxNode);

}

bool removeBottomList(DoubleListHead listHead)
{
	ptrDoubleList auxNode;

	if(listHead == NULL || *listHead == NULL)
		return false;

	auxNode = *listHead;

	while(auxNode->next != NULL)
	{
		auxNode = auxNode->next;
	}

	if(auxNode->previous == NULL)
		*listHead = auxNode->next;
	else
		auxNode->previous->next = NULL;

	free(auxNode);

}

bool removeElement(DoubleListHead listHead, int data)
{
	ptrDoubleList auxNode;

	if(listHead == NULL || *listHead == NULL)
		return false;

	auxNode = *listHead;

	while(auxNode != NULL && auxNode->data < data)
	{
		auxNode = auxNode->next;
	}

	if(auxNode == NULL)
		return false;

	if(auxNode->previous == NULL)
		*listHead = auxNode->next;
	else
		auxNode->previous->next = auxNode->next;

	if(auxNode->next != NULL)
		auxNode->next->previous = auxNode->previous;

	free(auxNode);

	return true;
}

bool printList(DoubleListHead listHead)
{
	ptrDoubleList auxNode;

	if(listHead == NULL && *listHead == NULL)
		return false;

	auxNode = *listHead;

	while(auxNode != NULL)
	{
		printf("%i\n", auxNode->data);
		auxNode = auxNode->next;
	}

	return true;
}

bool searchList(DoubleListHead listHead, int data, int* out)
{
	ptrDoubleList auxNode;

	if(listHead == NULL && *listHead == NULL)
		return false;

	auxNode = *listHead;

	while(auxNode != NULL)
	{
		if(auxNode->data == data)
		{
			*out = auxNode->data;
			return true;
		}
		auxNode = auxNode->next;
	}
	return false;
}

int main(int argc, char const *argv[])
{
	DoubleListHead list;

	list = newList();

	insertSorted(list,0);
	insertSorted(list,4);
	insertSorted(list,7);
	insertSorted(list,9);
	insertSorted(list,1);
	insertSorted(list,3);

	printList(list);
	
	return 0;
}