#ifndef STAFF_H_
#define STAFF_H_

class Staff {
private:
	int min_service_time;
	int max_service_time;
	HospitalQ* hospital_queue;
	LowPrioQ* lowPrioQ;
	HighPrioQ* highPrioQ;
	std::queue<Patients*> the_queue;
public:
	virtual void set_serviceTime(int min_service_time, int max_service_time) {}
	virtual void treatPatient() {} 
	void discharge() {}

};

class DoctorQ : public Staff {

	friend class HighPrioQ;
	friend class LowPrioQ;
};

class NurseQ : public Staff {

	friend class LowPrioQ;
};

#endif
