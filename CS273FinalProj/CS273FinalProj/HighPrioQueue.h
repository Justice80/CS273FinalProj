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
	std::vector<DoctorQ*> doctor_queue;
	std::priority_queue<Patients*> the_queue;
public:
	HighPrioQ() {}
	void set_Doctors(std::vector<DoctorQ*> Doctors) {
		for (int i = 0; i < Doctors.size(); i++) {
			this->doctor_queue.push_back(Doctors[i]);
		}
	}
	void set_Hospital(HospitalQ* Hospital) { this->hospital_queue = Hospital; }
	void update(int time) {
		if ((!hospital_queue->the_queue.empty()) && hospital_queue->the_queue.front()->get_severityLevel().front() > 10) {
			Patients *p = hospital_queue->the_queue.front();
			hospital_queue->the_queue.pop();
			the_queue.push(p);
		}

		//loop through vector of doctors check to see if theyre free
		if ((!the_queue.empty()))
			for (int i = 0; i < doctor_queue.size(); i++) {
				if (doctor_queue[i]->the_queue.empty()) {
					Patients* p = the_queue.top();
					std::map<std::string, Patients>::iterator it = patient_Map.find(p->get_name());
					the_queue.pop();
					hospital_queue->increment_num_served();
					p->start_Treatment(time);
					it->second.start_Treatment(time);
					doctor_queue[i]->the_queue.push(p);
					doctor_queue[i]->set_serviceTime();
					break;
				}
			}

	}	

	friend class LowPrioQ;
};

#endif
