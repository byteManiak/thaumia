#ifndef CONTEXT_FUNCTIONS_H
#define CONTEXT_FUNCTIONS_H

#include <GLFW/glfw3.h>

static unsigned char isFullscreen = 0;

void toggleFullscreen(GLFWwindow **window,
					  const GLFWvidmode **vidmodes,
					  int count)
{
	glfwSetWindowMonitor(*window,
						 isFullscreen ? glfwGetPrimaryMonitor() : NULL,
						 0, 0,
						 (*vidmodes)[count-1].width,
						(*vidmodes)[count-1].height,
						(*vidmodes)[count-1].refreshRate);
	isFullscreen = 1 - isFullscreen;
	printf("[toggleFullscreen] Fullscreen resolution is %d x %d.\n",
		   (*vidmodes)[count-1].width, (*vidmodes)[count-1].height);
}

void changeVideoMode(GLFWwindow **window,
					 const GLFWvidmode **vidmodes,
					 int count,
					 int newVidMode,
					 int fullscreen)
{
	if(newVidMode > count || newVidMode < 1)
	{
		fprintf(stderr, "[changeVideoMode] %d is not a valid video mode.\n", newVidMode-1);
		return;
	}
	glfwSetWindowMonitor(*window,
				   fullscreen ? glfwGetPrimaryMonitor() : NULL,
				   0, 0,
				   (*vidmodes)[newVidMode-1].width,
					(*vidmodes)[newVidMode-1].height,
					(*vidmodes)[newVidMode-1].refreshRate);
	printf("[changeVideoMode] Video mode %d applied. Resolution is %d x %d @ %dHz.\n",
		   newVidMode-1, (*vidmodes)[newVidMode-1].width, (*vidmodes)[newVidMode-1].height,
			(*vidmodes)[newVidMode-1].refreshRate);
}

#endif // CONTEXT_FUNCTIONS_H
