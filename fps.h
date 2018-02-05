#ifndef FPS_H
#define FPS_H

#include <GLFW/glfw3.h>

// this file implements a frametime indicator
// to do: implement a keybind for frametime to appear inside the renderer

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

	// the function averages frametime by looking at the number of fps
	// [optional] to do: don't average, just show raw frametimes
}

#endif // FPS_H
