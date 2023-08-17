#include "ProjectMain.h"



Musician* Build_Musician_Array(char** mixed_musicion_mat, InstrumentTree* tr, int number_of_musicians) // This Function get mixed musician file with seperators, here we extract the words without the seperators and consrtuct a pointers to musician's array.
{
	Musician** MusiciansGroup;
	MusiciansGroup = (Musician**)malloc(sizeof(Musician*) * number_of_musicians); // Create pointers to musician's array.
	checkMemoryAllocation(MusiciansGroup);
	char seps[] = " ,.;:?!-\t'()[]{}<>~_ ";
	char* token;
	for (int i = 0; i < number_of_musicians; i++)// Loop for every row in file.
	{
		// Initialize Parameters In Every Loop
		MPIList list;
		makeEmptyList(&list);
		ListNode* curr = NULL;
		int phisic_size = PHYSIC_SIZE, log_size = 0;
		bool flag_price = false, flag_instrument = false;
		Musician* temp_musician = (Musician*)malloc(sizeof(Musician));
		checkMemoryAllocation(temp_musician);
		
		temp_musician->name = (char**)malloc(sizeof(char*) * phisic_size);// Create Pointers To String array For The Full Name Per Musician.
		checkMemoryAllocation(temp_musician->name);

		token = strtok(mixed_musicion_mat[i], seps);// Extract The Word Without Seps.
		while (token != NULL)
		{
			bool flag_price = is_price(curr, token); // Check if the word mean to price of an instrument
			if (flag_price == false)
			{
				int check_insId = findInsId(*tr, token); // Here We call to reqursive functionn that give us the insId if the word is an instrument, otherwise we get -1.
				flag_instrument = is_instrument(&list, &curr, check_insId); // Check if the word mean to an instrument

				if (flag_instrument == false)
				{
					temp_musician->name = is_name(&log_size, &phisic_size, temp_musician->name, token);// Check if the word is part of musician's name.
				}
			}
			token = strtok(NULL, seps);// Get the next word
		}
		if (log_size < phisic_size)
		{
			temp_musician->name = (char**)realloc(temp_musician->name, log_size * (sizeof(char*))); // Narrow the char array to the log size.
			checkMemoryAllocation(temp_musician->name);
		}
		temp_musician->name_log_size = log_size; // Here we save the log size to "free memory" at the end of the use in the array.
		temp_musician->instruments = list; // link the list we created to the musician.

		MusiciansGroup[i] = temp_musician; // Save the adress.
	}
	return MusiciansGroup;
}

bool is_price(ListNode* curr, char* token)  // Check if the word mean to price of an instrument
{
	if (ISDIGIT(token[0]))
	{
		float currPrice;
		sscanf(token, "%f", &currPrice);
		curr->MPinstrument->price = currPrice; // Insert the price for the instrument to the exsist node in the list.
		return true;
	}
	else
	{
		return false;
	}
}

bool is_instrument(MPIList* list, ListNode** curr, int insId) //If the word mean to price of an instrument, we create new node with the insId details and enter the node to the list.
{
	if (insId != NOTINSTRUMENT)
	{
		insertDataToEndList(list, NOTINSTRUMENT, insId);
		*curr = list->tail;
		return true;
	}
	else
	{
		return false;
	}
}

char** is_name(int* log_size, int* phisic_size, char** names, char* token) // Check if the word is part of musician's name.
{
	if (*log_size == *phisic_size) // For realloc.
	{
		*phisic_size *= 2;
		names = (char**)realloc(names, *phisic_size * (sizeof(char*)));
		checkMemoryAllocation(names);
	}

	names[*log_size] = strdup(token); // Strdup for token and insert to the array of string respectively by location.
	(*log_size)++;
	return names;
}

void checkMemoryAllocation(void* ptr) // Check Memory Allocation.
{
	if (ptr == NULL)
	{
		printf("Failure memory allocation");
		exit(1);
	}
}

Instrument* Build_Musicians_Collection(Musician** MusiciansGroup, int number_of_instruments, int number_of_musicians) // Here we build array of arrays the contain all the musician that play on the instrument according to the insId.
{
	Instrument* MusiciansCollection = (Instrument*)malloc(sizeof(Instrument) * number_of_instruments);
	checkMemoryAllocation(MusiciansCollection);

	for (int i = 0; i < number_of_instruments; i++)
	{
		Musician** curr;
		int log_size = 0, phi_size = PHYSIC_SIZE;
		curr = (Musician**)malloc(sizeof(Musician*) * phi_size);
		checkMemoryAllocation(curr);
		for (int j = 0; j < number_of_musicians; j++)
		{
			if (is_instrument_exist(MusiciansGroup[j], i)) // Check if the musicion play on the specific instrument .
			{

				if (log_size == phi_size) // For realloc.
				{
					phi_size *= 2;
					curr = (Musician**)realloc(curr, phi_size * (sizeof(Musician*)));
					checkMemoryAllocation(curr);
				}

				curr[log_size] = MusiciansGroup[j]; // Insert The Adress Of Musician.
				log_size++;
			}

		}
		if (log_size < phi_size && log_size!=0)
		{
			curr = (Musician**)realloc(curr, log_size * (sizeof(Musician*))); // Narrow The Array.
			checkMemoryAllocation(curr);
		}

		MusiciansCollection[i].Who_Play_On_Specific_Instrument = curr;
		MusiciansCollection[i].SizeOfArr = log_size;
	}
	return MusiciansCollection;
}

bool is_instrument_exist(Musician* musician_member, int i) //Check if the specific musician have the instrument's insId according the index.
{
	ListNode* curr = musician_member->instruments.head;

	while (curr != NULL) // Run on the musician's list
	{
		if (curr->MPinstrument->insId == i)
		{
			return true;
		}
		curr = curr->next;
	}
	return false;
}

char** PerformanceText(int* num_of_shows) //This function scan all the shows from the user. 
{
	char** text;
	char c;
	int logSizeRow = 0, phsSizeRow = PHYSIC_SIZE;
	text = (char**)malloc(phsSizeRow * sizeof(char*));
	checkMemoryAllocation(text);
	bool endOfInput = false;
	char* line;
	while (endOfInput == false)
	{
		int logSizeCols = 0, phsSizeCols = PHYSIC_SIZE;

		line = (char*)malloc(phsSizeCols * sizeof(char));
		checkMemoryAllocation(line);
		scanf("%c", &c);

		while (c != '\n')
		{
			if (logSizeCols == phsSizeCols)
			{
				phsSizeCols *= 2;
				line = (char*)realloc(line, phsSizeCols * sizeof(char));
				checkMemoryAllocation(line);
			}
			line[logSizeCols] = c;
			logSizeCols++;
			scanf("%c", &c);
		}

		if (logSizeCols < phsSizeCols && logSizeCols != 0)
		{
			line = (char*)realloc(line, logSizeCols * sizeof(char));
			checkMemoryAllocation(line);
		}

		line[logSizeCols] = '\0';

		if (line[0] == '\0')
			endOfInput = true;

		else
		{
			if (logSizeRow == phsSizeRow)
			{
				phsSizeRow *= 2;
				text = (char**)realloc(text, phsSizeRow * sizeof(char*));
				checkMemoryAllocation(text);
			}
			text[logSizeRow] = strdup(line); //duplicates a string
			logSizeRow++;
		}
	}
	if (logSizeRow < phsSizeRow && logSizeRow != 0)
	{
		text = (char**)realloc(text, logSizeRow * sizeof(char*));
		checkMemoryAllocation(text);
	}

	*num_of_shows = logSizeRow;
	return text;
}

Concert* Build_Concert_Array(InstrumentTree* instrument_tr, char** text, int num_of_shows)// This function builds an array that contains all the show's order.
{
	Concert* ConcertArray = (Concert*)malloc(sizeof(Concert) * num_of_shows);
	checkMemoryAllocation(ConcertArray);

	for (int i = 0; i < num_of_shows; i++)
	{
		int curr_index = 0;
		makeEmptyCIList(&(ConcertArray[i].instruments));
		CIListNode curr;


		curr_index += InsertShowName(&ConcertArray[i], text[i]);

		curr_index += InsertShowDate(&ConcertArray[i], text[i] + curr_index + 1);

		ConcertArray[i].instruments = InsertShowListInstruments(&ConcertArray[i], text[i] + curr_index + 1, instrument_tr);


	}
	FreeText(text, num_of_shows); // After build the concert array whe free the text.

	return ConcertArray;
}

int InsertShowName(Concert* concert, char* line) // Insert the show name to the concert array.
{
	int curr_index = FindFirstNumIndex(line);
	line[curr_index] = '\0';
	concert->name = strdup(line);
	line[curr_index] = ' ';

	return curr_index;
}

int FindFirstNumIndex(char* line)// This function return the first index in line which before digit.
{
	int k = 0;

	while (!ISDIGIT(line[k]))
	{
		k++;
	}

	return k - 1;
}

int FindFirstLetterIndex(char* line)// This function return the first index in line which before letter.
{
	int k = 0;

	while (ISDIGIT(line[k]) || line[k] == ' ' || line[k] == ':')
	{
		k++;
	}

	return k - 1;
}

int InsertShowDate(Concert* concert, char* line)  // Insert the show date to the concert array.
{
	int index = 1;
	int end_of_date = FindFirstLetterIndex(line);
	char seps[] = " ";
	char* token;
	char* temp_line = strdup(line);
	token = strtok(temp_line, seps);
	while (index <= 4)
	{
		if (index % 4 == 1)
			sscanf(token, "%d", &(concert->date_of_concert.day));

		else if (index % 4 == 2)
			sscanf(token, "%d", &(concert->date_of_concert.month));

		else if (index % 4 == 3)
			sscanf(token, "%d", &(concert->date_of_concert.year));

		else if (index % 4 == 0)
			InsertHourToDate(concert, token);

		token = strtok(NULL, seps);
		index++;
	}
	free(temp_line);
	return end_of_date;
}

void InsertHourToDate(Concert* concert, char* token) // Insert the hour of the show to date's struct.
{
	float hour, minutes;
	char c = token[2];// :
	token[2] = ' ';
	sscanf(token, "%f%f", &hour, &minutes);
	minutes = minutes / 60;
	token[2] = c;

	concert->date_of_concert.hour = hour + minutes;

}

CIList InsertShowListInstruments(Concert* concert, char* token, InstrumentTree* instrument_tr)// Insert the supposed instruments list for the concert to the cooncert array.
{
	CIList lst;
	makeEmptyCIList(&lst);
	CIListNode* curr = lst.head;

	int i = 1;
	char* temp_token;
	char seps[] = " ";
	char* temp_line = strdup(token);
	temp_token = strtok(temp_line, seps);

	while (temp_token != NULL)
	{
		if (i % 3 == 1)
		{
			int inst = findInsId(*instrument_tr, temp_token);
			insertDataToEndCIList(&lst, EOF, EOF, inst);
			curr = lst.tail;
		}

		else if (i % 3 == 2)
		{
			sscanf(temp_token, "%d", &(curr->CIinstrument->num));
		}

		else if (i % 3 == 0)
		{
			sscanf(temp_token, "%c", &(curr->CIinstrument->importance));
			i = 0;
		}

		i++;
		temp_token = strtok(NULL, seps);
	}
	free(temp_line);
	return lst;

}

void FreeText(char** text, int size)
{
	for (int i = 0; i < size; i++)
	{
		free(text[i]);
	}
	free(text);
}

int ComparePriceInUpOrder(void* ptr1, void* ptr2)
{
	int inst = global_insId;
	Musician** musician1 = (Musician**)ptr1;
	Musician** musician2 = (Musician**)ptr2;
	float price1=FindPriceByInsId(*musician1, inst);
	float price2 = FindPriceByInsId(*musician2, inst);

	return (int)(price1) - (int)price2;
}

int ComparePriceInDownOrder(void* ptr1, void* ptr2)
{
	int inst = global_insId;
	Musician** musician1 = (Musician**)ptr1;
	Musician** musician2 = (Musician**)ptr2;
	float price1 = FindPriceByInsId(*musician1, inst);
	float price2 = FindPriceByInsId(*musician2, inst);

	return (int)(price2)-(int)price1;
}

float FindPriceByInsId(Musician* musician, int insId)// This function get insId and find the price of the musician that plays on the specific instrument.
{
	ListNode* curr = musician->instruments.head;

	while (curr != NULL)
	{
		if (curr->MPinstrument->insId == insId)
		{
			return curr->MPinstrument->price;
		}
		curr = curr->next;
	}
}

void copyArr(Musician** dest, Musician** src, int size)
{
	int i;

	for (i = 0; i < size; i++)
		dest[i] = src[i];
}

void PerformancesManagement(Concert* concert, Instrument* MusiciansCollection, Musician** MusiciansGroup, InstrumentTree* tree, int number_of_musicians)// This function gets details about show, check if the it possible to maintain the show.
{


	for (int i = 0; i < concert->num_of_shows; i++)
	{
		CIListNode* curr = concert[i].instruments.head;
		bool succeed = true;
		IntializeAvailability(MusiciansGroup, number_of_musicians);

		while (curr != NULL)
		{
			global_insId = curr->CIinstrument->inst;
			if (curr->CIinstrument->importance == AscendingOrder)
			{
				qsort(MusiciansCollection[curr->CIinstrument->inst].Who_Play_On_Specific_Instrument, MusiciansCollection[curr->CIinstrument->inst].SizeOfArr, sizeof(Musician*), ComparePriceInDownOrder);
			}
			else
			{
				qsort(MusiciansCollection[curr->CIinstrument->inst].Who_Play_On_Specific_Instrument, MusiciansCollection[curr->CIinstrument->inst].SizeOfArr, sizeof(Musician*), ComparePriceInUpOrder);
			}
			curr = curr->next;

		}
		concert[i].ConcertMusicians = *(BuildConcertMusiciansArray(&concert[i], MusiciansCollection, &succeed));// If it possible to maintain the show, we insert the details to the cooncert musician array.

		if (succeed)
		{
			PrintShowDetails(&concert[i], tree); // print the details of the show.
		}
	}
}

ConcertMusiciansList* BuildConcertMusiciansArray(Concert* concert, Instrument* MusiciansCollection, bool* succeed) //In this function we builds a list that contains all the musicians that will perform in the concert.
{
	
	ConcertMusiciansList list;
	CIListNode* curr = concert->instruments.head;
	int sizeoflist = 0;
	Instrument players;
	makeEmptyCMList(&list);
	int sum_musicians = 0;

	while (curr != NULL)
	{
		int i = 0, j = 0;
		Instrument players = MusiciansCollection[curr->CIinstrument->inst];
		if (curr->CIinstrument->num > players.SizeOfArr)
		{
			printf("Could not find musicians for the concert %s\n\n\n", concert->name);
			*succeed = false;
			break;
		}
		else
		{
			while (i < curr->CIinstrument->num && j < players.SizeOfArr)
			{
				if (players.Who_Play_On_Specific_Instrument[j]->Available)
				{
					insertDataToEndCMList(&list, players.Who_Play_On_Specific_Instrument[j], curr->CIinstrument->inst);
					players.Who_Play_On_Specific_Instrument[j]->Available = false;
					sizeoflist++;
					i++;
				}
				
				j++;

			}

			sum_musicians += curr->CIinstrument->num;

			if (sum_musicians > sizeoflist)
			{
				printf("Could not find musicians for the concert %s\n\n\n", concert->name);
				*succeed = false;
				break;
			}
		}
		curr = curr->next;
	}

	return &list;
}

void IntializeAvailability(Musician** MusiciansGroup, int size) // Initiailizes the availability of the muisicians for the next concerts.
{
	for (int i = 0; i < size; i++)
	{
		if (MusiciansGroup[i]->Available == false)
			MusiciansGroup[i]->Available = true;
	}
}

char* find_instrument_name_by_insId(InstrumentTree tree, int insId)
{
	return find_instrument_name_by_insId_Helper(tree.root, insId); // Rewursive Function 
}

char* find_instrument_name_by_insId_Helper(TreeNode* root, int insId)
{
	// Here we get insId and a tree of instruments, if the Inst is exist in the tree we return the instrument's name, otherwise we return NULL. 

	int left, right;
	if (root == NULL) // If the root point on NULL we return -1.
	{
		return NULL;
	}

	else if (root->insId == insId) //If the the root's insId is equal to the insId we return the name.
	{
		return root->instrument;
	}

	else
	{
		left = find_instrument_name_by_insId_Helper(root->left, insId); // Check the left tree.
		if (left != NULL) // If we found we return the name
		{
			return left;
		}
		else // Otherwise, we check the right tree.
		{
			return right = find_instrument_name_by_insId_Helper(root->right, insId);
		}
	}

}

void PrintShowDetails(Concert* concert, InstrumentTree* tree) // Prints the show's details.
{
	CMListNode* currCM = concert->ConcertMusicians.head;
	float currPrice = 0, TotalPrice = 0;
	
	
	printf("******************* %s Show's Details *******************\n\n", concert->name);
	printf("The name of the show is: %s\n", concert->name);

	PrintDate(concert);
	

	while (currCM != NULL)
	{
		printf("The name of the musician is: ");
		for (int j = 0; j < currCM->musician->name_log_size; j++)
		{
			printf("%s ", currCM->musician->name[j]);
		}
		printf("\n");
		printf("The instrument's insId is: %d and the instrument's name is: %s\n", currCM->InsIdForCurrShow, find_instrument_name_by_insId(*tree, currCM->InsIdForCurrShow));
		currPrice = FindPriceByInsId(currCM->musician, currCM->InsIdForCurrShow);
		printf("The price for the instrument is: %d\n\n", (int)currPrice);
		TotalPrice += currPrice;

		currCM = currCM->next;
	}

	printf("The total price for the show is: %d\n\n\n", (int)TotalPrice);
}

void PrintDate(Concert* concert)
{
	short unsigned hour, minutes;
	hour = (short unsigned)concert->date_of_concert.hour / 1;
	minutes = (concert->date_of_concert.hour - hour) * 60;
	char stringmin[3], stringhour[3], stringmonth[3], stringday[3];
	if (minutes == 0)
	{
		strcpy(stringmin, "00");
	}
	
	else if (minutes / 10 == 0)
	{
		stringmin[0] = '0';
		stringmin[1] = (char)minutes + IntToChar;
	}
	else
	{
		sprintf(stringmin, "%d", minutes);
	}

	if (hour == 0)
	{
		strcpy(stringhour, "00");
	}
	else if (hour / 10 == 0)
	{
		stringhour[0] = '0';
		stringhour[1] = (char)hour + IntToChar;
	}
	else
	{
		sprintf(stringhour, "%d", hour);
	}

	if (concert->date_of_concert.month / 10 == 0)
	{
		stringmonth[0] = '0';
		stringmonth[1]=(char)concert->date_of_concert.month+ IntToChar;
	}
	else
	{
		sprintf(stringmonth, "%d", concert->date_of_concert.month);

	}
	if (concert->date_of_concert.day / 10 == 0)
	{
		stringday[0] = '0';
		stringday[1]=(char)concert->date_of_concert.day+ IntToChar;
	}
	else
	{
		sprintf(stringday, "%d", concert->date_of_concert.day);

	}
	stringmin[2] = stringhour[2] = stringday[2] = stringmonth[2] = 0;
	printf("The date of the show is: %s %s %d %s:%s\n\n", stringday, stringmonth, concert->date_of_concert.year, stringhour, stringmin);


	
}

char** ScanFileToMat(char* file_name, int* size)
{
	char line[COLS];
	bool flag = true;
	char** file = (char**)malloc(sizeof(char*) * PHYSIC_SIZE);
	checkMemoryAllocation(file);
	int log_size = 0, phy_size = PHYSIC_SIZE;
	FILE* fp;
	fp = fopen(file_name, "r");
	CheckFile(fp);

	while (flag)
	{
		if (fgets(line, COLS, fp) == NULL)
			flag = false;

		else
		{
			line[strlen(line)-1] = 0;

			if (log_size == phy_size)
			{
				phy_size *= 2;
				file = (char**)realloc(file, sizeof(char*) * phy_size);
				checkMemoryAllocation(file);
			}
			file[log_size] = strdup(line);

			log_size++;
		}
	}

	if (log_size < phy_size)
	{
		file = (char**)realloc(file, sizeof(char*) * log_size);
		checkMemoryAllocation(file);
	}

	

	fclose(fp);
	*size = log_size;
	return file;
}

void CheckFile(FILE* fp)
{
	if (fp == NULL)
	{
		printf("File is not exist");
		exit(1);
	}
}

void FreeMusicianGroup(Musician** MusiciansGroup, int number_of_musicians)
{
	for (int i = 0; i < number_of_musicians; i++)
	{
		for (int j = 0; j < MusiciansGroup[i]->name_log_size; j++)// Free musician names
		{
			free(MusiciansGroup[i]->name[j]);
		}

		freeCIList(&(MusiciansGroup[i]->instruments));

		free(MusiciansGroup[i]);
	}

	free(MusiciansGroup);
}

void FreeMusicianCollection(Instrument* MusicianCollection, int number_of_instruments)
{
	for (int i = 0; i < number_of_instruments; i++)
	{
		free(MusicianCollection[i].Who_Play_On_Specific_Instrument);
	}

	free(MusicianCollection);
}

void FreeConcertArray(Concert* concert)
{
	for (int i = 0; i < concert->num_of_shows; i++)
	{
		freeCMList(&(concert[i].ConcertMusicians));
		freeCIList(&(concert[i].instruments));
		free(concert[i].name);


	}

	free(concert);
}

void FreeAll(InstrumentTree* tree, Musician** MusiciansGroup, Instrument* MusicianCollection, Concert* concert, int number_of_instruments, int number_of_musicians)
{
	freeTree(*tree);
	FreeMusicianGroup(MusiciansGroup, number_of_musicians);
	FreeMusicianCollection(MusicianCollection, number_of_instruments);
	FreeConcertArray(concert);
}