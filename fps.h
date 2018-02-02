#ifndef FPS_H
#define FPS_H

#include <GLFW/glfw3.h>

static int fps = 0;
static double currentTime = 1;

void getFrameTime()
{
	fps++;
	if(glfwGetTime() - currentTime >= 1)
	{
		printf("[getFrameTime] Frame time: %.2fms\n", 1000.0f/fps);
		fps = 0;
		currentTime = glfwGetTime();
	}
}

#endif // FPS_H
