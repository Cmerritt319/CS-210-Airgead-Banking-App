/*
 * Driver.h
 *
 *  Created on: Oct 1, 2020
 *      Author: Clayton
 */

#ifndef DRIVER_H_
#define DRIVER_H_

class Driver {
public:
	//Default Constructor
	Driver();
	//Menu options
	int menuDisplay();
	void projectionScreen();
	/*
	 * User input options. I Wanted to try to make a more dynamic type of input, like a catch all,
	 * which you can do, but I didn't know enough about "generic input" to make a single function
	 * that did this, so I just did two user input functions - one for doubles (AKA Money), the other
	 * for ints (AKA Months and percentages).
	 */
	double getMoneyInput();
	int getNumberInput();
	//Interest earned calculator
	void InterestCalculations(double InitialInvestment, double MonthlyDeposit, int Interest, int NumYears);

private:
	double InitialInvestment;
	double MonthlyDeposit;
	int Interest;
	int NumYears;

};

#endif /* DRIVER_H_ */
