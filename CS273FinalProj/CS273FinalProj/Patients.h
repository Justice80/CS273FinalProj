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
public:
	Patients(std::string first_name, std::string surname) : numOfVisits(0) {
		this->name = first_name +" " + surname;
	}
	std::string get_name() { return name; }

	void addVisit(int severity) {
		SeverityLevel.push_back(severity);
		numOfVisits++;
	}

	int get_NumVisits() { return numOfVisits; }

	void start_Treatment(int clock) { this->startTreatment = clock; }

	int get_treatmentStart() { return startTreatment; }

	int get_severityLevel() { return SeverityLevel.front(); }
};

#endif
