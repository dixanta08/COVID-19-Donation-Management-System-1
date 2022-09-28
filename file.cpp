#include <iostream>
#include <fstream>

#include "global.h"

//File Handling (Donation)
char* ReadDonationFromFile() {
	FILE* fptr;
	fopen_s(&fptr,"donation.txt", "r");

	static char result[MAX_FILE_LENGTH];
	if (fptr == NULL)
	{
		printf("Error opening file! Please create donation.txt!");
	}
	else
	{	
		int counter = 0;
		while (1) {
			int display;
			display = fgetc(fptr);

			if (display == EOF) {
				break;
			}

			result[counter] = display;
			counter++;

		}
		fclose(fptr);
	}
	return result;
}

void SaveDonationToFile(Donation* AllDonation) {
	FILE* fptr;
	if (fopen_s(&fptr, "donation.txt", "w+") != 0)
	{
		printf("\nError");
		return;
	}
	if (!fptr)
	{
		printf("\n Error in opening file!");
		return;
	}

	for (int i = 0; i < MAX_RECORD_COUNT; i++) {
		if (AllDonation[i].QuantityReceived == -1) {
			break;
		}
		else {
			fprintf(fptr, "%s;", AllDonation[i].SupplyName);
			fprintf(fptr, "%s;", AllDonation[i].SupplyCode);
			fprintf(fptr, "%s;", AllDonation[i].Donator);
			fprintf(fptr, "%d;", AllDonation[i].NoOfShipment);
			fprintf(fptr, "%lf\n", AllDonation[i].QuantityReceived);
		}
	}
	fclose(fptr);
}

void AddDonationToFile(char SupplyName[30], char SupplyCode[20], char Donator[30], int NoOfShipment, double QuantityReceived) {
	FILE* fptr;
	if (fopen_s(&fptr, "donation.txt", "a") != 0)
	{
		printf("\nError");
		return;
	}
	if (!fptr)
	{
		printf("\n Error in opening file!");
		return;
	}
	fprintf(fptr, "%s;", SupplyName);
	fprintf(fptr, "%s;", SupplyCode);
	fprintf(fptr, "%s;", Donator);
	fprintf(fptr, "%d;", NoOfShipment);
	fprintf(fptr, "%lf\n", QuantityReceived);
	fclose(fptr);
}

Donation* Donation_ConvertTextToStruct(char* FileTextPtr) {
	Donation AllDonation[MAX_RECORD_COUNT];

	char* pch, * pch2, * buf, * buf2;
	buf = (char*)malloc(MAX_FILE_LENGTH);
	buf2 = (char*)malloc(MAX_FILE_LENGTH);

	int counter = 0;
	pch = strtok_s(FileTextPtr, "\n", &buf);
	while (pch != NULL)
	{
		int counter2 = 0;
		pch2 = strtok_s(pch, ";", &buf2);
		while (pch2 != NULL)
		{
			switch (counter2) {
			case 0:
				strcpy_s(AllDonation[counter].SupplyName, pch2);
				break;
			case 1:
				strcpy_s(AllDonation[counter].SupplyCode, pch2);
				break;
			case 2:
				strcpy_s(AllDonation[counter].Donator, pch2);
				break;
			case 3:
				sscanf_s(pch2, "%d", &AllDonation[counter].NoOfShipment);
				break;
			case 4:
				sscanf_s(pch2, "%lf", &AllDonation[counter].QuantityReceived);
				break;
			default:
				printf("\nError: Extra column detect! - %s,%d", pch2, counter2);
				break;
			}
			counter2++;

			pch2 = strtok_s(NULL, ";", &buf2);
		}
		counter++;
		pch = strtok_s(NULL, "\n", &buf);
	}
	return AllDonation;
}





//File Handling (Distribution)
char* ReadDistributionFromFile() {
	FILE* fptr;
	fopen_s(&fptr, "dist.txt", "r");

	static char result[MAX_FILE_LENGTH];
	if (fptr == NULL)
	{
		printf("Error opening file! Please create dist.txt!");
	}
	else
	{
		int counter = 0;
		while (1) {
			int display;
			display = fgetc(fptr);

			if (display == EOF) {
				break;
			}

			result[counter] = display;
			counter++;

		}
		fclose(fptr);
	}
	return result;
}

void SaveDistributionToFile(Dist* AllDist) {
	FILE* fptr;
	if (fopen_s(&fptr, "dist.txt", "w+") != 0)
	{
		printf("\nError");
		return;
	}
	if (!fptr)
	{
		printf("\n Error in opening file!");
		return;
	}

	for (int i = 0; i < MAX_RECORD_COUNT; i++) {
		if (AllDist[i].QuantityDistributed == -1) {
			break;
		}
		else {
			fprintf(fptr, "%s;", AllDist[i].DonationCode);
			fprintf(fptr, "%lf\n", AllDist[i].QuantityDistributed);
		}
	}
	fclose(fptr);
}

void AddDistributionToFile(char DonationCode[40], double QuantityReceived) {
	FILE* fptr;
	if (fopen_s(&fptr, "dist.txt", "a") != 0)
	{
		printf("\nError");
		return;
	}
	if (!fptr)
	{
		printf("\n Error in opening file!");
		return;
	}
	fprintf(fptr, "%s;", DonationCode);
	fprintf(fptr, "%lf\n", QuantityReceived);
	fclose(fptr);
}

Dist* Dist_ConvertTextToStruct(char* FileTextPtr2) {
	Dist AllDist[MAX_RECORD_COUNT];

	char* pch3, * pch4, * buf3, * buf4;
	buf3 = (char*)malloc(MAX_FILE_LENGTH);
	buf4 = (char*)malloc(MAX_FILE_LENGTH);

	int counter = 0;
	pch3 = strtok_s(FileTextPtr2, "\n", &buf3);
	while (pch3 != NULL)
	{
		int counter2 = 0;
		pch4 = strtok_s(pch3, ";", &buf4);
		while (pch4 != NULL)
		{
			switch (counter2) {
			case 0:
				strcpy_s(AllDist[counter].DonationCode, pch4);
				break;
			case 1:
				sscanf_s(pch4, "%lf", &AllDist[counter].QuantityDistributed);
				break;
			default:
				printf("\nError: Extra column detect! - %s,%d", pch4, counter2);
				break;
			}
			counter2++;

			pch4 = strtok_s(NULL, ";", &buf4);
		}
		counter++;
		pch3 = strtok_s(NULL, "\n", &buf3);
	}

	return AllDist;
}



////This function can split a string up to 100 pieces, each pieces with maximum 50 character
//char* SplitWithCharacter(char* Source, char Spliter, int index) {
//	int counter = 0;
//
//	bool end = false;
//	int a = 0;
//	char segment[80] = "";
//
//	while (!end) {
//		for (int b=0; a < MAX_FILE_LENGTH; a++) {
//			if (Source[a] != Spliter) {
//				if (Source[a] == NULL) {
//					end = true;
//					return NULL;
//				}
//				else {
//					segment[b] = Source[a];
//					b++;
//				}
//			}
//			else {
//				break;
//			}
//		}	
//		printf("\nindex: %d   counter: %d    segment: %s", index, counter, segment);
//		if (counter == index) {
//			char* result = segment;
//			return result;
//		}
//		counter++;
//		a++;
//	}
//}
//
//
////This function is an alternative function to parse text to struct
//Dist* Dist_ConvertTextToStruct(char* FileTextPtr2) {
//	Dist AllDist[MAX_RECORD_COUNT];
//	char* SplitWithCharacter(char*, char, int);
//
//	for (int a = 0; a < MAX_RECORD_COUNT; a++) {
//
//		char* SplitResult = SplitWithCharacter(FileTextPtr2, '\n', a);
//		if (SplitResult == NULL) {
//			break;
//		}
//
//		for (int b = 0; b < MAX_RECORD_COUNT; b++) {
//			char SplitResultTemp[80] = "";
//			strcpy_s(SplitResultTemp, SplitResult);
//
//			char* SplitResult2 = SplitWithCharacter(SplitResultTemp, ';', b);
//			printf("\nResult: %s", SplitResult2);
//
//			if (SplitResult2 == NULL) {
//				break;
//			}
//			switch (b) {
//			case 0:
//				strcpy_s(AllDist[a].DonationCode, SplitResult2);
//				break;
//			case 1:
//				sscanf_s(SplitResult2, "%lf", &AllDist[a].QuantityDistributed);
//				break;
//			default:
//				printf("\nError: Extra column detect! - %s,%d", SplitResult2, a);
//				break;
//			}
//		}
//
//	}
//}
//
//
