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
	std::vector<DoctorQ*> doctor_queue;
	std::vector<NurseQ*> nurse_queue;
	HighPrioQ* highPrio;
	std::priority_queue<Patients*> the_queue;
public:
	LowPrioQ() {}
	void set_Doctors(std::vector<DoctorQ*> Doctors) { 
		for (int i = 0; i < Doctors.size(); i++) {
			this->doctor_queue.push_back(Doctors[i]);
		}
	}
	void set_Nurses(std::vector<NurseQ*> Nurses) { 
		for (int i = 0; i < Nurses.size(); i++) {
			this->nurse_queue.push_back(Nurses[i]);
		}
	}
	void set_Hospital(HospitalQ* Hospital) { this->hospital_queue = Hospital; }
	void set_HighPrioQ(HighPrioQ* HighPQ) { this->highPrio = HighPQ; }
	void update(int time) {
		if ((!hospital_queue->the_queue.empty()) && hospital_queue->the_queue.front()->get_severityLevel().front() <= 10) {
			Patients* p = hospital_queue->the_queue.front();
			hospital_queue->the_queue.pop();
			the_queue.push(p);
		}
		//high priority patients are taken care of low priority patients can go to doctor or nurse
		if (!the_queue.empty()) {
			int nurse_index = 0;
			if (highPrio->the_queue.empty()) {
				for (int i = 0; i < doctor_queue.size(); i++) {
					for (int j = 0; j < nurse_queue.size(); j++) {
						if (doctor_queue[i]->the_queue.empty() || nurse_queue[j]->the_queue.empty()) {
							if (nurse_queue[j]->the_queue.empty() && !the_queue.empty()) {
								Patients* p = the_queue.top();
								std::map<std::string, Patients>::iterator it = patient_Map.find(p->get_name());
								the_queue.pop();
								hospital_queue->increment_num_served();
								nurse_queue[j]->the_queue.push(p);
								nurse_queue[j]->set_serviceTime();
								it->second.start_Treatment(time);
								p->start_Treatment(time);
								nurse_index = j;
								break;
							}
							else if (doctor_queue[i]->the_queue.empty() && nurse_queue[nurse_index]->the_queue.empty()) {
								Patients* p = the_queue.top();
								std::map<std::string, Patients>::iterator it = patient_Map.find(p->get_name());
								the_queue.pop();
								hospital_queue->increment_num_served();
								doctor_queue[i]->the_queue.push(p);
								doctor_queue[i]->set_serviceTime();
								it->second.start_Treatment(time);
							}
						}
					}
				}
			}
			//high priority still being worked on by doctors patients can go only to nurse
			if ((!highPrio->the_queue.empty())) {
				for (int k = 0; k < nurse_queue.size(); k++) {
					if ((nurse_queue[k]->the_queue.empty())) {
						Patients* p = the_queue.top();
						std::map<std::string, Patients>::iterator it = patient_Map.find(p->get_name());
						the_queue.pop();
						hospital_queue->increment_num_served();
						nurse_queue[k]->the_queue.push(p);
						nurse_queue[k]->set_serviceTime();
						it->second.start_Treatment(time);
					}
				}
			}
		}
	}

};

#endif
