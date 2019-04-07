#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include"bank.h"
#include<iostream>
#include<queue>
#include <vector>

using std::vector;
using std::queue;


TEST_CASE("Functions")
{
	//CostumerGeneratior Function
	SECTION("nextMinute from CostumerGenerator")
	{
		FixedCG frontDoor(queue<int>({ 2 }), queue<int>({ 3 }));
		REQUIRE(frontDoor.nextMinute() == nullptr);
		REQUIRE(frontDoor.nextMinute() == nullptr);
		Customer * next = frontDoor.nextMinute();
		REQUIRE(next != nullptr);
		REQUIRE(next->helpTime == 3); 
		REQUIRE(frontDoor.nextMinute() == nullptr);


	}



	//*****************************************
	//Bank functions 

	SECTION("nextMin from Bank")
	{
		queue <int> waitTime;
		{
			waitTime.push(1);
			waitTime.push(2);
			waitTime.push(2);
			waitTime.push(2);
			waitTime.push(4);
			waitTime.push(3);
		} 
		queue <int> Helptime; 
		{
			Helptime.push(1);
			Helptime.push(2);
			Helptime.push(2);
			Helptime.push(2);
			Helptime.push(4);
			Helptime.push(3);
		}
		FixedCG test(waitTime, Helptime);
		FixedCG testptr = test; 
		Bank helptime(30,test);
		helptime.nextMin();
		REQUIRE(helptime.gettime() == 1);

	}


	SECTION("Simulate from Bank")
	{
		queue <int> waitTime;
		{
			waitTime.push(1);
			waitTime.push(2);
			waitTime.push(2);
			waitTime.push(2);
			waitTime.push(4);
			waitTime.push(3);
		}
		queue <int> Helptime;
		{
			Helptime.push(1);
			Helptime.push(2);
			Helptime.push(2);
			Helptime.push(2);
			Helptime.push(4);
			Helptime.push(3);
		}
		
		//FixedCG test(waitTime, Helptime);
		FixedCG frontDoor(queue<int>({ 2 }), queue<int>({ 3 }));
		//Bank testing(20, test);
		Bank testing(20, frontDoor);
		testing.simulate();
		REQUIRE(testing.getmaxWTime() == 0);
		REQUIRE(testing.getMaxCustomerCount() == 1);

	}
}
