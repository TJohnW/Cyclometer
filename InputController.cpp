//
// Created by Tristan Whitcher on 3/9/16.
//

#include <iostream>
#include <stdio.h>
#include <termios.h>
#include "InputController.h"

Cyclometer* InputController::cyclometer;
CyclometerCalculations* InputController::calculations;
bool InputController::enabled;


static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}


InputController::InputController(Cyclometer* cyclometer, CyclometerCalculations *pCalculations) {
    InputController::cyclometer = cyclometer;
    InputController::calculations = pCalculations;
    enabled = true;
}


void InputController::forwardEvent(Event event) {
    if(event == PULSE) {
        // pulse event handled by cyclometer calculator
        time_t now;
        time(&now);
        calculations->queuePulse(now);
    } else {
        cyclometer->queueEvent(event);
    }
}

void InputController::run() {
    GLFWwindow *window;
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        exit(EXIT_FAILURE);
    window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glfwSetKeyCallback(window, key_callback);

    while (!glfwWindowShouldClose(window)) {

        float ratio;

        int width, height;

        glfwGetFramebufferSize(window, &width, &height);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    exit(EXIT_SUCCESS);
}

void InputController::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);


    if (key == GLFW_KEY_1 && action == GLFW_RELEASE)
        forwardEvent(MODE_BUTTON);

    if (key == GLFW_KEY_2 && action == GLFW_RELEASE)
        forwardEvent(SET_BUTTON);

    if (key == GLFW_KEY_0 && action == GLFW_RELEASE)
        forwardEvent(PULSE);
}


