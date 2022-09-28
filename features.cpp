#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <Windows.h>

#include "global.h"


//Function Prototypes
void AddDonationToFile(char[30], char[20], char[30], int, double), SaveDonationToFile(Donation*), AddDistributionToFile(char[40],double);
char* ReadDonationFromFile();
char* ReadDistributionFromFile();
Donation* Donation_ConvertTextToStruct(char*); 
Dist* Dist_ConvertTextToStruct(char*);


//Functions


void NewDonation() {
	char cont = 'y';
	while (cont == 'y') {
		char SupplyName[30];
		char SupplyCode[20];
		char Donator[30];
		int NoOfShipment;
		double QuantityReceived;

		system("cls");
		printf("\n              Inventory Creation   \n");
		printf("           =======================\n");
		printf("\nPlease provide the supply name: ");
		gets_s(SupplyName);
		printf("\nPlease provide the supply code: ");
		gets_s(SupplyCode);
		printf("\nPlease provide the donator name: ");
		gets_s(Donator);
		printf("\nPlease provide the number of shipments: ");
		scanf_s("%d", &NoOfShipment); while (getchar() != '\n');
		printf("\nPlease provide the quantity received (millions): ");
		scanf_s("%lf", &QuantityReceived); while (getchar() != '\n');
		
		AddDonationToFile(SupplyName, SupplyCode, Donator, NoOfShipment, QuantityReceived);
		printf("\n\n\n           ==================================================\n");
		printf("                               ! Success !   \n");
		printf("           ==================================================\n");
		printf("               The system has generated a Donation Code.\n");
		printf("                   -->  %s-%s \n\n", Donator, SupplyCode);
		printf("               Please keep it for future reference.   \n");
		printf("           ==================================================\n");

		printf("\n\nDo you want to add another donation? (y/n): ");
		scanf_s("%c", &cont); while (getchar() != '\n');
	}
}

void UpdateDonation() {
	char cont = 'y';
	while (cont == 'y') {
		char* DonationText = ReadDonationFromFile();
		Donation* AllDonation = Donation_ConvertTextToStruct(DonationText);

		system("cls");
		printf("\n             Update Donation Quantities   ");
		printf("\n           =============================\n");
		printf("\nWelcome! You can update the quantity of donation at here. \n\n\n");
		printf("%-5s %-25s %-15s %-20s %-25s %-25s\n", "No.", "Supply Name", "Supply Code", "Donator Name", "Number of Shipments", "Quantity Remained (mil)");
		printf("%-5s %-25s %-15s %-20s %-25s %-25s\n", "===", "===========", "===========", "============", "===================", "=======================");
		for (int i = 0; i < MAX_RECORD_COUNT; i++) {
			if (AllDonation[i].QuantityReceived == -1) {
				break;
			}
			else {
				printf("%-5d %-25s %-15s %-20s %-25d %-25lf\n", i+1, AllDonation[i].SupplyName, AllDonation[i].SupplyCode, AllDonation[i].Donator, 
					AllDonation[i].NoOfShipment, AllDonation[i].QuantityReceived);
			}
		}
		printf("\n");

		int choice = 0;
		while (choice < 1) {
			printf("\nPlease provide the No. of donation: ");
			scanf_s("%d", &choice); while (getchar() != '\n');
		}

		char ReceivedOrDistributed = 'n';
		while (!(ReceivedOrDistributed == 'd' || ReceivedOrDistributed == 'r')) {
			printf("\nPlease select received or distributed quantity (r/d): ");
			scanf_s("%c", &ReceivedOrDistributed); while (getchar() != '\n');
		}

		double Quantity;
		printf("\nPlease provide the quantity received/distributed (millions): ");
		scanf_s("%lf", &Quantity); while (getchar() != '\n');

		bool failed = false;
		if (AllDonation[choice - 1].QuantityReceived == -1) {
			printf("\n\n\nSorry. This donation is not valid. Please select again. Aborting....\n");
			failed = true;
		}
		else {
			if (ReceivedOrDistributed == 'r') {
				AllDonation[choice - 1].QuantityReceived += Quantity;
			}
			else {
				if (AllDonation[choice - 1].QuantityReceived >= Quantity) {
					AllDonation[choice - 1].QuantityReceived -= Quantity;

					char temp[1024] = "";
					strcat_s(temp, 1024, AllDonation[choice - 1].Donator);
					strcat_s(temp, 1024, "-");
					strcat_s(temp, 1024, AllDonation[choice - 1].SupplyCode);
					AddDistributionToFile(temp, Quantity);
				}
				else {
					printf("\n\n\nSorry. The existing quantity is not enough. Please enter again. Aborting....\n");
					failed = true;
				}
			}
		}

		if (!failed) {
			printf("\n\n\nSaving changes. Please wait...");
			SaveDonationToFile(AllDonation);

			printf("\n\n\n\n           =================\n");
			printf("               Success!   \n");
			printf("           =================\n");
		}

		printf("\n\nDo you want to update another donation? (y/n): ");
		scanf_s("%c", &cont); while (getchar() != '\n');

	}
}

void SearchDonation() {
	char cont = 'y';
	while (cont == 'y') {
		char* DonationText = ReadDonationFromFile();
		Donation* AllDonation = Donation_ConvertTextToStruct(DonationText);

		system("cls");
		printf("\n             Search Donation   ");
		printf("\n           ==================\n");

		char choice[30];
		printf("\nYou can search a specific donation with donation code.");
		printf("\nDonation code is given when you added the donation. It's combination of Donator Name and Supply Code with character '-'.");
		printf("\n\nPlease provide the donation code, or type 'all' for all list : ");
		gets_s(choice);

		while (strcmp(choice,"all")==0){
			printf("\n\nHere is a list of all donation. \n\n");
			printf("%-25s %-15s %-20s %-25s %-25s\n", "Supply Name", "Supply Code", "Donator Name", "Number of Shipments", "Quantity Remained (mil)");
			printf("%-25s %-15s %-20s %-25s %-25s\n", "===========", "===========", "============", "===================", "=======================");
			for (int i = 0; i < MAX_RECORD_COUNT; i++) {
				if (AllDonation[i].QuantityReceived == -1) {
					break;
				}
				else {
					printf("%-25s %-15s %-20s %-25d %-25lf\n", AllDonation[i].SupplyName, AllDonation[i].SupplyCode, AllDonation[i].Donator, 
						AllDonation[i].NoOfShipment, AllDonation[i].QuantityReceived);
				}
			}
			printf("\n\n\nYou can search a specific donation with donation code or with all list.");
			printf("\nDonation code is given when you added the donation. It's combination of Supply Code and Donator Name with character '-'.");
			printf("\n\nPlease provide the donation code, or type 'all' for all list : ");
			gets_s(choice);
		};

		int index = -1;
		for (int i = 0; i < MAX_RECORD_COUNT; i++) {
			char temp[1024] = "";
			strcat_s(temp, 1024, AllDonation[i].Donator);
			strcat_s(temp, 1024, "-");
			strcat_s(temp, 1024, AllDonation[i].SupplyCode);
			if (strcmp(temp,choice)==0) {
				index = i;
			}
		}

		if (index!=-1) {
			printf("\n\n           =================");
			printf("\n             Record Found!   \n");
			printf("           =================\n");
			printf("\n%-25s %-15s %-20s %-25s %-25s\n", "===========", "===========", "============", "===================", "=======================");
			printf("%-25s %-15s %-20s %-25s %-25s\n", "Supply Name", "Supply Code", "Donator Name", "Number of Shipments", "Quantity Remained (mil)");
			printf("%-25s %-15s %-20s %-25s %-25s\n", "===========", "===========", "============", "===================", "=======================");
			printf("%-25s %-15s %-20s %-25d %-25lf\n", AllDonation[index].SupplyName, AllDonation[index].SupplyCode, AllDonation[index].Donator, 
				AllDonation[index].NoOfShipment, AllDonation[index].QuantityReceived);
		}
		else {
			printf("\n\n\nFailed to find donation with this donation code. Please try again.");
		}

		printf("\n\nDo you want to search another donation? (y/n): ");
		scanf_s("%c", &cont); while (getchar() != '\n');

	}
}

void AllDonationAndDistribution() {
	int choice = 0;
	while (!(choice == 1 || choice == 2 || choice == 3 || choice == 4 || choice == 5)) {
		system("cls");
		printf("\n             List Donation and Distribution   ");
		printf("\n           =================================\n");
		printf("           1. All Donation (raw)\n");
		printf("           2. All Donation (sorted)\n");
		printf("           3. All Distribution (raw)\n");
		printf("           4. All Distribution (accumulated and sorted)\n");
		printf("           5. Back to Main Menu\n\n");
		printf("Your choice: ");
		scanf_s("%d", &choice); while (getchar() != '\n');
	}
	
	printf("\n\n");

	if (choice == 1) {
		char* DonationText = ReadDonationFromFile();
		Donation* AllDonation = Donation_ConvertTextToStruct(DonationText);

		printf("\n             All Donation   \n");
		printf("           =================\n\n");
		printf("%-25s %-15s %-20s %-25s %-25s\n", "Supply Name", "Supply Code", "Donator Name", "Number of Shipments", "Quantity Remained (mil)");
		printf("%-25s %-15s %-20s %-25s %-25s\n", "===========", "===========", "============", "===================", "=======================");
		for (int i = 0; i < MAX_RECORD_COUNT; i++) {
			if (AllDonation[i].QuantityReceived == -1) {
				break;
			}
			else {
				printf("%-25s %-15s %-20s %-25d %-25lf\n", AllDonation[i].SupplyName, AllDonation[i].SupplyCode, AllDonation[i].Donator, 
					AllDonation[i].NoOfShipment, AllDonation[i].QuantityReceived);
			}
		}
		printf("\n\nPress any key to back to menu...");
	}

	if (choice == 2) {
		char* DonationText = ReadDonationFromFile();
		Donation* AllDonation = Donation_ConvertTextToStruct(DonationText);

		//Detect filled donation count in AllDonation
		int counter = 0;
		for (int i = 0; i < MAX_RECORD_COUNT; i++) {
			if (AllDonation[i].QuantityReceived == -1) {
				break;
			}
			else {
				counter++;
			}
		}

		//Bubble sorting AllDonation
		int i, j;
		Donation Temp;
		for (i = 0; i < counter; i++)
		{
			for (j = i + 1; j < counter; j++)
				if (AllDonation[i].QuantityReceived < AllDonation[j].QuantityReceived)
				{
					Temp = AllDonation[i];
					AllDonation[i] = AllDonation[j];
					AllDonation[j] = Temp;
				}
		}

		printf("\n             All Donation   \n");
		printf("           =================\n\n");
		printf("%-25s %-15s %-20s %-25s %-25s\n", "Supply Name", "Supply Code", "Donator Name", "Number of Shipments", "Quantity Remained (mil)");
		printf("%-25s %-15s %-20s %-25s %-25s\n", "===========", "===========", "============", "===================", "=======================");
		for (int i = 0; i < MAX_RECORD_COUNT; i++) {
			if (AllDonation[i].QuantityReceived == -1) {
				break;
			}
			else {
				printf("%-25s %-15s %-20s %-25d %-25lf\n", AllDonation[i].SupplyName, AllDonation[i].SupplyCode, AllDonation[i].Donator, 
					AllDonation[i].NoOfShipment, AllDonation[i].QuantityReceived);
			}
		}
		printf("\n\nPress any key to back to menu...");
	}
	
	if (choice == 3) {
		char* DonationText = ReadDonationFromFile();
		Donation* AllDonationPtr = Donation_ConvertTextToStruct(DonationText);
		Donation AllDonation[MAX_RECORD_COUNT];
		for (int x = 0; x < MAX_RECORD_COUNT; x++)
			AllDonation[x] = AllDonationPtr[x];
		char* DistText = ReadDistributionFromFile();
		Dist* AllDist = Dist_ConvertTextToStruct(DistText);

		printf("\n             All Distributed Donations (detailed)   \n");
		printf("           ========================================\n\n");
		printf("%-25s %-15s %-20s %-25s\n", "Supply Name", "Supply Code", "Donator Name", "Quantity Distributed (mil)");
		printf("%-25s %-15s %-20s %-25s\n", "===========", "===========", "============", "==========================");

		for (int i2 = 0; i2 < MAX_RECORD_COUNT; i2++) {
			if (AllDist[i2].QuantityDistributed == -1) {
				break;
			}
			else {
				char SupplyName[30] = "";
				char SupplyCode[20];
				char Donator[30];

				for (int i = 0; i < MAX_RECORD_COUNT; i++) {
					if (AllDonation[i].QuantityReceived == -1) {
						break;
					}
					else {
						char temp[1024] = "";
						strcat_s(temp, 1024, AllDonation[i].Donator);
						strcat_s(temp, 1024, "-");
						strcat_s(temp, 1024, AllDonation[i].SupplyCode);
						if (strcmp(AllDist[i2].DonationCode, temp) == 0) {
							strcpy_s(SupplyName, AllDonation[i].SupplyName);
							strcpy_s(SupplyCode, AllDonation[i].SupplyCode);
							strcpy_s(Donator, AllDonation[i].Donator);
						}
					}
				}

				if (strcmp(SupplyName,"")==0) {
					printf("Error detected! Donation Code: %s     Distributed: %lf\n", AllDist[i2].DonationCode, AllDist[i2].QuantityDistributed);
				}
				else {
					printf("%-25s %-15s %-20s %-25lf\n", SupplyName, SupplyCode, Donator, AllDist[i2].QuantityDistributed);
				}
			}
		}
		printf("\n\nPress any key to back to menu...");
	}
	
	if (choice == 4) {
		char* DonationText = ReadDonationFromFile();
		Donation* AllDonationPtr = Donation_ConvertTextToStruct(DonationText);
		Donation AllDonation[MAX_RECORD_COUNT];
		for (int x = 0; x < MAX_RECORD_COUNT; x++)
			AllDonation[x] = AllDonationPtr[x];
		char* DistText = ReadDistributionFromFile();
		Dist* AllDist = Dist_ConvertTextToStruct(DistText);

		printf("\n             All Distributed Donations (accumulated)  \n");
		printf("           ===========================================\n\n");
		printf("%-25s %-15s %-20s %-25s\n", "Supply Name", "Supply Code", "Donator Name", "Quantity Distributed (mil)");
		printf("%-25s %-15s %-20s %-25s\n", "===========", "===========", "============", "==========================");

		Dist AllDist2[MAX_RECORD_COUNT];
		int counter = 0;   //This will store final size of AllDist2
		int counter2 = 0;  //This will store final size of AllDist
		for (int i = 0; i < MAX_RECORD_COUNT; i++) {
			if (AllDist[i].QuantityDistributed == -1) {
				break;
			}

			bool Duplicated = false;
			for (int i2 = 0; i2 < MAX_RECORD_COUNT; i2++) {
				if (AllDist2[i2].QuantityDistributed == -1) {
					break;
				}
				if (strcmp(AllDist[i].DonationCode, AllDist2[i2].DonationCode) == 0) {
					Duplicated = true;
					AllDist2[i2].QuantityDistributed += AllDist[i].QuantityDistributed;
				}
			}
			if (!Duplicated) {
				strcpy_s(AllDist2[counter].DonationCode, AllDist[i].DonationCode);
				AllDist2[counter].QuantityDistributed = AllDist[i].QuantityDistributed;
				counter++;
			}
			counter2++;
		}

		int i, j;
		Dist Temp;
		for (i = 0; i < counter2; i++)
		{
			for (j = i + 1; j < counter2; j++)
				if (AllDist2[i].QuantityDistributed < AllDist2[j].QuantityDistributed)
				{
					Temp = AllDist2[i];
					AllDist2[i] = AllDist2[j];
					AllDist2[j] = Temp;
				}
		}

		for (int i2 = 0; i2 < MAX_RECORD_COUNT; i2++) {
			if (AllDist2[i2].QuantityDistributed == -1) {
				break;
			}
			else {
				char SupplyName[30] = "";
				char SupplyCode[20];
				char Donator[30];

				for (int i = 0; i < MAX_RECORD_COUNT; i++) {
					if (AllDonation[i].QuantityReceived == -1) {
						break;
					}
					else {
						char temp[1024] = "";
						strcat_s(temp, 1024, AllDonation[i].Donator);
						strcat_s(temp, 1024, "-");
						strcat_s(temp, 1024, AllDonation[i].SupplyCode);
						if (strcmp(AllDist2[i2].DonationCode, temp) == 0) {
							strcpy_s(SupplyName, AllDonation[i].SupplyName);
							strcpy_s(SupplyCode, AllDonation[i].SupplyCode);
							strcpy_s(Donator, AllDonation[i].Donator);
						}
					}
				}

				if (SupplyName == "") {
					printf("Error detected! Donation Code: %s     Distributed: %lf\n", AllDist2[i2].DonationCode, AllDist2[i2].QuantityDistributed);
				}
				else {
					printf("%-25s %-15s %-20s %-25lf\n", SupplyName, SupplyCode, Donator, AllDist2[i2].QuantityDistributed);
				}
			}
		}
		printf("\n\nPress any key to back to menu...");
	}

	return;
}