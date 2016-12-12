//I think this is finished
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
	std::priority_queue<Patients*> the_queue;
public:
	HighPrioQ() {}
	void set_Doctors(DoctorQ* Doctors) { this->doctor_queue = Doctors; }
	void set_Hospital(HospitalQ* Hospital) { this->hospital_queue = Hospital; }
	void update(int time) {
		if ((!hospital_queue->the_queue.empty()) && hospital_queue->the_queue.front()->get_severityLevel() > 10) {
			Patients *p = hospital_queue->the_queue.front();
			hospital_queue->the_queue.pop();
			the_queue.push(p);
		}

		//loop through vector of doctors check to see if theyre free
		if (doctor_queue->the_queue.empty()) {
			Patients* p = the_queue.top();
			the_queue.pop();
			doctor_queue->the_queue.push(p);
			doctor_queue->set_serviceTime();
			p->start_Treatment(time);
		}

	}	

	friend class LowPrioQ;
};

#endif
