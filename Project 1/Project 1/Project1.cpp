//--------------------------------------------------------------------
// CS215 Project 1 Fall 2020 Section 002
//--------------------------------------------------------------------
// Author: Andrew Tackett
// Date: 8/25/20
// Description: This program will act like a gas pump and calculate the amount of gas per car and customer.
// Assistance: I received help from Amanda Jones with formatting pump-start up, some broken if-loops, and shutdown format.
//-------------------------------------------------------------------

#include <iomanip> //needed for setwidth
#include <iostream> //needed for cout 
#include <string> //needed for string and getline
#include <Windows.h> //needed for the wait or sleep function
using namespace std;

const int sleep_interval = 1000;

int main() {

	//Here are my constants for the project, I have different types of such as doubles, int, and strings.
	//I have made the variables based on the number and price of all octanes, along with a member check system that factors in a discount on cost.
	double numHOctane, priceHOctane, numMOctane, priceMOctane, numLOctane, priceLOctane;
	int i;
	int numRewards;
	double ppgDiscount;
	double ppg;
	string memberCheck;
	string shutdown;
	string selectedOctane;
	double numGallons;
	int numPump;
	double pumpCount;
	double total;
	double highGallonsSold = 0, mediumGallonsSold = 0, lowGallonsSold = 0;
	double highDollars = 0, mediumDollars = 0, lowDollars = 0;
	double totalDollarsSold;

	//Here I have the set the precision of all of the decimals/doubles.
	cout << fixed << setprecision(2);

	//This is the pump start up menu that is given, here we can answer the numbr of gallons for each octane, and the price of each, after that we have
	//a for loop that prints dots to simulate the pump starting up.
	cout << "+---------------------------------------------+" << endl;
	cout << ":                Pump Start Up                :" << endl;
	cout << "+---------------------------------------------+" << endl;
	cout << "Enter gallons in pump and today's price per gallon for: " << endl;
	cout << "High octane:   ";
	cin >> numHOctane >> priceHOctane;
	cout << "Medium octane: ";
	cin >> numMOctane >> priceMOctane;
	cout << "Low octane:    ";
	cin >> numLOctane >> priceLOctane;
	cout << "Starting Pump";
	for (i = 0; i < 4; i++) {
		Sleep(sleep_interval);
		cout << ".";
	}
	Sleep(sleep_interval);
	cout << endl;
	cout << endl;

	//This is the beginning of a sentinal controlled while loop that will check to see if the member has entered a shutdown, without it, the rest will run.
	while (memberCheck != "shutdown") {

		cout << "+-------------------------------------------------------+" << endl;
		cout << ":       Welcome To HuckaBilly's Self Serve!             :" << endl;
		cout << ":              Andrew Tackett, Owner                    :" << endl;
		cout << "+-------------------------------------------------------+" << endl;
		cout << "Are you a rewards customer? (Y/N): ";
		cin >> memberCheck;

		//This nested if loop will verify the answer given by the user to see if they are a member or not, given that, it will apply a discount to the
		//cost of the octane gas or no, also it will check to see if the user enters a wrong answer and correct them on it.
		if (memberCheck != "shutdown") {

				if (memberCheck == "Y" || memberCheck == "y") {
					cout << "Enter customer rewards number:   ";
					cin >> numRewards;
					ppgDiscount = (numRewards % 10);
					ppgDiscount = (ppgDiscount + 1) / 100;
					cout << "Price Per Gallon Discount:      $" << ppgDiscount << endl;
					cout << endl;
				}
				else if(memberCheck == "N" || memberCheck == "n") {
					ppgDiscount = 0;
					cout << "Price Per Gallon Discount:      $" << ppgDiscount << endl;
					cout << endl;

				}
				while (memberCheck != "Y" && memberCheck != "y" && memberCheck != "N" && memberCheck != "n") {
					cout << "Please Enter Y or N." << endl;
					cout << "Are you a rewards customer? (Y/N): ";
					cin >> memberCheck;


				}

				//This prints the prices per gallon for each octane
			cout << "Prices per Gallon: " << endl;
			cout << "High Octane:      $" << priceHOctane - ppgDiscount << endl;
			cout << "Medium Octane:    $" << priceMOctane - ppgDiscount << endl;
			cout << "Low Octane:       $" << priceLOctane - ppgDiscount << endl;
			cout << endl;

			//Here the user is asked to pick the octane that they would like and then the while loop will check to see if the answer contradicts the options
			cout << "Select Octane (H/M/L): ";
			cin >> selectedOctane;
			cout << endl;

			while (selectedOctane != "H" && selectedOctane != "h" && selectedOctane != "M" && selectedOctane != "m" && selectedOctane != "L" && selectedOctane != "l") {
				cout << "Error. Please enter H, M, L!" << endl;
				cout << "Select Octane (H/M/L): ";
				cin >> selectedOctane;
				cout << endl;
			}

			//This nested if loop will activate based on the user's answer, for all 3 however, if the number of gallons is a negative number, it will 
			//generate a random number, and then print that number and pump that gas
			if (selectedOctane == "H" || selectedOctane == "h") {
				cout << "Enter number of gallons (-1 to Fill it up): ";
				cin >> numGallons;
				ppg = priceHOctane;
				if (numGallons < 0) {
					numGallons = rand() % 8 + 1;
					cout << "Sensor reports " << numGallons << " gallons needed to fill up" << endl;
					cout << endl;
				}
				//This if loop will check to see if the number of gallons requested exceeds the number of the particular octane
				if (numGallons > numHOctane) {
					cout << "Sorry, our tank is nearly empty. We only have " << numHOctane << " gallons avaiable." << endl;
					numGallons = numHOctane;
				}
				//for all three if statements, calculations will be made for the the number of octane sold and the amount paid by the user.
				if (numHOctane > 0) {
					numHOctane = numHOctane - numGallons;
					highDollars = highDollars + (priceHOctane * numGallons);
					highGallonsSold = highGallonsSold + numGallons;
				}
			}
			else if (selectedOctane == "M" || selectedOctane == "m") {
				cout << "Enter number of gallons (-1 to Fill it up): ";
				cin >> numGallons;
				ppg = priceMOctane;
				if (numGallons < 0) {
					numGallons = rand() % 8 + 1;
					cout << "Sensor reports " << numGallons << " gallons needed to fill up" << endl;
					cout << endl;
				}
				if (numGallons > numMOctane) {
					cout << "Sorry, our tank is nearly empty. We only have " << numMOctane << " gallons avaiable." << endl;
					numGallons = numMOctane;
				}
				if (numMOctane > 0) {
					numMOctane = numMOctane - numGallons;
					mediumDollars = mediumDollars + (priceMOctane * numGallons);
					mediumGallonsSold = mediumGallonsSold + numGallons;
				}
			}
			else {
				cout << "Enter number of gallons (-1 to Fill it up): ";
				cin >> numGallons;
				ppg = priceLOctane;
				if (numGallons < 0) {
					numGallons = rand() % 8 + 1;
					cout << "Sensor reports " << numGallons << " gallons needed to fill up" << endl;
					cout << endl;
				}
				if (numGallons > numLOctane) {
					cout << "Sorry, our tank is nearly empty. We only have " << numLOctane << " gallons avaiable." << endl;
					numGallons = numLOctane;
				}
				cout << endl;
				if (numLOctane > 0) {
					numLOctane = numLOctane - numGallons;
					lowDollars = lowDollars + (priceLOctane * numGallons);
					lowGallonsSold = lowGallonsSold + numGallons;
				}
			}

			//Here we have the total amount spent by the amount of money spent with the amount of octane purchased.
			totalDollarsSold = highDollars + mediumDollars + lowDollars;

			//Here we have a if and for loop that will simulate pumping gas in increments.
			cout << "Pumping Gas..." << endl;
			if (numGallons > 0) {
				numPump = numGallons * 2;
				pumpCount = 0;
				for (i = 0; i < numPump; ++i) {
					Sleep(sleep_interval * 2);
					pumpCount = pumpCount + 0.5;
					cout << pumpCount << " gallons pumped..." << endl;
				}
				if (pumpCount < numGallons) {
					cout << numGallons << " gallons pumped..." << endl;
				}
			}
			cout << endl;

			//Here we have the reciept for each individual purchase, the octane will print based on the user's answer.
			//After that the price per gallon is made based on the price per gallon made previously.
			cout << "-----------Your Receipt---------------" << endl;
			cout << "Octane:                          ";
			if (selectedOctane == "H" || selectedOctane == "h") {
				cout << "High" << endl;
			}
			else if (selectedOctane == "M" || selectedOctane == "m") {
				cout << "Medium" << endl;
			}
			else {
				cout << "Low" << endl;
			}
			cout << "Price Per Gallon:                $" << ppg << endl;
			total = ppg * numGallons;
			cout << "Total:                           $" << total << endl;
			cout << "Thank you for visiting Huckabilly's!!" << endl;
			cout << endl;
			cout << "--------------------------------------" << endl;

			system("pause");
			cout << endl;
			cout << endl;
		}
	}
	cout << endl;
	cout << endl;

	//Here is the shutting down portion of the pump, here it will print the octanes, how many gallons have been sold, dollars spent/sold, and the gallons remaining.
	cout << "Shutting down pump";
	cout << endl;
	cout << "------------------------------------------------------" << endl;
	cout << " Octane  Gallons Sold  Dollars Sold  Gallons Remaining" << endl;
	cout << "-------- ------------  ------------  -----------------" << endl;
	cout << left << setw(15) << "High" << right << setw(7) << highGallonsSold << "  $" << right << setw(11) << highDollars << right << setw(18) << numHOctane << endl;
	cout << left << setw(15) << "Medium" << right << setw(7) << mediumGallonsSold << "  $" << right << setw(11) << mediumDollars << right << setw(18) << numMOctane << endl;
	cout << left << setw(15) << "Low" << right << setw(7) << lowGallonsSold << "  $" << right << setw(11) << lowDollars << right << setw(18) << numLOctane << endl;
	cout << left << setw(24) << "TOTAL" << "$" << right << setw(11) << totalDollarsSold;
	return 0;
}