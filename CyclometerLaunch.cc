#include <iostream>
//#include <sys/neutrino.h>

#include "ThreadUtils.h"
#include "IOPort.h"
#include "Cyclometer.h"
#include "InputController.h"
#include "OutputController.h"
#include "Calculations.h"
#include <GLFW/glfw3.h>

using namespace std;

static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
}

//Button 0 - Set, Button 1 - Start/stop, Button 2 - Mode.
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);



	if(key == GLFW_KEY_1 && action == GLFW_PRESS) {
		InputController::buttons[SET_BUTTON_IN] = true;
	}

	if (key == GLFW_KEY_1 && action == GLFW_RELEASE) {
		InputController::buttons[SET_BUTTON_IN] = false;
		//forwardEvent(SET_BUTTON);
	}

	if(key == GLFW_KEY_2 && action == GLFW_PRESS) {
		InputController::buttons[START_STOP_BUTTON_IN] = true;
	}

	if (key == GLFW_KEY_2 && action == GLFW_RELEASE) {
		InputController::buttons[START_STOP_BUTTON_IN] = false;
		//forwardEvent(START/STOP);
	}

	if(key == GLFW_KEY_3 && action == GLFW_PRESS) {
		InputController::buttons[MODE_BUTTON_IN] = true;
	}

	if (key == GLFW_KEY_3 && action == GLFW_RELEASE) {
		InputController::buttons[MODE_BUTTON_IN] = false;
		//forwardEvent(START/STOP);
	}



	if (key == GLFW_KEY_0 && action == GLFW_RELEASE)
		InputController::forwardEvent(PULSE);
}



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
	((Calculations*) calc)->run();
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
	Calculations* calculations = cyclometer->getCalculations();
	InputController* inputController = new InputController(cyclometer, calculations);

	pthread_t cyclometerThread;
	pthread_t inputThread;
	pthread_t outputThread;
	pthread_t calculationsThread;

	pthread_create(&cyclometerThread, NULL, startCyclometer, (void*) cyclometer);
	pthread_create(&inputThread, NULL, startInput, (void*) inputController);
	pthread_create(&outputThread, NULL, startOutput, (void*) outputController);
	pthread_create(&calculationsThread, NULL, startCalculations, (void*) calculations);

	GLFWwindow *window;
	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
		exit(EXIT_FAILURE);
	window = glfwCreateWindow(10, 10, "Simple example", NULL, NULL);
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	glfwSetKeyCallback(window, key_callback);

	while (!glfwWindowShouldClose(window)) {

		int width, height;

		glfwGetFramebufferSize(window, &width, &height);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	exit(EXIT_SUCCESS);

	return EXIT_SUCCESS;
}
