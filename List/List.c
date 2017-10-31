#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef struct List
{
	struct List* next;
	int data;
}*ptrList;

typedef ptrList* ListHead;
typedef struct List List;

ListHead newList(void);
bool isEmpty(ListHead listHead);
bool insertTopList(ListHead listHead, int data);
bool insertBottomList(ListHead listHead, int data);
bool insertSorted(ListHead listHead, int data)
bool printList(ListHead listHead);
bool removeElement(ListHead listHead, int data);
bool removeTopList(ListHead listHead);
bool removeBottomList(ListHead listHead);
unsigned getSizeList(ListHead listHead);
bool searchList(ListHead listHead, int data, int* out);

ListHead newList(void)
{
	ListHead listHead = NULL;

	listHead = (ListHead)malloc(sizeof(ptrList));

	if(listHead != NULL)
		*listHead = NULL;

	return listHead;
}

bool destroyList(ListHead listHead)
{
	ptrList node;

    if(listHead != NULL)
    {
		while(*listHead != NULL)
		{
			node = *listHead;
			*listHead = (*listHead)->next;
			free(node);
		}
		free(listHead);
	}
	else
	{
		printf("%s\n","Empty List!");
		return false;
	}

	return true;
}

bool isEmpty(ListHead listHead)
{
	return *listHead == NULL?true:false;
}

bool insertTopList(ListHead listHead, int data)
{
	ptrList newElement = NULL;

	if(listHead == NULL)
		return false;

	newElement = (ptrList)malloc(sizeof(List));
	if(newElement == NULL)
		return false;

	newElement->data = data;
	newElement->next = *listHead;
	*listHead = newElement;

	return true;
}

bool insertBottomList(ListHead listHead, int data)
{
	ptrList newElement = NULL;
	ptrList auxNode;

	if(listHead == NULL)
		return false;

	newElement = (ptrList)malloc(sizeof(List));
	if(newElement == NULL)
		return false;

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
	}

	return true;
}

bool insertSorted(ListHead listHead, int data)
{
	ptrList newElement;
	ptrList current;
	ptrList previous;

	if(listHead == NULL)
		return false;

	newElement = (ptrList)malloc(sizeof(List));
	newElement->data = data;
	newElement->next = NULL;

	if(*listHead == NULL)
	{
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
			*listHead = newElement;
		}
		else
		{
			newElement->next = previous->next;
			previous->next = newElement;
		}

	}
	return true;
}

bool removeTopList(ListHead listHead)
{
	ptrList auxNode;

	if(listHead == NULL || *listHead == NULL)
		return false;

	auxNode = *listHead;
	*listHead = auxNode->next;

	free(auxNode);

	return true;
}

bool removeBottomList(ListHead listHead)
{
	ptrList auxNode;
	ptrList previous;

	if(listHead == NULL || *listHead == NULL)
		return false;

	auxNode = *listHead;

	while(auxNode->next != NULL)
	{
		previous = auxNode;
		auxNode = auxNode->next;
	}

	if(auxNode == *listHead)
	{
		*listHead = auxNode->next; 
	}
	else
	{
		previous->next = auxNode->next;
	}

	free(auxNode);
}

bool removeElement(ListHead listHead, int data)
{
	ptrList current = NULL;
	ptrList previous = NULL;

	if(listHead == NULL || *listHead == NULL)
		return false;

	current = *listHead;

	while(current != NULL && data != current->data)
	{
		previous = current;
		current = current->next;
	}

	if(current == *listHead)
	{
		*listHead = current->next; 
	}
	else
	{
		previous->next = current->next;
	}
	free(current);

	return true;
}

unsigned getSizeList(ListHead listHead)
{
	unsigned counter = 0;
    ptrList auxNode;

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

bool searchList(ListHead listHead, int data, int* out)
{
	ptrList auxNode;
    
    if(listHead == NULL || *listHead == NULL)
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

bool printList(ListHead listHead)
{
	ptrList auxNode;

	if(listHead == NULL)
		return false;
   
    auxNode = *listHead;

	while(auxNode != NULL)
	{
		printf("%i\n",auxNode->data);
		auxNode = auxNode->next; 
	}

	return true;
}


int main(int argc, char const *argv[])
{
	ListHead list;

	unsigned i;

	list = newList();
    
    srand(time(NULL));

	for(i = 0; i < 100; i++)
	{
		if(!insertSorted(list,rand()%100))
		{
			puts("there was an error in insertion");
			break;
		}
	}
    
    printf("Size of list before remove two elements: %i\n", getSizeList(list));
	removeTopList(list);
	removeBottomList(list);

	printf("Size of list after remove two elements: %i\n", getSizeList(list));
	printList(list);

    if(!searchList(list,78,&i))
    {
    	puts("it's not on the list");
    }
    printf("%i\n",i);

    
	return 0;
}