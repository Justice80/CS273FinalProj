//I think this is finished
#ifndef HOSPITAL_Q_H_
#define HOSPITAL_Q_H_
#include "Patients.h"
#include <fstream>
#include <vector>
#include <ctime>
#include <utility>
#include <map>
#include "Random.h"

extern Random rand_num;
extern std::map<std::string, Patients> patient_Map;

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
				int i = 0;

				srand(time(NULL));
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

				std::ifstream FnameFile, LnameFile;
				FnameFile.open("residents_of_273ville.txt");
				LnameFile.open("surname_of_273ville.txt");
				std::vector<std::string> fnames;
				std::vector<std::string> lnames;
				int randNum = rand() % 2000 + 1;
				while (FnameFile.good()) {			//both while loops allocate names from files to vectors
					getline(FnameFile, fnames[i]);
					i++;
				}
				i = 0;
				while (LnameFile.good()) {
					getline(LnameFile, lnames[i]);
					i++;
				}

				int FRand = rand() % 2000 + 1;
				int LRand = rand() % 1000 + 1;
				std::string fname = fnames[FRand];
				std::string lname = lnames[LRand];

				std::map<std::string, Patients>::iterator it = patient_Map.find(fname);
				if (it == patient_Map.end()) {		//patient is not found in the map 
					Patients* p = new Patients(fname, lname);
					patient_Map.insert(make_pair(fname, *p));
					p->addVisit(severity);
					the_queue.push(p);
				}
				else {								//patient is found in the map
					//auto p = (*it)->second;		?
					Patients* p = new Patients(fname, lname); //this creates a new patients
					p->addVisit(severity);
					the_queue.push(p);
				}
			}
		}
		
	}

	friend class HighPrioQ;
	friend class LowPrioQ;
};

#endif
