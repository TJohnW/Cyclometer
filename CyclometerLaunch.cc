#include <iostream>
#include <pthread.h>

#include <sys/neutrino.h>

#include "Application.h"
#include "SafeOutput.h"
#include "IOPort.h"
#include "Cyclometer.h"

using namespace std;


void *startGarage(void* cyclometer) {
    ((Cyclometer*) cyclometer)->run();
}

void *startInputController(void* inputController) {
    ((InputController*) inputController)->run();
}

void *startMotor(void* motor) {
    ((Motor*) motor)->run();
}


void verifyThreadAccess() {
	if ( ThreadCtl(_NTO_TCTL_IO, NULL) == -1)
	{
		perror("Failed to get I/O access permission");
		exit(1);
	}
}


int main(int argc, char *argv[]) {

	verifyThreadAccess();

	IOPort ioPort = IOPort();
	return -1;

	SafeOutput out;
	SafeOutput::init();

	Application cyclometerController(true);
	//pthread_t inputThread;
	pthread_t cyclometerThread;
	pthread_t motorThread;
	//pthread_create(&inputThread, NULL, startInputController, (void *) cyclometerController.inputController);
	pthread_create(&cyclometerThread, NULL, startGarage, (void*) cyclometerController.cyclometer);
	pthread_create(&motorThread, NULL, startMotor, (void*) cyclometerController.cyclometer->getMotor());

	cyclometerController.inputController->run();

	return EXIT_SUCCESS;
}
