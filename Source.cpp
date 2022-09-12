// ---------------------------------------------------------------
// Programming Assignment:	Group B Project
// Developer:			    Stephen Blevins
// Date Written:		    07/14/2021
// Purpose:					Financial Calculator
// ---------------------------------------------------------------

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;


int main()
{
	// Initialize inputs
	float interestRate, loanAmmount, monthlyPayment, months, annualRate, decimalRate, monthArr[360];
	ofstream savedData("data.txt");
	ifstream data("data.txt");

	int choice = 0, loanLength;
	string line;

	// Ask the user how much they want to borrow
	cout << ("What is the ammount borrowed?") << endl;
	cin >> loanAmmount;

	while (1)
	{
		if (cin.fail() || loanAmmount <= 0) //we can add more rules here
		{
			cin.clear();
			cout << "You have entered wrong input" << endl;
			cin >> loanAmmount;
		}
		if (!cin.fail() && loanAmmount > 0)
			break;
	}
	
	// Ask the user how long of a mortgage do they want
	// Did not use an if statement for length of time
	// Because the user could use this for a car loan etc. other than 15 or 30 year
	cout << ("Choose a loan length of 1-30 years. How many years is your loan for? ") << endl;
	cin >> loanLength;


	//Check for a loan length between 1 and 30
	while (1)
	{
		if (cin.fail() || loanLength <= 0 || loanLength > 30) //we can add more rules here
		{
			cin.clear();
			cout << "You have entered wrong input for the loan length\n" << endl;
			cout << ("Choose a loan length of 1-30 years. How many years is your loan for? ") << endl;
			cin >> loanLength;
		}
		if (!cin.fail() && loanLength > 0 && loanLength <= 30)
			break;
	}

	// Make sure to break the years into months
	months = loanLength * 12;

	// Ask user for their interest rate
	/*if (loanLength == 15)
	{
		interestRate = 3;
	}
	else
	{
		interestRate = 6;
	}*/

	cout << ("What is your interest rate?");
	cin >> interestRate;

	// Divide the interest rate by 100 to transform it to a decimal point value
	decimalRate = interestRate / 100;

	// For amortization, you must divide the interest rate by months to get the annual rate
	annualRate = decimalRate / 12;

	// Using an amortization formula to calculate monthly payments
	monthlyPayment = loanAmmount / ((pow(1 + annualRate, months) - 1) / (annualRate * (pow(1 + annualRate, months))));

	// Display monthly payment with fixed decimal points
	cout << setprecision(2) << fixed << ("Borrowing $") << loanAmmount << (" at a ") << interestRate << ("%") << (" interest rate, your monthly payment would be $") << monthlyPayment << endl;
	

	float balance = loanAmmount;
	float interest = loanAmmount * annualRate;

	for (int i = 0; i < months; i++)
	{
		interest = balance * annualRate;
		float principal = monthlyPayment - interest;
		balance = balance - principal;
		if (balance < 0)
			balance = 0;
		monthArr[i] = balance;
	}

	cout << "Your balance after each payment per month: " << endl;
	for (int i = 0; i < months; i++)
	{
		if (monthArr[i] == 0)
			break;
		cout << i + 1 << ": " << monthArr[i] << endl;
	}
	cout << "Congratulations, your loan has been paid off!\n" << endl;
	
	while (choice != 3) {
		cout << "\n1) Save Data" << endl;
		cout << "2) Retrieve Data" << endl;
		cout << "3) Exit Program" << endl;
		cout << "Please choose an option from above: ";
		cin >> choice;
		switch (choice) {
		case 1:
			if (savedData.is_open()) {
				savedData << "********************************" << endl;
				savedData << "Your loan ammount is: $" << loanAmmount << endl;
				savedData << "Your loan length in years is: " << loanLength << endl;
				savedData << "Your monthly payment is: $" << monthlyPayment << endl;
				savedData << "Your interest rate is: " << interestRate << "%" << endl;
				savedData.close();
				cout << "Your loan information has been saved!\n" << endl;
				break;
			}
			else
				cout << "Unable to open file" << endl;
				break;
		case 2:
			if (data.is_open()) {
				while (getline(data, line)) {
					cout << line << endl;
				}
				data.close();
				break;
			}
			else
				cout << "Unable to open file" << endl;
				break;
		case 3:
			break;
		}
	}

}

