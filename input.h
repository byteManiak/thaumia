#ifndef INPUT_H
#define INPUT_H

#include <GLFW/glfw3.h>

static int keys[400];

int isHeld(GLFWwindow **window, int code)
{
	if(code == GLFW_KEY_UNKNOWN) return 0;
	return glfwGetKey(*window, code);
}

int isPressed(GLFWwindow **window, int code)
{
	if(code == GLFW_KEY_UNKNOWN) return 0;
	if(glfwGetKey(*window, code) && keys[code] == 0) { keys[code] = 1; return 1; }
	else if(!glfwGetKey(*window, code)) { keys[code] = 0; return 0; }
	return 0;
}

int isReleased(GLFWwindow **window, int code)
{
	if(code == GLFW_KEY_UNKNOWN) return 0;
	if(!glfwGetKey(*window, code) && keys[code] == 1) { keys[code] = 0; return 1; }
	else if(glfwGetKey(*window, code)) { keys[code] = 1; return 0; }
	return 0;
}
#endif // INPUT_H
