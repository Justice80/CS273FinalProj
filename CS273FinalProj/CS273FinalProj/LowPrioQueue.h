//I think this is finished
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
	HighPrioQ* highPrio;
	std::priority_queue<Patients*> the_queue;
public:
	LowPrioQ() {}
	void set_Doctors(DoctorQ* Doctors) { this->doctor_queue = Doctors; }
	void set_Nurses(NurseQ* Nurses) { this->nurse_queue = Nurses; }
	void set_Hospital(HospitalQ* Hospital) { this->hospital_queue = Hospital; }
	void set_HighPrioQ(HighPrioQ* HighPQ) { this->highPrio = HighPQ; }
	void update(int time) {
		if ((!hospital_queue->the_queue.empty()) && hospital_queue->the_queue.front()->get_severityLevel() <= 10) {
			Patients* p = hospital_queue->the_queue.front();
			hospital_queue->the_queue.pop();

			the_queue.push(p);
		}
		//high priority patients are taken care of low priority patients can go to doctor or nurse
		if (!the_queue.empty()) {
			if (highPrio->the_queue.empty() && (doctor_queue->the_queue.empty() || nurse_queue->the_queue.empty())) {
				if (nurse_queue->the_queue.empty()) {
					Patients* p = the_queue.top();
					the_queue.pop();
					hospital_queue->increment_num_served();
					nurse_queue->the_queue.push(p);
					nurse_queue->set_serviceTime();
					p->start_Treatment(time);
				}
				else if (doctor_queue->the_queue.empty()) {
					Patients* p = the_queue.top();
					the_queue.pop();
					hospital_queue->increment_num_served();
					doctor_queue->the_queue.push(p);
					doctor_queue->set_serviceTime();
					p->start_Treatment(time);
				}
			}
			//high priority still being worked on by doctors patients can go only to nurse
			if ((!highPrio->the_queue.empty()) && (nurse_queue->the_queue.empty())) {
				Patients* p = the_queue.top();
				the_queue.pop();
				hospital_queue->increment_num_served();
				nurse_queue->the_queue.push(p);
				nurse_queue->set_serviceTime();
				p->start_Treatment(time);
			}
		}
	}

};

#endif
