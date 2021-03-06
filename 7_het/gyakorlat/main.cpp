// MultithreadedQueueSimulation.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <chrono>
#include <deque>
#include <list>
#include <algorithm>
#include <thread>
#include <stdlib.h> // srand, rand miatt

#include "people.h"

void initialize_random_seed(){
	srand(
		std::chrono::system_clock::to_time_t(
			std::chrono::system_clock::now()
		)
	); // rand() random generator seed-je mindig mas lesz
}

void printCustomers(const std::deque<Customer>& cus) {
	for (const auto& cu : cus) {
		std::cout << "\t\t" << cu << std::endl;
	}
}

void printCustomers(const std::list<Teller>& tels, const std::deque<Customer>& cus) {
	for (const auto& tel : tels) {
		if (tel.isBusy())
			tel.printServicedCustomers();
	}
	for (const auto& cu : cus) {
		std::cout << "\t\t" << cu << std::endl;
	}
}

int main()
{
	std::deque<Customer> customers;
	std::list<Teller> tellers;
	typedef std::list<Teller>::iterator TellIt;

	tellers.push_back(Teller(customers));
	
	initialize_random_seed();
	
	while (true) {
		std::cout << "===== New tick =====" << std::endl;
		
		// Random szamu (0 es 4 kozotti) ugyfel, random igenyelt (1 es 15 mp kozotti) idovel
		for (int i = 0; i < rand() % 5; i++) { // rand() 0 es RAND_MAX kozotti szamot ad vissza, ezert modulozzuk
			customers.push_back(Customer(std::chrono::seconds(rand() % 15 + 1)));
		}
		std::cout << '{' << tellers.size() << " tellers}" << std::endl;
		std::cout << "\tCustomers to service:" << std::endl;
		printCustomers(customers);

		std::deque<std::thread*> ttr;

		// A kiszolgalok most 5 masodpercig kiszolgaljak az ugyfeleket
		for (TellIt i = tellers.begin(); i != tellers.end(); i++) {
			(*i).run();
		}

		std::cout << "\tCustomers remaining:" << std::endl;
		printCustomers(tellers, customers);

		// Ha tobb mint 2x annyi ugyfel van mint kiszolgalo, letrehozunk meg 1 kiszolgalot:
		if (customers.size() / tellers.size() > 2) {
			tellers.push_back(Teller(customers));
		}
		// Ha tobb mint 1 kiszolgalo van es nincs 2x annyi ugyfel mint kiszolgalo, 1 kiszolgalo pihenhet
		if (tellers.size() > 1 && customers.size() / tellers.size() < 2) {
			for (TellIt i = tellers.begin(); i != tellers.end(); i++) {
				if (!(*i).isBusy()) {
					tellers.erase(i);
					break;
				}
			}
		}

		if (
			customers.empty() /* &&
			std::find_if(
				tellers.begin(),
				tellers.end(),
				[](const Teller& t) -> bool { return t.isBusy(); }) == tellers.cend() */
			) { break; }

		std::cin.get();
	}
}


