#include <conio.h>
#include <stdio.h>
#include <Windows.h>

//Function Prototypes
int get_menu_choice();
void NewDonation(), AllDonationAndDistribution(), UpdateDonation(), SearchDonation();

void main() {
	int result = get_menu_choice();
	do {
		switch (result) {
			case 1:
				NewDonation();
				break;
			case 2:
				UpdateDonation();
				break;
			case 3:
				SearchDonation();
				break;
			case 4:
				AllDonationAndDistribution();
				break;
			case 5:
				break;
			default:
				printf("\n\nInvalid input! Please try again!");
		}
		_getch();
		result = get_menu_choice();
	} while (result != 5);

	printf("\n\nGood Bye! Good Luck!");
	_getch();
}

int get_menu_choice() {
	system("cls");
	printf("\n     ========================================");
	printf("\n       COVID-19 DONATION MANAGEMENT SYSTEM   ");
	printf("\n     ========================================\n");
	printf("\n               Main Menu   \n");
	printf("           =================\n");
	printf("         1. Inventory Creation\n");
	printf("         2. Update Donation Quantities\n");
	printf("         3. Search Donation\n");
	printf("         4. List Donation and Distribution\n");
	printf("         5. Exit Program\n\n");

	int choice;
	printf("    Please select one (1-5): ");
	scanf_s("%d", &choice); while (getchar() != '\n');

	return choice;
}