#include<iostream>
#include<string>
#include<queue>
#include <random>
#include <ctime>
#include "bank.h"


using namespace std; 


//How long can the bank be opened? 
//Do we need a memeber variable or function to determine that? 



/**
* Returns an integer 1, 2, 3, or 4 uniformly at random
*/
int randInt1To4() {
	// shared random number generator (seeded with clock time)
	static default_random_engine randEngine(time(0));
	// shared uniform distribution
	static uniform_int_distribution<int> dist1To4(1, 4);
	// return a sample
	return dist1To4(randEngine);

}

Customer* CustomerGenerator::nextMinute()
{
	remainingTime--; 
	if (remainingTime == 0)
	{
		// resets the time until the next customer with a new random integer between 1 and 4
		remainingTime = randInt1To4(); 
	
		//a new costumer 
		Customer * nCusPtr = new Customer; 
		nCusPtr->helpTime = randInt1To4(); //we assign a number for it to get help 
		return nCusPtr;
		
	}

	return nullptr; 
}

Bank::Bank(const int & workDayLength)
{
	workDay = workDayLength; 
	timeSinceBO = 0; 
	cur = nullptr; 
	CustomerGenerator frontDoor;
	customerCount = 0;
	maxWTime = 0;
 
}

void Bank::nextMin()
{
	timeSinceBO++; 
	//if there is a customer being helped, 
	//decrement the amount of help time still required for that customer;
	if (cur)
	{
		(cur->helpTime)--;

		
		//if the customer has no more minutes required, the customer leaves
		if (cur->helpTime == 0)
		{

			//we remove the costumer
			if (!cosLine.empty())
			{
				delete cur;

				cur = cosLine.front();
				cosLine.pop();

				//description of what is happening
				cout << "Customer leaving, and new one being helped" << endl;
				//****************************************************
			}
			else
				cur = nullptr;

		}
		
	}
	//this will tell us what the maximun wait time is 
	if (timeSinceBO < workDay)
	{
		Customer*  temp;

		temp= frontDoor.nextMinute();
		if (temp != nullptr)
		{
			//description of what is happening
			cout << "New customer arrived" << endl; 
			//**************************************
			customerCount++;
			maxWTime += temp->helpTime;
			temp->arrivalTime = timeSinceBO;





			//assig
			cur = cosLine.front();
		}


	}

}



//include 
void Bank::simulate()
{
	Bank test(workDay);

	do {
		test.nextMin();
	} while (test.timeSinceBO <= test.workDay);

}




int Bank::getmaxWTime() const
{
	return maxWTime;
}

int Bank::getCustomerCount() const
{
	return customerCount; 
}