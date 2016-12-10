#ifndef LOWPRIO_Q_H_
#define LOWPRIO_Q_H_
#include <queue>
#include "Patients.h"
#include "Random.h"
#include "HospitalQueue.h"
#include "Staff.h"

class LowPrioQ {
private:
	HospitalQ* hospital_queue;
	DoctorQ* doctor_queue;
	NurseQ* nurse_queue;
	std::priority_queue<Patients*> the_queue;
public:
	LowPrioQ() {}
	void set_Doctors(DoctorQ* Doctors) {}
	void set_Nurses(NurseQ* Nurses) {}
	void set_Hospital(HospitalQ* Hospital_queue) {}
	void update(int time) {} //continue to work on
};

#endif
