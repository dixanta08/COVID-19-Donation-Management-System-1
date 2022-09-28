#pragma once

#define MAX_FILE_LENGTH 3000
#define MAX_RECORD_COUNT 100

//Structs
struct donation {
	char SupplyName[30];
	char SupplyCode[20];
	char Donator[30];
	int NoOfShipment = 0;
	double QuantityReceived = -1.0;
};
typedef struct donation Donation;

struct distribution {
	char DonationCode[40];
	double QuantityDistributed = -1.0;
};
typedef struct distribution Dist;