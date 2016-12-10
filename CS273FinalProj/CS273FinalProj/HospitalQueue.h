#ifndef HOSPITAL_Q_H_
#define HOSPITAL_Q_H_

class HospitalQ {
private:
	double arrival_rate;
	int num_served;
	std::queue<Patients*> the_queue;
public:
	void set_arrival_rate(double arrival_rate) {
		this->arrival_rate = arrival_rate;
	}
	void increment_num_served() {
		this->num_served += 1;
	}
	int get_num_served() { return num_served; }

	friend class HighPrioQ;
	friend class LowPrioQ;
};

#endif
