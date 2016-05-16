#include <iostream>
//#include <sys/neutrino.h>

#include "ThreadUtils.h"
#include "IOPort.h"
#include "Cyclometer.h"
#include "InputController.h"
#include "OutputController.h"
#include "CyclometerCalculations.h"

using namespace std;


void *startCyclometer(void* cyclometer) {
	((Cyclometer*) cyclometer)->run();
}

void *startInput(void* input) {
	((InputController*) input)->run();
}

void *startOutput(void* output) {
	((OutputController*) output)->run();
}

void *startCalculations(void* calc) {
	((CyclometerCalculations*) calc)->run();
}


/*
void verifyThreadAccess() {
	if ( ThreadCtl(_NTO_TCTL_IO, NULL) == -1)
	{
		perror("Failed to get I/O access permission");
		exit(1);
	}
}
 */



int main(int argc, char *argv[]) {

	/*
	if(false) {
		verifyThreadAccess();
		IOPort ioPort = IOPort();
	}
	 */

	std::cout << "Starting" << std::endl;

	ThreadUtils out;

	Cyclometer* cyclometer = new Cyclometer();
	OutputController* outputController = new OutputController(cyclometer);
	CyclometerCalculations* calculations = new CyclometerCalculations(cyclometer->getCyclometerData());
	InputController* inputController = new InputController(cyclometer, calculations);

	pthread_t cyclometerThread;
	//pthread_t inputThread;
	pthread_t outputThread;
	pthread_t calculationsThread;

	pthread_create(&cyclometerThread, NULL, startCyclometer, (void*) cyclometer);
	//pthread_create(&inputThread, NULL, startInput, (void*) inputController);
	pthread_create(&outputThread, NULL, startOutput, (void*) outputController);
	pthread_create(&calculationsThread, NULL, startCalculations, (void*) calculations);

	inputController->run();

	return EXIT_SUCCESS;
}
