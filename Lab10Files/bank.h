#ifndef BANK_H
#define BANK_H
#include<iostream>
#include<string>
#include<queue>

using std::queue; 


struct Customer
{
	//record the time when the customer arrived in line
	int arrivalTime=0; //in minutes
	//keeps track of how many more minutes of help that customer will require.
	int helpTime=0; 

};




//It represents the stream of customers arriving at the front door of the bank 
class CustomerGenerator
{
private: 
	// it indicates the number of minutes left before the next customer
	int remainingTime =-1; 

public:
	// It decrements the number of minutes left  till the next customer
	Customer* nextMinute();



	virtual int getNextDelay();

	virtual int getHelpNeeded();
	
};





 //sub-class to be able to test; 
class FixedCG : public CustomerGenerator
{
private: 
	queue<int> delays_;
	queue<int> needs_;
public:

	FixedCG(queue<int> delays, queue<int> needs):delays_(delays), needs_(needs)
	{
	}

	virtual int getNextDelay() override;
	virtual int getHelpNeeded() override;
	
};






class Bank
{
private: 
	int workDay; //in minutes 
	int timeSinceBO; //in minutes 
	Customer * cur; //a pointer to a current Customer being helped (or null if none is being helped)
	std::queue<Customer*> cusLine; //the customer's line 
	CustomerGenerator *frontDoor;  //a reference to a CustomerGenerator object
	int maxCustomerCount;  //integer tracking the maximum amount of customers that where waiting in the line
	int maxWTime;  //integer tracking the maximum wait time 1 costumer had to wait

public:
	Bank(const int & workDayLength,CustomerGenerator & cust); //give a work dy length 
	void nextMin();
	void simulate(); //loop over minutes and work day 
	int getMaxCustomerCount() const;
	int getmaxWTime() const; 
	int gettime();
};









#endif // !BANK_H
