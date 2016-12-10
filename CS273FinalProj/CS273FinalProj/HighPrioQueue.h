#ifndef HIGHPRIO_Q_H_
#define HIGHPRIO_Q_H_
#include <queue>
#include "Patients.h"
#include "Random.h"
#include "HospitalQueue.h"
#include "Staff.h"

class HighPrioQ {
private:
	HospitalQ* hospital_queue;
	DoctorQ* doctor_queue;
	NurseQ* nurse_queue;
	std::priority_queue<Patients*> the_queue;
public:
	HighPrioQ() {}
	void set_Doctors(DoctorQ* Doctors) {}
	void set_Hospital(HospitalQ* Hospital_queue) {}
	void update(int time) {} //continue to work on
};

#endif
