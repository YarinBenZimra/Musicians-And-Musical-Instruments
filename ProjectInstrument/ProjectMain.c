#include "ProjectMain.h"


void main(int argc, char* argv[])
{
	FILE* musiciansfile;
	int number_of_instruments, number_of_musicians;

	InstrumentTree tr = Build_Binari_Instrument_Tree_By_Lexicography(argv[1], &number_of_instruments);
	Musician** MusiciansGroup;
	char** mixed_musicians_mat = ScanFileToMat(argv[2], &number_of_musicians);
	MusiciansGroup = Build_Musician_Array(mixed_musicians_mat, &tr, number_of_musicians);

	Instrument* MusiciansCollection;
	MusiciansCollection = Build_Musicians_Collection(MusiciansGroup, number_of_instruments, number_of_musicians);

	int num_of_shows;
	char** text = PerformanceText(&num_of_shows);

	Concert* Concert_Array;
	Concert_Array = Build_Concert_Array(&tr, text, num_of_shows);
	Concert_Array->num_of_shows = num_of_shows;

	PerformancesManagement(Concert_Array, MusiciansCollection, MusiciansGroup, &tr, number_of_musicians);
	FreeAll(&tr, MusiciansGroup, MusiciansCollection, Concert_Array, number_of_instruments, number_of_musicians);
}


