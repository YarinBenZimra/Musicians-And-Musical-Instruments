#ifndef ProjectMain_H



#define ProjectMain_H
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "TREES.h"
#include "LIST.h"


#define PHYSIC_SIZE 1
#define AscendingOrder 49
#define DescendingOrder 48
#define IntToChar 48
#define ISDIGIT(c) (((((c) >= '0') && ((c) <= '9'))) ? (true) : (false))
#define IMPORTANT 1
#define NOT_IMPORTANT 0

int global_insId;

typedef struct date
{
	int day, month, year;
	float hour;
} Date;


typedef struct concert
{
	Date date_of_concert;
	char* name;
	CIList instruments;
	ConcertMusiciansList ConcertMusicians;
	int num_of_shows;
} Concert;


Musician* Build_Musician_Array(char** mixed_musicion_mat, InstrumentTree* tr, int number_of_musicians);

bool is_price(ListNode* curr, char* token);

bool is_instrument(MPIList* list, ListNode** curr, int insId);

char** is_name(int* log_size, int* phisic_size, char** names, char* token);

void checkMemoryAllocation(void* ptr);

Instrument* Build_Musicians_Collection(Musician** MusiciansGroup, int number_of_instruments, int number_of_musicians);

bool is_instrument_exist(Musician* musician_member, int i);

char** PerformanceText(int* num_of_shows);

Concert* Build_Concert_Array(InstrumentTree* instrument_tr, char** text, int num_of_shows);

int InsertShowName(Concert* concert, char* line);

int FindFirstNumIndex(char* line);

int FindFirstLetterIndex(char* line);

int InsertShowDate(Concert* concert, char* line);

void InsertHourToDate(Concert* concert, char* token);

CIList InsertShowListInstruments(Concert* concert, char* token, InstrumentTree* instrument_tr);

char** ScanFileToMat(char* file_name, int* size);

void CheckFile(FILE* fp);

void FreeText(char** text, int size);

int ComparePriceInUpOrder(void* ptr1, void* ptr2);

int ComparePriceInDownOrder(void* ptr1, void* ptr2);

void copyArr(Musician** dest, Musician** src, int size);

float FindPriceByInsId(Musician* musician, int insId);

void PerformancesManagement(Concert* concert, Instrument* MusiciansCollection, Musician** MusiciansGroup, InstrumentTree* tree, int number_of_musicians);

ConcertMusiciansList* BuildConcertMusiciansArray(Concert* concert, Instrument* MusiciansCollection, bool* succeed);

void IntializeAvailability(Musician** MusiciansGroup, int size);

char* find_instrument_name_by_insId(InstrumentTree tree, int insId);

char* find_instrument_name_by_insId_Helper(TreeNode* root, int insId);

void PrintShowDetails(Concert* concert, InstrumentTree* tree);

void PrintDate(Concert* concert);

void FreeMusicianGroup(Musician** MusiciansGroup, int number_of_musicians);

void FreeMusicianCollection(Instrument* MusicianCollection, int number_of_instruments);

void FreeConcertArray(Concert* concert);

void FreeAll(InstrumentTree* tree, Musician** MusiciansGroup, Instrument* MusicianCollection, Concert* concert, int number_of_instruments, int number_of_musicians);

#endif // !ProjectMain_H