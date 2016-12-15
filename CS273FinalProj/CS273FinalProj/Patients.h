//I think this is finished
#ifndef PATIENTS_H_
#define	PATIENTS_H_

#include <string>

class Patients
{
private:
	std::string name;
	int numOfVisits;
	std::vector<int>SeverityLevel;
	int startTreatment;
	int arrivalTime;
	int discharge_time;
	int wait_time;

public:
	Patients(std::string first_name, std::string surname) : numOfVisits(0), discharge_time(-1), wait_time(-1) {
		this->name = first_name +" " + surname;
	}
	std::string get_name() { return name; }

	void addVisit(int severity) {
		SeverityLevel.push_back(severity);
		numOfVisits++;
	}

	int set_wait_time() { 
		wait_time = discharge_time - arrivalTime;
		return wait_time;
	}

	int get_wait_time() { return wait_time; }

	void set_dichargeTime(int clock) { this->discharge_time = clock; }

	void set_arrivalTime(int clock) { this->arrivalTime = clock; }

	int get_NumVisits() { return numOfVisits; }

	void start_Treatment(int clock) { this->startTreatment = clock; }

	int get_treatmentStart() { return startTreatment; }

	std::vector<int> get_severityLevel() { return SeverityLevel; }
};

#endif
