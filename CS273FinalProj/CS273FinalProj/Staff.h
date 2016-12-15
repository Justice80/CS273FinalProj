#ifndef STAFF_H_
#define STAFF_H_
#include <ctime>
#include <cstdlib>

class Staff {
protected:
	int min_service_time = 1;
	int max_service_time = 243;
	int serviceTime;
	int total_wait;
	HospitalQ* hospital_queue;
	LowPrioQ* lowPrioQ;
	HighPrioQ* highPrioQ;
	std::queue<Patients*> the_queue;
public:
	Staff () {}
	void set_serviceTime() {
		srand(time(NULL));
		serviceTime = rand() % this->max_service_time + this->min_service_time;
	}

	virtual void update(int clock) {}

	friend class DoctorQ;
	friend class NurseQ;
};

class DoctorQ : public Staff {
private:
	int min_service_time = 1;
	int max_service_time = 20;
	int serviceTime;
	std::queue<Patients*> the_queue;
public:
	DoctorQ() {}
	void set_serviceTime() {
		srand(time(NULL));
		serviceTime = rand() % this->max_service_time + this->min_service_time;
	}
	void update(int clock) {
		if (!the_queue.empty()) {
			Patients* p = the_queue.front();
			std::map<std::string, Patients>::iterator it = patient_Map.find(p->get_name());
			//patient has been fully treated
			if ((clock - it->second.get_treatmentStart()) == this->serviceTime) {
				the_queue.pop();
				it->second.set_dichargeTime(clock);
				it->second.set_wait_time();
				delete p;
			}
		}
	}

	friend class HighPrioQ;
	friend class LowPrioQ;
};

class NurseQ : public Staff {
private:
	int min_service_time = 1;
	int max_service_time = 10;
	int serviceTime;
	std::queue<Patients*> the_queue;
public:
	NurseQ() {}
	void set_serviceTime() {
		srand(time(NULL));
		serviceTime = rand() % this->max_service_time + this->min_service_time;
	}
	void update(int clock) {
		if (!the_queue.empty()) {
			Patients* p = the_queue.front();
			std::map<std::string, Patients>::iterator it = patient_Map.find(p->get_name());
			//patient has been fully treated
			if ((clock - p->get_treatmentStart()) == this->serviceTime) {
				the_queue.pop();
				it->second.set_dichargeTime(clock);
				it->second.set_wait_time();
				delete p;
			}
		}
	}

	friend class LowPrioQ;
};

#endif
