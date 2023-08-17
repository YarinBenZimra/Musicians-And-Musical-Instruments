#ifndef List_H
#define List_H

#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


typedef struct musicianpriceinstrument
{
    short unsigned insId;
    float price;
} MusicianPriceInstrument;

// Instrument's List Struct

typedef struct listNode 
{
    MusicianPriceInstrument* MPinstrument;
    struct listNode* next;
}ListNode;

typedef struct MPIList
{
    ListNode* head;
    ListNode* tail;
}MPIList;

typedef struct musician
{
    char** name;
    int name_log_size;
    MPIList instruments;
    bool Available;
} Musician;

typedef struct instrument
{
    Musician** Who_Play_On_Specific_Instrument;
    int SizeOfArr;
} Instrument;

typedef struct concertinstrument
{
	int num;
	int inst;
	char importance;
} ConcertInstrument;

//Concert instrument's List Struct

typedef struct CIlistnode {
	ConcertInstrument* CIinstrument;
	struct CIListNode* next;
}CIListNode;

typedef struct CIlist
{
	CIListNode* head;
	CIListNode* tail;
}CIList;

//Concert Musician's List Struct

typedef struct CMlistnode 
{
	Musician* musician;
	int InsIdForCurrShow;
	struct CMlistnode* next;
}CMListNode;

typedef struct concertmusicianslist
{
	CMListNode* head;
	CMListNode* tail;
}ConcertMusiciansList;


// Musician instrument's List Signature
void makeEmptyList(MPIList* lst);

void insertDataToEndList(MPIList* lst, float price, short unsigned insId);

ListNode* createNewListNode(float price, short unsigned insId, ListNode* next);

void insertNodeToEndList(MPIList* lst, ListNode* tail);

bool isEmptyList(MPIList* lst);

void freeList(MPIList* lst);

// Instrument's List Signature
void makeEmptyCIList(CIList* lst);

void insertDataToEndCIList(CIList* lst, char importance, int num, int inst);

void insertNodeToEndCIList(CIList* lst, CIListNode* tail);

CIListNode* createNewCIListNode(char importance, int num, int inst, CIListNode* next);

bool isEmptyCIList(CIList* lst);

void freeCIList(CIList* lst);

//Concert Musician's List Signature
void makeEmptyCMList(ConcertMusiciansList* lst);

void insertDataToEndCMList(ConcertMusiciansList* lst, Musician* musician, int insId);

void insertNodeToEndCMList(ConcertMusiciansList* lst, CMListNode* tail);

CMListNode* createNewCMListNode(Musician* musician, CMListNode* next, int insId);

bool isEmptyCMList(ConcertMusiciansList* lst);

void freeCMList(ConcertMusiciansList* lst);

#endif
