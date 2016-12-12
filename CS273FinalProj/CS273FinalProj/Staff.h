#ifndef STAFF_H_
#define STAFF_H_
#include <ctime>
#include <cstdlib>

class Staff {
protected:
	int min_service_time;
	int max_service_time;
	int serviceTime;
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

	int getServiceTime() { return serviceTime; }
	virtual void update(int clock) {}

	friend class DoctorQ;
	friend class NurseQ;
};

class DoctorQ : public Staff {
private:
	int min_service_time = 1;
	int max_service_time = 20;
	std::queue<Patients*> the_queue;
public:
	DoctorQ() {}
	void update(int clock) {
		if (!the_queue.empty()) {
			Patients* p = the_queue.front();
			//patient has been fully treated
			if ((clock - p->get_treatmentStart()) > this->getServiceTime()) {
				the_queue.pop();
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
	std::queue<Patients*> the_queue;
public:
	NurseQ() {}
	void update(int clock) {
		if (!the_queue.empty()) {
			Patients* p = the_queue.front();
			//patient has been fully treated
			if ((clock - p->get_treatmentStart()) > this->getServiceTime()) {
				the_queue.pop();
				delete p;
			}
		}
	}

	friend class LowPrioQ;
};

#endif
