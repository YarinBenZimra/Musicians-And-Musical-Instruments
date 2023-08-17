#include "LIST.h"

//Musician's Instruments List Functions
void makeEmptyList(MPIList* lst) // Make A leagal List.
{
    lst->head = NULL;
    lst->tail = NULL;
}

ListNode* createNewListNode(float price, short unsigned insId, ListNode* next) // Create New Node
{
    ListNode* res;
    res = (ListNode*)malloc(sizeof(ListNode));
    checkMemoryAllocation(res);
    res->MPinstrument = (MusicianPriceInstrument*)malloc(sizeof(MusicianPriceInstrument));
    checkMemoryAllocation(res->MPinstrument);
    res->MPinstrument->insId = insId;
    res->MPinstrument->price = price;
    res->next = next;
    return res;
}

void insertDataToEndList(MPIList* lst, float price, short unsigned insId) // Insert Data To End Of List.
{
    ListNode* newTail;
    newTail = createNewListNode(price, insId, NULL);
    insertNodeToEndList(lst, newTail);
}

void insertNodeToEndList(MPIList* lst, ListNode* tail) // Insert Node To End
{
    if (isEmptyList(lst) == true)
        lst->head = lst->tail = tail;
    else
    {
        lst->tail->next = tail;
        lst->tail = tail;
    }
    tail->next = NULL;
}

bool isEmptyList(MPIList* lst) // Check If Empty List.
{
    if (lst->head == NULL)
        return true;
    else
        return false;
}

void freeList(MPIList* lst)
{
    ListNode* curr = lst->head;
    ListNode* saver;
    while (curr != NULL)
    {
        saver = curr->next;
        free(curr->MPinstrument);
        free(curr);
        curr = saver;
    }
    lst->head = NULL;
    lst->tail = NULL;
}

//Instrument's List Functions
void makeEmptyCIList(CIList* lst)
{
	lst->head = NULL;
	lst->tail = NULL;
}

void insertDataToEndCIList(CIList* lst, char importance, int num, int inst)
{
	CIListNode* newTail;
	newTail = createNewCIListNode(importance, num, inst, NULL);
	insertNodeToEndCIList(lst, newTail);
}

void insertNodeToEndCIList(CIList* lst, CIListNode* tail)
{
	if (isEmptyCIList(lst) == true)
		lst->head = lst->tail = tail;
	else
	{
		lst->tail->next = tail;
		lst->tail = tail;
	}
	tail->next = NULL;

}

CIListNode* createNewCIListNode(char importance, int num, int inst, CIListNode* next)
{
	CIListNode* res;
	res = (CIListNode*)malloc(sizeof(CIListNode));
	checkMemoryAllocation(res);
	res->CIinstrument = (ConcertInstrument*)malloc(sizeof(ConcertInstrument));
	checkMemoryAllocation(res->CIinstrument);
	res->CIinstrument->inst = inst;
	res->CIinstrument->num = num;
	res->CIinstrument->importance = importance;
	res->next = next;
	return res;
}

bool isEmptyCIList(CIList* lst)
{
	if (lst->head == NULL)
		return true;
	else
		return false;
}

void freeCIList(CIList* lst)
{
	CIListNode* curr = lst->head;
	CIListNode* saver;
	while (curr != NULL)
	{
		saver = curr->next;
		free(curr->CIinstrument);
		free(curr);
		curr = saver;
	}
	lst->head = NULL;
	lst->tail = NULL;
}

//Concert Musician's List Functions
void makeEmptyCMList(ConcertMusiciansList* lst)
{
	lst->head = NULL;
	lst->tail = NULL;
}

void insertDataToEndCMList(ConcertMusiciansList* lst, Musician* musician, int insId)
{
	CMListNode* newTail;
	newTail = createNewCMListNode(musician, NULL, insId);
	insertNodeToEndCMList(lst, newTail);
}

void insertNodeToEndCMList(ConcertMusiciansList* lst, CMListNode* tail)
{
	if (isEmptyCMList(lst) == true)
		lst->head = lst->tail = tail;
	else
	{
		lst->tail->next = tail;
		lst->tail = tail;
	}
	tail->next = NULL;

}

CMListNode* createNewCMListNode(Musician* musician, CMListNode* next, int insId)
{
	CMListNode* res;
	res = (CMListNode*)malloc(sizeof(CMListNode));
	checkMemoryAllocation(res);
	res->musician = musician;
	res->next = next;
	res->InsIdForCurrShow = insId;
	return res;
}

bool isEmptyCMList(ConcertMusiciansList* lst)
{
	if (lst->head == NULL)
		return true;
	else
		return false;
}

void freeCMList(ConcertMusiciansList* lst)
{
	CMListNode* curr = lst->head;
	CMListNode* saver;
	while (curr != NULL)
	{
		saver = curr->next;
		free(curr);
		curr = saver;
	}
	lst->head = NULL;
	lst->tail = NULL;
}


