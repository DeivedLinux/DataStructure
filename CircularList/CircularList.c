#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>



typedef struct CircularList
{
	struct CircularList* next;
	int data;
}*ptrCircularList;

typedef ptrCircularList* ListHead;
typedef struct CircularList List;


ListHead newList(void);
bool isEmpty(ListHead listHead);
bool destroyList(ListHead listHead);
bool insertTopList(ListHead listHead, int data);
bool insertBottomList(ListHead listHead, int data);
bool insertSorted(ListHead listHead, int data);
bool removeTopList(ListHead listHead);
bool removeBottomList(ListHead listHead);
bool removeElement(ListHead listHead, int data);
bool printList(ListHead listHead);

ListHead newList(void)
{
	ListHead listHead = NULL;

	listHead = (ListHead)malloc(sizeof(ptrCircularList));
	if(listHead != NULL)
		*listHead = NULL;

	return listHead;
}

bool isEmpty(ListHead listHead)
{
	if(listHead == NULL || *listHead == NULL)
		return true;
	return false;
}

bool destroyList(ListHead listHead)
{
	ptrCircularList freeNode;
	ptrCircularList scrollList;

	if(listHead == NULL && *listHead == NULL)
		return false;

	if(listHead != NULL && *listHead == NULL)
	{
		free(listHead);
		return true;
	}

	scrollList = *listHead;

	while(*listHead != scrollList->next)
	{
		freeNode = scrollList;
		scrollList = scrollList->next;
		free(freeNode);
	}
	free(freeNode);
	free(listHead);

	return true;
}

bool insertTopList(ListHead listHead, int data)
{
	ptrCircularList newElement = NULL;
	ptrCircularList scrollList;

	if(listHead == NULL)
		return false;

	newElement = (ptrCircularList)malloc(sizeof(List));
	if(newElement == NULL)
	{
		puts("Memory Allocation Error");
		return false;
	}
	if(*listHead == NULL)
	{
		newElement->data = data;
		newElement->next = newElement;
		*listHead = newElement;
	}
	else
	{
		scrollList = *listHead;

		while(scrollList->next != *listHead)
			scrollList = scrollList->next;

		scrollList->next = newElement;
		newElement->next = *listHead;
		*listHead = newElement;
	}

	return true;
}

bool insertBottomList(ListHead listHead, int data)
{
	ptrCircularList newElement = NULL;
	ptrCircularList scrollList;

	if(listHead == NULL)
		return false;

	newElement = (ptrCircularList)malloc(sizeof(List));
	if(newElement == NULL)
	{
		puts("Memory Allocation Error");
		return false;
	}
	newElement->data = data;

	if(*listHead == NULL)
	{
		newElement->next = newElement;
		*listHead = newElement;
	}
	else
	{
		scrollList = *listHead;
		while(scrollList->next != *listHead)
			scrollList = scrollList->next;

		scrollList->next = newElement;
		newElement->next = *listHead;
	}
	return true;
}

bool insertSorted(ListHead listHead, int data)
{
	ptrCircularList newElement = NULL;
	ptrCircularList scrollList;
	ptrCircularList current;
	ptrCircularList previous;

	if(listHead == NULL)
		return false;

	newElement = (ptrCircularList)malloc(sizeof(List));
	if(newElement == NULL)
	{
		puts("Memory Allocation Error");
		return false;
	}

	newElement->data = data;

	if(*listHead == NULL)
	{
		newElement->next = newElement;
		*listHead = newElement;
	}
	else
	{
		scrollList = *listHead;
		if((*listHead)->data > data)
		{
			while(scrollList->next != *listHead)
				scrollList = scrollList->next;

			newElement->next = *listHead;
			scrollList->next = newElement;
			*listHead = newElement;

			return true;
		}

		current = (*listHead)->next;
		previous = *listHead;

		while(current != *listHead && current->data < data)
		{
			previous = current;
			current = current->next;
		}

		previous->next = newElement;
		newElement->next = current;
	}

	return true;
}

bool removeTopList(ListHead listHead)
{
	ptrCircularList scrollList;
	ptrCircularList freeNode;

	if(listHead == NULL || *listHead == NULL)
		return false;

	if((*listHead)->next = *listHead)
	{
		free(*listHead);
		*listHead = NULL;
	}
	else
	{
		scrollList = *listHead;

	
		while(scrollList->next != *listHead)
			scrollList = scrollList->next;

		freeNode = *listHead;
		scrollList->next = freeNode->next;
		*listHead = freeNode->next;

		free(freeNode);
	}

	return true;
}

bool removeBottomList(ListHead listHead)
{
	ptrCircularList current;
	ptrCircularList previous;
	ptrCircularList freeNode;

	if(listHead == NULL || *listHead == NULL)
		return false;

	if((*listHead)->next == *listHead)
	{
		free(*listHead);
		*listHead = NULL;
	}
	else
	{
		current = *listHead;

		while(current->next != *listHead)
		{
			previous = current;
			current = current->next;
		}

		previous->next = current->next;
	}
	return true;
}

bool removeElement(ListHead listHead, int data)
{
	ptrCircularList current;
	ptrCircularList previous;
	ptrCircularList freeNode;

	if(listHead == NULL || *listHead == NULL)
		return false;

	current = *listHead;

	if(current->data == data)
	{
		if(current == current->next)
		{
			free(*listHead);
			*listHead = NULL;
		}
		else
		{
			while(current->next != *listHead)
			{
				current = current->next;
			}
			freeNode = *listHead;
			current->next = freeNode->next;
			*listHead = freeNode->next;
			free(freeNode);
		}
	}
	else
	{ 
		previous = current;
		current = current->next;

		while(current != *listHead && current->data != data)
		{
			previous = current;
			current = current->next;
		}

		if(current == *listHead)
			return false;

		previous->next = current->next;
		free(current);
	}

	return true;
}

bool printList(ListHead listHead)
{
	ptrCircularList scrollList;

	if(listHead == NULL || *listHead == NULL)
		return false;

	scrollList = *listHead;

	do
	{
		printf("%i\n",scrollList->data);
		scrollList = scrollList->next;
	}while(scrollList->next != (*listHead)->next);
	
	return true;
}

int main(int argc, char const *argv[])
{
	ListHead list;

	list = newList();

	insertSorted(list,3);
	insertSorted(list,1);
	insertSorted(list,4);
	insertSorted(list,2);
	insertSorted(list,0);

	removeElement(list,0);
	printList(list);

	return 0;
}