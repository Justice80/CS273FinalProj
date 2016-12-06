#ifndef HospitalSim_H_
#define HospitalSim_H_

#include <iostream>
#include <string>
#include <stdexcept>
#include <limits>
#include <ios>
#include "Random.h"

class Simulator {
private:
	int total_time;
	int clock;

	//WaitingRoomQ* waiting_room;
	//HighPrioQ* high_prio;
	//LowPrioQ* low_prio;
	//NurseQ* nurse_queue;
	//DoctorQ* doctor_queue;

	int read_int(const std::string &prompt, int low, int high)
	{
		if (low >= high) // invalid range
			throw std::invalid_argument("invalid range specified");

		std::cin.exceptions(std::ios_base::failbit);
		int num = 0;
		while (true) {
			try {
				while (true) {
					std::cout << prompt;
					std::cin >> num;
					if (num >= low && num <= high) { // within the specified range
						std::cout << std::endl;
						return num;
					}
				}
			}
			catch (std::ios_base::failure) {
				std::cout << "Bad numeric string -- try again\n";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<int>::max(), '\n');
			}
		}
	}

public:
	Simulator() {
		
		//new queues

	}

	void enter_data() {

		std::cout << "Welcom" << std::endl;
		//more welcome message 

		int Rate = read_int("Please enter the patient arrival rate (patients/hour): ", 1, 59);
		double arrival_Rate = Rate / 60.0;

		total_time = read_int("Please enter the simulation time (hours): ", 1, INT_MAX);
		total_time *= 60;

		//set the arrival rate for new patients in waiting room queue

		//set other queues to referenece each other
		

	}

	void run_sim() {

		for (clock = 0; clock < total_time; ++clock) {
			//update each queue
		}

	}

	void stats() {

		std::cout << "Number of patients served in the Hospital waiting room: " << endl;
		//show stats

	}

};

#endif