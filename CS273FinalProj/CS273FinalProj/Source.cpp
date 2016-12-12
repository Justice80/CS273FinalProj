#include "HospitalSim.h"

Simulator hospital;

void main() {

	hospital.enter_data();
	hospital.run_sim();
	hospital.stats();

}