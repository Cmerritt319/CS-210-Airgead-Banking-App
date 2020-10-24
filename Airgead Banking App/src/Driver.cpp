/*
 * Driver.cpp
 *
 *  Created on: Oct 1, 2020
 *      Author: Clayton
 */
#include <iostream>
#include <iomanip>
#include <cctype>
#include <stdexcept>
#include <vector>
#include <limits>
#include "Driver.h"


using namespace std;
/*
 * Initial Menu Display. As the user inputs data, next menu item pops up for the user to input data.
 */
int Driver::menuDisplay(){

	cout << setw(33) << setfill('*') << "*" << endl;
	cout << setw(10) << setfill('*') << "*";
	cout << " Data Input ";
	cout << setw(11) << setfill('*') << "*" << endl;
	// Initial investment input
	cout << setw(28) << setfill(' ') << left << "Initial investment amount:";
	InitialInvestment = getMoneyInput();
	cout << "$";
	cout << fixed << setprecision(2) << InitialInvestment << endl;
	//
	// Monthly Deposit input
	cout << setw(28) << setfill(' ') << left << "Monthly deposit:";
	MonthlyDeposit = getMoneyInput();
	cout << "$";
	cout << fixed << setprecision(2) << MonthlyDeposit << endl;
	//
	// Interest Percentage input
	cout << setw(32) << setfill(' ') << left << "Annual interest:";
	Interest = getNumberInput();
	cout << "%" << Interest << endl;
	//
	//Investment Duration input
	cout << setw(32) << setfill(' ') << left << "Number of years:";
	NumYears = getNumberInput();
	cout << NumYears << endl;
	//cout << setw(28) << setfill(' ') << left << "Press any key continue..." << endl; // took this line out because in the system("pause"); code, its displayed anyway.
	/*
	 *  Researched how to "pause the program". This will work on windows, but not mac or unix.
	 *  to do this on mac, the following code needs to be system("read");. The more I read up on this
	 *  the more this seems to be an end user problem? dealing with compatibility sucks.
	 */
	system("pause");
	return 0;

}
void Driver::projectionScreen(){
	/*
	 * Basic display for outputs. Used \t to space things out a bit.
	 */
	cout << "   Balance and Interest with Additional Monthly Deposits" << endl; // 55 chars
	cout << setw(60) << setfill('=') << "=" << endl;
	cout << "Year\t" << "    Year End Balance\t" << "    Year end Earned Interest" << endl; // 45 chars
	InterestCalculations(this->InitialInvestment, this->MonthlyDeposit, this->Interest, this-> NumYears);

	cout << endl;
	cout << endl;

	cout << "   Balance and Interest without Additional Monthly Deposits" << endl; // 58 chars
	cout << setw(60) << setfill('=') << "=" << endl;
	cout << "Year\t" << "    Year End Balance\t" << "    Year end Earned Interest" << endl; // 45 chars
	InterestCalculations(this->InitialInvestment, 0, this->Interest, this-> NumYears);



}
void Driver::InterestCalculations(double InitialInvestment, double MonthlyDeposit, int Interest, int NumYears){
	int i;
	int j;
	int k;//<-This throws a warning in the compiler because it see's that I am using this int, while compound Interest is a double. NBD Still compiles.

	double newInvestmentAmount = InitialInvestment;
	double interest = Interest; //I had issues with this, needed to implicitly cast Interest as a double, otherwise wouldn't display calculations as double.
	double interestTotal= 0;
	const int NUM_MONTHS = 12; // Months in a year
	double compoundInterest;
	vector<double> interests; // used this to add the year end compound interest up and display it in the cout statement. You'll see later!


	/*
	//Variable Pass Checker:
	//This was added to make sure that my stuff is passed along thru the function.
	//Had some issues with my calculations, the following helped to isolate and fix them:
	cout << "Initial Investment: " << InitialInvestment << "\nMonthlyDeposit: " << MonthlyDeposit <<"\nInterest: " <<Interest<< "\nNumYears: " <<NumYears<< endl;
	cout << endl;
	*/

	/*
	 *Calculation:
	 *The following is the computational portion of the program. It calculates the interest the user will make over time
	 *The first for loop is setup to print out:
	 *1. Year number (i)
	 *2. Current account balance (newInvestmentAmount) after monthly computations have iterated over the course of the year in months.
	 *3. Interest earned that year (interestTotal) which is extracted from the interest vector.
	 *The Second for loop is set up to calculate the following on a monthly basis:
	 *1. New balance(newInvestmentAmount) after monthly deposit(MonthlyDeposit) is added
	 *2. Compounding interest (compoundInterest) on the New Balance(newInvestmentAmount) given the interest rate(interest/100) divided by number of months in a year(NUM_MONTHS)
	 *3. Adding compounding interest(compoundInterest) to the new balance(newInvestmentAmount)
	 *4. Storing the compounding interest(interests.push_back(compoundInterest)) for later so we can add it all up at years end.
	 */
	for(i=1; i<=NumYears; i++){
		for(j=1; j<=NUM_MONTHS; j++){
			newInvestmentAmount = (newInvestmentAmount+MonthlyDeposit);
			compoundInterest = newInvestmentAmount*((interest/100)/NUM_MONTHS);// <- this is where computational issues were happening Variable Pass Checker helped me find it.
			newInvestmentAmount = newInvestmentAmount + compoundInterest;
			interests.push_back(compoundInterest);
		}
		// Adds up all interest payments
		for(k=0; k<interests.size(); k++){//vector breakdown
				interestTotal = interests.at(k)+interestTotal;//vector
		}
		/*
		//Compound interest checker:
		//this was used to see how much compound interest was adding up to. could add another vector to see how much interest has been earned total
		//if we needed or wanted to.

		for(k=0; k<interests.size(); k++){
				cout << k << " $" << interests.at(k);
		}
		cout << endl;
		cout << endl;
		*/
		//Output text to the user
		cout << i << "\t    $" << newInvestmentAmount << "\t\t     $" << interestTotal << endl;;

		/*
		 Value Resets:
		 Added these value resets, to include a vector resize so that we have correct yearly interest numbers.
		 Without these, we would end up getting residual interest numbers. Used the compound interest checker to see
		 what the hell was happening.

		 - Without the interestTotal and CompoundInterest resets, the previous stored information is retained, leading
		   to incorrect yearly amounts being displayed(think, years prior interest being added to displayed total).
		   This fixes that.
		 - Without the interests vector resize to zero, the vector retains prior data, which results in the wrong
		   interest total. If I reset the vector contents to zero, reminance of the prior numbers are still stored
		   in the vector. Tried it. Resize gets rid of all stored information.
		 */
		interestTotal = 0;
		compoundInterest = 0;
		interests.resize(0);
	}
}

double Driver::getMoneyInput(){
	double userInput;
	cin >> userInput;
	/*
	Error Check:
	Added this to check for errors. If the input stream is bunged up with non numbers, the program will crash.
	While we can accept a negative a number, you can't deposit a negative number, so reject!
	I wanted to use a try{} catch{}, but this seemed more efficient as it doesnt allow the user to input bad
	data all together.
	 */
	while(!cin.good() || userInput < 0){ // In otherwords, if what cin gets is bad OR if userInput is less than zero, enter this loop
		cout << endl;
		//These statements report on what type of problem were having.
		if(!cin.good()){// if the user is inputting garbage other than numbers...
			cout << "ERROR: We're looking for numbers, not text. Try again: " << endl;
		}
		if(userInput < 0){// if the user is inputting negative numbers. We don't owe them money for using this program...
			cout << "ERROR: We're looking for a positive number here. We don't owe you money for using this! Try again buddy:" << endl;
		}

		//Clean the cin pipe!
		cin.clear();
		cin.ignore(LC_MAX, '\n');//this is the maximum double number you could possibly have.

		//Lets try again
		cin >> userInput;

	}
	return userInput;
}
int Driver::getNumberInput(){
	int userInput;
	cin >> userInput;
	/*
	// Error Check:
	// Added this to check for errors. If the input stream is bunged up with non numbers, the program will crash.
	// While we can accept a negative a number, you cant have a negative interest rate or go thru negative time. so reject!
	*/
		while(!cin.good() || userInput < 0){ // In otherwords, if what cin gets is bad OR if userInput is less than zero, enter this loop
			cout << endl;
			//These statements report on what type of problem were having.
			if(!cin.good()){// if the user is inputting garbage thats not numbers
				cout << "ERROR: We're looking for numbers, not text. Try again: " << endl;
			}
			if(userInput < 0){// if the user is trying to have a negative interest rate or go backwards in time
				cout << "ERROR: We're looking for a positive number here. Try again: " << endl;
			}

			//Clean the cin pipe!
			cin.clear();
			cin.ignore(LC_MAX, '\n');//this is the maximum double number you could possibly have.

			//Lets try again
			cin >> userInput;
		}
	return userInput;
}
Driver::Driver() {

}

