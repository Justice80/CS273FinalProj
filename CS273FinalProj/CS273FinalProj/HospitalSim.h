//I think this is finished
#ifndef HOSPITALSIM_H_
#define HOSPITALSIM_H_
#include <fstream>
#include <iostream>
#include <string>
#include <stdexcept>
#include <limits>
#include <ios>
#include <queue>
#include <map>
#include <utility>
#include "HospitalQueue.h"
#include "HighPrioQueue.h"
#include "LowPrioQueue.h"
#include "Staff.h"
#include "Random.h"
#include <fstream>

Random rand_num;
std::map<std::string, Patients> patient_Map;
std::vector<std::string> fnames;
std::vector<std::string> lnames;

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
	std::vector<DoctorQ*> doc_Vec;
	std::vector<NurseQ*> nurse_Vec;

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

	void populate_name_vectors() {
		std::string name;
		std::ifstream FnameFile, LnameFile;
		FnameFile.open("C:\\Users\\Justice Martinez\\Documents\\GitHub\\CS273FinalProj\\residents_of_273ville.txt");
		LnameFile.open("C:\\Users\\Justice Martinez\\Documents\\GitHub\\CS273FinalProj\\surnames_of_273ville.txt");

		if (!FnameFile.fail()) {
			while (std::getline(FnameFile, name)) {			//both while loops allocate names from files to vectors
				fnames.push_back(name);
			}

		}
		if (!LnameFile.fail()) {
			while (std::getline(LnameFile, name)) {
				lnames.push_back(name);
			}
		}
	}

public:
	Simulator() {
		//new queues
		int numStaff = read_int("How many Doctors work in this Hospital? ", 1, 4);

		for (int i = 0; i < numStaff; i++) {
			doctor_queue = new DoctorQ();
			doc_Vec.push_back(doctor_queue);
		}

		numStaff = read_int("How many Nurses work in this Hospital? ", 1, 6);

		for (int i = 0; i < numStaff; i++) {
			nurse_queue = new NurseQ();
			nurse_Vec.push_back(nurse_queue);
		}
		

		Hospital_queue = new HospitalQ();
		high_prio = new HighPrioQ();
		low_prio = new LowPrioQ();
		this->populate_name_vectors();

	}

	void enter_data() {

		std::cout << "Welcome to this hospital simulation\n\n";

		int Rate = read_int("Please enter the patient arrival rate (patients/hour): ", 1, 59);
		double arrival_Rate = Rate / 60.0;

		total_time = read_int("Please enter the simulation time (hours)[a max of 168 hours(a week)]: ", 1, 168);
		total_time *= 60;

		//set the arrival rate for new patients in hospital(waiting room) queue
		Hospital_queue->set_arrival_rate(arrival_Rate);

		//set other queues to referenece each other
		high_prio->set_Hospital(Hospital_queue);
		high_prio->set_Doctors(doc_Vec);
		low_prio->set_Hospital(Hospital_queue);
		low_prio->set_Doctors(doc_Vec);
		low_prio->set_Nurses(nurse_Vec);
		low_prio->set_HighPrioQ(high_prio);


	}

	void run_sim() {
		for (clock = 0; clock < total_time; ++clock) {
			Hospital_queue->update(clock);
			high_prio->update(clock);
			low_prio->update(clock);
			for (int i = 0; i < doc_Vec.size(); i++) {
				doc_Vec[i]->update(clock);
			}
			for (int j = 0; j < nurse_Vec.size(); j++) {
				nurse_Vec[j]->update(clock);
			}
		}

	}

	void stats() {
		int choice;
		std::string name;
		bool exit = false;
		int avg_wait = 0;
		int num_served = 0;
		std::cout << "Number of patients served in the Hospital waiting room: " << Hospital_queue-> get_num_served() <<std::endl;
		for (std::map<std::string, Patients>::iterator it = patient_Map.begin(); it != patient_Map.end(); it++) {
			if (it->second.get_wait_time() != -1) {
				avg_wait += it->second.get_wait_time();
				num_served++;
			}
		}
		std::cout << "Average visit time: " << avg_wait/num_served << " minutes. " <<std::endl;

		do {
			choice = read_int("1 - Show list of patients\n2 - Get patient recond\n3 - Exit\nEnter your choice and press enter: ", 1, 4);

			switch (choice)
			{
			case 1:
				std::cout << "List of patients & number of visits: " << std::endl;
				for (std::map<std::string, Patients>::iterator it = patient_Map.begin(); it != patient_Map.end(); it++) {
					std::cout << it->first << " " << it->second.get_NumVisits() << std::endl;
				}
				break;
			case 2:
				std::cout << "Type the name of the patient: ";
				std::cin.ignore();
				std::getline(std::cin, name);

				for (std::map<std::string, Patients>::iterator it = patient_Map.begin(); it != patient_Map.end(); it++) {
					if (it->first == name) {
						std::cout << "The severity level of this patients injury was ";
						for (int i = 0; i < it->second.get_severityLevel().size(); i++) {
							std::cout << it->second.get_severityLevel()[i] << std::endl;
						}
					}
				}
				break;
			case 3:
				exit = true;
				break;
			default:
				break;
			}
		} while (exit == false);
		
	} 

};

#endif