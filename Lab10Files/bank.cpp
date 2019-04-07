#include<iostream>
#include<string>
#include<queue>
#include <random>
#include <ctime>
#include "bank.h"


using namespace std; 




/**
* Returns an integer 1, 2, 3, or 4 uniformly at random
*/
int randInt1To4() {
	// shared random number generator (seeded with clock time)
	static default_random_engine randEngine(static_cast<unsigned int>( time(0)));
	// shared uniform distribution
	static uniform_int_distribution<int> dist1To4(1, 4);
	// return a sample
	return dist1To4(randEngine);

}

Customer* CustomerGenerator::nextMinute()
{
	//if is less than 0, wich means we have not initialize it then ..
	if (remainingTime < 0) 
	{
		remainingTime = getNextDelay();

	} 

	//if the remaining time ( the minutes left before the next customer comes) is 0
	if (remainingTime == 0)
	{
		// resets the time until the next customer with a new random integer between 1 and 4
		remainingTime = getNextDelay(); 
	
		//Create a new costumer 
		Customer * nCusPtr = new Customer; 
		nCusPtr->helpTime = getHelpNeeded(); //we assign the amount oof minutes it will need help 
		
		return nCusPtr;
		
	}
	else
	{
		remainingTime--;
		return nullptr;
	}

	
}

//the first one
int CustomerGenerator::getNextDelay()
{
	return randInt1To4();
}

int CustomerGenerator::getHelpNeeded()
{
	return randInt1To4();
}




// we override the virtual functions 
 int FixedCG::getNextDelay()
{
	int temp = delays_.front();
	delays_.pop();
	delays_.push(temp);

	return temp;
}

 int FixedCG::getHelpNeeded()
{
	int temp = needs_.front();
	needs_.pop();
	needs_.push(temp);

	return temp;
}









Bank::Bank(const int & workDayLength, CustomerGenerator& cust) :frontDoor(&cust)
{
	workDay = workDayLength; 
	timeSinceBO = 0; 
	cur = nullptr; 
	maxCustomerCount = 0;
	maxWTime = 0;
 
}




void Bank::nextMin()
{

	//PART 1 
	//increment the number of minutes since opening
	timeSinceBO++; 



	//PART 2
	//if there is a customer being helped:
	if (cur)
	{
		//we decrement the amount of help time (since its been a minute) 
		(cur->helpTime)--;

		//if the customer has no more minutes in helpTime, the customer leaves
		if (cur->helpTime == 0)
		{
			delete cur;
			cur = nullptr;
		}
		
	}



	//PART 3
	//If the time since the bank opened is less than the work day  
	if (timeSinceBO < workDay)
	{
		//create a temp
		Customer*  temp;

		//we call the nextMinute() function from the CustomerGenerator 
		temp = frontDoor->nextMinute();

		//nextMinute() retuneda new Custormer (meaning it did not retuned a nullptr)
		if (temp != nullptr)
		{
			//description of what is happening is displayed 
			cout << "New customer arrived" << endl; 
			//**************************************
			
			//We assign the arrival time
			temp->arrivalTime = timeSinceBO;
			//add a new customer to the line 
			cusLine.push(temp);
		}



		//PART 4
		//We check of the size is line is greated to the maximun customer count we assign it to it
		if (cusLine.size() > maxCustomerCount)
			maxCustomerCount = cusLine.size();

	}



	//PART 5
	//if there are customers in line and no customer currently being helped
	if (cusLine.size() > 0 && cur == nullptr)
	{
		//the current customer will be the one in front of the line 
		cur = cusLine.front();

		//we pop him/her from the waiting line
		cusLine.pop();
		//description of what is happening is displayed
		cout << "A customer is leaving and new one is being helped" << endl;
		//********************************************************************


		//we update maxWaitTime if necessary
		if ((timeSinceBO - cur->arrivalTime) > maxWTime)
		{
			maxWTime = timeSinceBO - cur->arrivalTime;
		
		}
	}
}



//it simulates a day at the bank with the minutes assign by the usser 
void Bank::simulate()
{
	//Bank test(workDay);

	//A loop that repeats as long as the mank is still open
	do {
		nextMin();
	} while (timeSinceBO < workDay);

	// check to see if day is over
	// loop while cur call next min.


	//Displaay the maximu customer count and the maximun wait time
	cout << "The maximun number of customers in line were: "<< getMaxCustomerCount() << endl;
	cout << "The maximun number of minutes a customer had to wait in line were: " <<getmaxWTime() << endl; 
	
}




int Bank::getmaxWTime() const
{
	return maxWTime;
}

int Bank::gettime()
{
	return timeSinceBO;
}



int Bank::getMaxCustomerCount() const
{
	return maxCustomerCount; 
}