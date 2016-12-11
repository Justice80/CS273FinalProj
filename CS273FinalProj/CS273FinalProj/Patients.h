#ifndef PATIENTS_H_
#define	PATIENTS_H_



class Patients
{
private:
	string name;
	int numOfVisits;
	vector<int>SeverityLevel;
public:
	void incrementVisits;
	int waitTime;
	int arrivaTime;
	int discargeTime;
};

#endif
