//--------------------------------------------------------------------
// CS215 Project 1 Fall 2020 Section 002
//--------------------------------------------------------------------
// Author: Andrew Tackett
// Date: 10/1/2020
// Description: This program will be used as an ATM that can track transactions using functions and arrays
// Assistance: Amanda Jones helped me with some problems in my main function, inacting those functions.
//-------------------------------------------------------------------

#include <iomanip> //needed for setw and setprecision
#include <iostream> //needed for cout 
#include <string> //needed for strings and getline 
#include <fstream> //needed to read and write to files
using namespace std; //needed for cin and cout 


//Here I have all of my constants for the project, these include the constants for the max number of accounts and transactions, as well as admin 
//parameters, also the max balance made, and the NOT_FOUND condition. I also went ahead and made the files constants, so if they needed to be 
//changed it would be easier.
const int MAX_ACCOUNTS = 5;
const int MAX_TRANS = 7;
const int MAX_BALANCE = 99999;
const string adminUser = "admin";
const int adminPin = 9999;
const int NOT_FOUND = -1;
const string inputAccounts = "acctsIn.txt";
const string outputAccounts = "acctsOut.txt";
const string outputTrans = "transactions.txt";


//Here is my first structure for an account, it contains a string for the account number and account name, it also has an integer for the account
//pin and a double for the account balance since this deals with money.
struct account {
	string accountNum = "";
	string accountName = "";
	int accountPin = 0;
	double accountBalance = 0;
};

//My second structure is similar, and has a character for the code given by the menu option, and a string to associate to the account number,
//also given is the double amount of the transaction and balance since both are in money.
struct transaction {
	char transCode = ' ';
	string accountNumber = "";
	double transAmount = 0;
	double transBalance = 0;
};

//---------------------------------------------------------
//						displayLogo
//---------------------------------------------------------

//Here is my first function, this being the name of the program and the person who made it, the menu DOES LINE up by the way.
//This is a joke. 
void displayLogo() {
	cout << "+------------------------------------------------------+" << endl;
	cout << "|           This Menu Doesn't Line up Bank ATM         |" << endl;
	cout << "|                   By: Andrew Tackett                 |" << endl;
	cout << "+------------------------------------------------------+" << endl;
}

//---------------------------------------------------------
//						startup
//---------------------------------------------------------


//This functions is a bool because it returns a true or false. This is used to start the ATM up and read the resource file given, which is the
//inputAccounts constant. It will check for that file, open it, read the data, and then use it in the program, if it isn't opened, the ATM will
//shut down. If it is able to be read, then the data will use a for loop to get the account number, Balance, Pin, and Name. It will then close
//the file.
bool startup(account acct[], int & numAccounts) {
	ifstream fin;
	fin.open(inputAccounts);
	if (fin.fail()) {
		cout << "Unable to open input file " << inputAccounts << " !" << endl;
		cout << "ATM shut down." << endl;
		return true;
	}
	else {
		cout << "Account data read!" << endl << endl;
		fin >> numAccounts;
		for (int i = 0; i < numAccounts; i++) {
			fin >> acct[i].accountNum >> acct[i].accountBalance >> acct[i].accountPin;
			if (fin.peek() == ' ') fin.ignore();
			getline(fin, acct[i].accountName);
		}
		return false;
	}
	fin.close();
}

//---------------------------------------------------------
//						search
//---------------------------------------------------------

//This function will search using the NOT_FOUND constant and the found variable that we made local here. This will use linear search for an array,
//and use a for loop to catch the array being searched.
int search(account acct[], int numAccounts, string accountNumber) {
	int found = NOT_FOUND;
	for (int i = 0; i < numAccounts; i++) {
		if (acct[i].accountNum == accountNumber) {
			found = i;
		}
	}
	return found;
}

//---------------------------------------------------------
//						addTrans
//---------------------------------------------------------

//This function will continously add the number of transactions until it hits the MAX_TRANS, after that it use the else part of the if.
void addTrans(transaction trans[], int & numTrans, char transCode, string accountNumber, double transAmount, double transBalance) {
	
	if (numTrans < MAX_TRANS) {
		trans[numTrans].transCode = transCode;
		trans[numTrans].accountNumber = accountNumber;
		trans[numTrans].transAmount = transAmount;
		trans[numTrans].transBalance = transBalance;
		numTrans++;
	}
	else {
		cout << "No more transactions can be added!" << endl;
	}
}

//---------------------------------------------------------
//						getMaintOption
//---------------------------------------------------------

//This function will be used to display the maintenance menu that the admin utilizes. Then using the local variable, "option" it will determine if
//the option is between 1 and 8 and use that valid option, if it is less than 1 or greater than 8, then a message will display saying that the 
//option is invalid.
int getMaintOption() {
	int option;
	cout << "------------------ MAINTENANCE MENU ------------------" << endl;
	cout << "1. Add new account   5. Print current accounts" << endl;
	cout << "2. Remove account    6. Print current transactions" << endl;
	cout << "3. Shut down ATM     7. Sort Accounts by Account Number" << endl;
	cout << "4. Exit Maintenance  8. Sort Accounts by Name" << endl;
	cout << "Enter option: ";
	cin >> option;
	while (option < 1 || option > 8) {
		cout << "Invalid Option. Try again!" << endl;
		cout << "Enter option: ";
		cin >> option;
	}
	return option;
}

//---------------------------------------------------------
//						askAcctData
//---------------------------------------------------------

//This function will ask for the account data and then take that data from the user, this is based on the admin's reponse and will use the responses
//to put into a new account. If the user isn't an admin, only the account number and account pin will be asked.
void askAcctData(account & acct) {
	
	cout << "Enter account number:    ";
	cin >> acct.accountNum;
	cout << "Enter account name:      ";
	if (cin.peek() == '\n') cin.ignore();
	getline(cin, acct.accountName);
	cout << "Enter account PIN:       ";
	cin >> acct.accountPin;
	cout << "Enter account balance:   ";
	cin >> acct.accountBalance;
	
}

//---------------------------------------------------------
//						addAcct
//---------------------------------------------------------

//In this function we will add an account based on what the admin asks and enters. It makes sure that the number of accounts does not exceed the 
//MAX_ACCOUNTS and then will initiate the askAcctData function and increment the number of accounts
void addAcct(account acct[], transaction trans[], int &numAccounts, int &numTrans) {

	if (numAccounts < MAX_ACCOUNTS && numTrans < MAX_TRANS) {
		askAcctData(acct[numAccounts]);
		cout << "New account added!" << endl;
		addTrans(trans, numTrans, 'A', acct[numAccounts].accountNum, 0 , acct[numAccounts].accountBalance);
		numAccounts++;
	}
	else if (numAccounts == MAX_ACCOUNTS) {
		cout << "No more accounts may be added!" << endl;
	}
	else {
		cout << "No more transactions may be added!" << endl;
	}

}

//---------------------------------------------------------
//						removeAcct
//---------------------------------------------------------

//In this function, the admin will remove the account by asking for the account number and then search for the account using the search function
//after that it will remove the account with a for loop.
void removeAcct(account acct[], transaction trans[], int & numAccounts, int & numTrans) {

	string accountNumber;
	int found;

	if (numTrans < MAX_TRANS) {
		
		cout << "Enter account number: ";
		cin >> accountNumber;
		found = search(acct, numAccounts, accountNumber);
		if (found == NOT_FOUND) {
			cout << "No account with account number " << accountNumber << " found!" << endl;
		}
		else {
			addTrans(trans, numTrans, 'R', accountNumber, acct[found].accountBalance, 0);
			cout << "Account removed!" << endl;
			for (int i = found; i < numAccounts - 1; i++) {
				acct[i] = acct[i + 1];
			}
			numAccounts--;
		}

	}
	else {
		cout << "No more transactions may be added!" << endl;
	}
	
}

//---------------------------------------------------------
//						printAccts
//---------------------------------------------------------

//In this function, the admin chooses to print the accounts and their information with the total number of accounts.
void printAccts(account acct[], int numAccounts) {

	cout << "--------------------------------------------------------------------" << endl;
	cout << "Account Num  Balance  PIN  Name " << endl;
	cout << "------------ -------- ---- -----------------------------------------" << endl;
	for (int i = 0; i < numAccounts; i++) {
		cout << left << setw(12) << acct[i].accountNum << right << setw(9) << acct[i].accountBalance << " "
			 << right << setw(4) << acct[i].accountPin << " " << left << setw(30) << acct[i].accountName << endl;
	}
	cout << "--------------------------------------------------------------------" << endl;
	cout << "Number of accounts = " << numAccounts;
	cout << endl;
}

//---------------------------------------------------------
//						printTrans
//---------------------------------------------------------

//This function is basically just like the previous function but prints the transactions with their information instead.
void printTrans(transaction trans[], int numTrans) {
	cout << "--------------------------------------------" << endl;
	cout << "Account Num  Trans Trans Amt Balance " << endl;
	cout << "-----------  ----- --------- ---------------" << endl;
	for (int i = 0; i < numTrans; i++) {
		cout << left << setw(12) << trans[i].accountNumber << "   " << setw(1) << trans[i].transCode << "  "
			<< right << setw(9) << trans[i].transAmount << "  " << left << setw(9) << trans[i].transBalance << endl;
	}
	cout << "--------------------------------------------------------------------" << endl;
	cout << "Number of Transactions = " << numTrans;
	cout << endl;
}

//---------------------------------------------------------
//						sortByName
//---------------------------------------------------------

//This function will sort the arrays based on their name, using a nested for loop and if loop.
void sortByName(account acct[], int & numAccounts) {

	for (int i = 0; i < numAccounts - 1; i++) {
		for (int j = i + 1; j < numAccounts; j++) {
			if (acct[i].accountName > acct[j].accountName) {
				account r = acct[i];
				acct[i] = acct[j];
				acct[j] = r;
			}
		}
	}
	cout << "Accounts sorted by Name." << endl;
}

//---------------------------------------------------------
//						sortByNum
//---------------------------------------------------------

//This function will sort the accounts by their number using the same method as the sortByName.
void sortByNum(account acct[], int& numAccounts) {

	for (int i = 0; i < numAccounts - 1; i++) {
		for (int j = i + 1; j < numAccounts; j++) {
			if (acct[i].accountNum > acct[j].accountNum) {
				account r = acct[i];
				acct[i] = acct[j];
				acct[j] = r;
			}
		}
	}
	cout << "Accounts sorted by Number." << endl;
}

//---------------------------------------------------------
//						doMaintenance
//---------------------------------------------------------

//This function us a bool function that returns a true/false value, then it will use the getMainOption function to ask the user to pick an option.
//Then based on this option, you will do a certain operation and activate a certain function.
bool doMaintenance(account acct[], transaction trans[], int& numAccounts, int& numTrans) {
	int maintOption;
	cout << endl;
	maintOption = getMaintOption();
	

	while (maintOption != 4) {

		if (maintOption == 1) {
			addAcct(acct, trans, numAccounts, numTrans);
			
		}
		else if (maintOption == 2) {
			removeAcct(acct, trans, numAccounts, numTrans);
			
		}
		else if (maintOption == 3) {
			return true;
			
		}
		else if (maintOption == 5) {
			printAccts(acct, numAccounts);
			
		}
		else if (maintOption == 6) {
			printTrans(trans, numTrans);
			
		}
		else if (maintOption == 7) {
			sortByNum(acct, numAccounts);
			
		}
		else {
			sortByName(acct, numAccounts);
		
		}
		cout << endl;
		maintOption = getMaintOption();
		cout << endl;
	}

	return false;

}

//---------------------------------------------------------
//						getCustOption
//---------------------------------------------------------

//This function will return an integer based on the user's option, then it will check to see that the user's option is within the options and 
//activate a particular function based on their option.
int getCustOption() {
	int transOption;
	
	cout << endl;
	cout << "---- Transaction Menu ----" << endl;
	cout << "1. Deposit Funds" << endl;
	cout << "2. Withdraw Funds" << endl;
	cout << "3. Balance Inquiry" << endl;
	cout << "4. Cancel Transaction" << endl;
	cout << "Enter option: ";
	cin >> transOption;
	

	while (transOption < 1 || transOption > 4) {
		cout << "Invalid option! Try again! " << endl;
		cout << "Enter option: ";
		cin >> transOption;
	}
	
	return transOption;

}

//---------------------------------------------------------
//						doWithdrawal
//---------------------------------------------------------


//This function will do a withdrawal based on the amount and account accessed. It checks to see that the balance isn't less than $0 and isn't 
//greater than the amount of money in the user's account.
void doWithdrawal(account & acct, transaction trans[], int & numTrans) {

	double withdrawalAmt;


	cout << left << setw(25) << "Current Balance:" << acct.accountBalance << endl;
	cout << left << setw(25) << "Enter withdrawal amount: ";
	cin >> withdrawalAmt;
	
	while (withdrawalAmt < 0 || withdrawalAmt > acct.accountBalance) {
		cout << "Invalid amount. Enter a number 0.00 to " << acct.accountBalance << endl;
		cout << "Enter withdrawal amount: ";
		cin >> withdrawalAmt;
	}
	
	acct.accountBalance = acct.accountBalance - withdrawalAmt;
	cout << "Your new balance is:     " << acct.accountBalance << endl;
	addTrans(trans, numTrans, 'W', acct.accountNum, withdrawalAmt, acct.accountBalance);

}

//---------------------------------------------------------
//						doDeposit
//---------------------------------------------------------


//This function will do a deposit based on the amount entered by the user, the while loop will check to see whether the amount is less than zero or
//greater than the MAX_DEPOSIT amount.
void doDeposit(account & acct, transaction trans[], int& numTrans) {

	double depositAmt;

	cout << left << setw(25) << "Current Balance: " << acct.accountBalance << endl;
	cout << left << setw(25) << "Enter deposit amount: ";
	cin >> depositAmt;
	
	while (depositAmt < 0 && depositAmt > MAX_BALANCE) {
		cout << "Invalid amount. Enter a number 0.00 to " << acct.accountBalance << endl;
		cout << "Enter deposit amount: ";
		cin >> depositAmt;
	}

	acct.accountBalance = acct.accountBalance + depositAmt;
	cout << "Your new balance is:     " << acct.accountBalance << endl;
	addTrans(trans, numTrans, 'D', acct.accountNum, depositAmt, acct.accountBalance);

}

//---------------------------------------------------------
//						serveCustomer
//---------------------------------------------------------


//This function will serve the customer, the customer option will then determine which operation is enacted.
void serveCustomer(account & acct, transaction trans[], int & numTrans) {

	int customerOption;
	customerOption = getCustOption();
	
	if (customerOption == 1) {
		
		doDeposit(acct, trans, numTrans);

	}
	else if (customerOption == 2) {
		doWithdrawal(acct, trans, numTrans);
	}
	else if (customerOption == 3) {
		cout << "Your current balance is: " << acct.accountBalance << endl;
		addTrans(trans, numTrans, 'I', acct.accountNum, 0, acct.accountBalance);
	}
	else {
		cout << "Transaction cancelled!" << endl;

	}
}

//---------------------------------------------------------
//						writeAccounts
//---------------------------------------------------------

//In this function it writes the accounts to the outputAccounts constant which is the file acctsOut.txt
void writeAccts(account acct[], int& numAccounts) {

	ofstream fout;
	
	fout.open(outputAccounts);
	if (fout.fail()) {
		cout << "Unable to open input file " << outputAccounts << " !" << endl;
		cout << "ATM shut down." << endl;
		return;
	}
	else {
		fout << numAccounts << endl;
		
			for (int i = 0; i < numAccounts; i++) {
				fout << acct[i].accountNum << " " << acct[i].accountBalance << " " << acct[i].accountPin << " " << acct[i].accountName << " " << endl;
				
			}
				
	}
	fout.close();
}

//---------------------------------------------------------
//						writeTrans
//---------------------------------------------------------

//This function basically does the same as writeAccounts, but with the transactions and uses the outputTrans constant which is the transactions.txt
void writeTrans(transaction trans[], int& numTrans) {

	ofstream fout;

	fout.open(outputTrans);
	if (fout.fail()) {
		cout << "Unable to open input file " << outputTrans << " !" << endl;
		cout << "ATM shut down." << endl;
	}
	else {
		fout << numTrans << endl;

			for (int i = 0; i < numTrans; i++) {
				fout << trans[i].transCode << " " << trans[i].accountNumber << " " << trans[i].transAmount << " " << trans[i].transBalance << endl;
			}
		
	}
	fout.close();
}


//---------------------------------------------------------
//						doShutdown
//---------------------------------------------------------

//This function is activated when the admin initiates the shutdown in the maintanence menu. It will write the account data and transaction data to
//the two out texts
void doShutdown(account acct[], transaction trans[], int& numAccounts, int& numTrans) {

	writeAccts(acct, numAccounts);
	writeTrans(trans, numTrans);
	cout << "Account data written to " << outputAccounts << endl;;
	cout << "Transaction data written to " << outputTrans << endl;
	cout << "ATM shut down." << endl;

}

//---------------------------------------------------------
//						getAcct
//---------------------------------------------------------

//This function will find the account that is being searched through the pin and number. it initiates the search function and sets it equal to
//the found account to either find it or not find the account.
int getAcct(account acct[], int& numAccounts) {
	string accountNumber;
	int accountPin;
	int found;

	displayLogo();
	cout << "Enter an account number: ";
	cin >> accountNumber;
	cout << "Enter an account Pin:    ";
	cin >> accountPin;
	found = search(acct, numAccounts, accountNumber);
	if (accountNumber == adminUser && accountPin == adminPin) {
		found = -2;
	}
	else if (found >= 0 && acct[found].accountPin == accountPin) {
		found = found;
	}
	else {
		found = NOT_FOUND;
	}
	return found;
}


//---------------------------------------------------------
//						main
//---------------------------------------------------------

//This function is the main that is used to initiate certain functions and what is printed to the debug console, here we declare the specific 
//parameters and what is needed to initiate those functions. I also have variables declared in the main that are local to that main.
int main() {

	account acct[MAX_ACCOUNTS];
	transaction trans[MAX_TRANS];
	int numAccounts = 0;
	int numTrans = 0;
	int startupReturn;
	int doMaintanenceReturn = false;
	int accountIndex;
	
	cout << fixed << setprecision(2) << endl;

	displayLogo();
	startupReturn = startup(acct, numAccounts);
	if (startupReturn == false) {
		while (doMaintanenceReturn == false) {
			accountIndex = getAcct(acct, numAccounts);
			if(accountIndex == -2){
				doMaintanenceReturn = doMaintenance(acct, trans, numAccounts, numTrans);
			}
			else if (accountIndex == NOT_FOUND) {
				cout << "Invalid account number and/or pin!" << endl;
			}
			else if (accountIndex >= 0){
				if (numTrans < MAX_TRANS) {
					serveCustomer(acct[accountIndex], trans, numTrans);
					cout << endl;
				}
				else {
					cout << "Sorry, this ATM is unavailable. Please check back later." << endl;
				}
			}
		}
	}

	doShutdown(acct, trans, numAccounts, numTrans);

	
	system("pause");
	return 0;

}