#ifndef PATIENTS_H_
#define	PATIENTS_H_

#include <string>

class Patients{
private:
	std::string name;
	int num_visits;
public:
	void incriment_visits() {}
	int arrivalTime() {}
	int waitingTime() {}
	int dischargeTime() {}
};

#endif
