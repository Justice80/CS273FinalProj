#ifndef HOSPITALSIM_H_
#define HOSPITALSIM_H_

#include <iostream>
#include <string>
#include <stdexcept>
#include <limits>
#include <ios>
#include <queue>
#include "HospitalQueue.h"
#include "HighPrioQueue.h"
#include "LowPrioQueue.h"
#include "Staff.h"
#include "Random.h"

Random rand_num;

class Simulator {
private:
	int total_time;
	int clock;

	HospitalQ* Hospital_queue;
	HighPrioQ* high_prio;
	LowPrioQ* low_prio;
	Staff* staff_queue;
	NurseQ* nurse_queue;
	DoctorQ* doctor_queue;

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
		Staff* nurse_queue;
		Staff* doctor_queue;
		Hospital_queue = new HospitalQ();
		high_prio = new HighPrioQ();
		low_prio = new LowPrioQ();
		nurse_queue = new NurseQ();
		doctor_queue = new DoctorQ();

	}

	void enter_data() {

		std::cout << "Welcome to this hospital simulation\n\n";

		int Rate = read_int("Please enter the patient arrival rate (patients/hour): ", 1, 59);
		double arrival_Rate = Rate / 60.0;

		total_time = read_int("Please enter the simulation time (hours): ", 1, INT_MAX);
		total_time *= 60;

		//set the arrival rate for new patients in hospital(waiting room) queue
		Hospital_queue->set_arrival_rate(arrival_Rate);

		//set other queues to referenece each other
		high_prio->set_Hospital(Hospital_queue);
		high_prio->set_Doctors(doctor_queue);
		low_prio->set_Hospital(Hospital_queue);
		low_prio->set_Doctors(doctor_queue);
		low_prio->set_Nurses(nurse_queue);


	}

	void run_sim() {

		for (clock = 0; clock < total_time; ++clock) {
			high_prio->update(clock);
			low_prio->update(clock);
		}

	}

	void stats() {

		std::cout << "Number of patients served in the Hospital waiting room: " << std::endl;
		//show stats

	}

};

#endif