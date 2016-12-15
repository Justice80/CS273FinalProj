//I think this is finished
#ifndef HOSPITAL_Q_H_
#define HOSPITAL_Q_H_
#include "Patients.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <utility>
#include <map>
#include "Random.h"

extern Random rand_num;
extern std::map<std::string, Patients> patient_Map;
extern std::vector<std::string> fnames;
extern std::vector<std::string> lnames;

class HospitalQ {
private:
	double arrival_rate;
	int num_served;
	std::queue<Patients*> the_queue;
public:
	void set_arrival_rate(double arrival_rate) {
		this->arrival_rate = arrival_rate;
	}
	void increment_num_served() {
		this->num_served += 1;
	}
	int get_num_served() { return num_served; }

	void update(int clock) {

		if (the_queue.empty()) {
			if (rand_num.next_double() < arrival_rate) {

				srand(clock);
				int severityRate = rand() % 10 + 1;
				int severity;

				if (severityRate <= 7) {
					severity = rand() % 10 + 1;
				}

				else if (severityRate > 7 && severityRate < 10) {
					severity = rand() % 5 + 11;
				}

				else {
					severity = rand() % 4 + 16;
				}

				std::string name;

				int FRand = rand() % 2000;
				int LRand = rand() % 1000;
				std::string fname = fnames[FRand];
				std::string lname = lnames[LRand];
				name = fname + " " + lname;

				std::map<std::string, Patients>::iterator it = patient_Map.find(name);
				if (it == patient_Map.end()) {		//patient is not found in the map 
					Patients* p = new Patients(fname, lname);
					patient_Map.insert(make_pair(p-> get_name(), *p));
					it = patient_Map.find(name);
					it->second.addVisit(severity);
					p->addVisit(severity);
					it->second.set_arrivalTime(clock);
					p->set_arrivalTime(clock);
					the_queue.push(p);
				}
				else {								//patient is found in the map
					Patients* p = new Patients(fname, lname);
					it->second.addVisit(severity);
					p->addVisit(severity);
					it->second.set_arrivalTime(clock);
					p->set_arrivalTime(clock);
					the_queue.push(p);
				}
			}
		}
		
	}

	friend class HighPrioQ;
	friend class LowPrioQ;
};

#endif
