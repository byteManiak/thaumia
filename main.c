#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include "init.h"
#include "shader.h"
#include "renderer.h"
#include "input.h"
#include "cvar.h"
#include "fps.h"
#include "text.h"
#include "context_functions.h"

static unsigned int currentVidMode = 0;
int main()
{
	GLFWwindow *window;
	const GLFWvidmode *vidmodes; int count;
	FT_Library fontLibrary; FT_Face fontFace;
	if(init(&window, &vidmodes, &count, &fontLibrary, &fontFace)) return 1;	// init returns 0 on success

	printf("[getVidModes] Available modes: %d\n", count);
	for(int i = 0; i < count; i++)
	{
		printf("[getVidModes] Mode %d: %d x %d @ %dHz\n", i, vidmodes[i].width, vidmodes[i].height,
			   vidmodes[i].refreshRate);
	}

	glClearColor(0.1, 0, 0.2, 1);

	defaultShader = getShader(defaultVertexSource, defaultFragmentSource);
	watermelonShader = getShader(watermelonVertexSource, defaultFragmentSource);

	//struct drawable *texture = newTexture("logo.tga", -256, -64, 512, 128);
	struct drawable *texture2 = newTexture("potion.tga", -256, -64, 128, 128);

	struct text *t = newText("Malarkey piness!!", &fontFace, -320, 32);

	GLint resolution[2] = {0, 0}, oldResolution[2] = {0, 0};

	double time = 0;

	do
	{
		time = glfwGetTime();
		getFrameTime();

		glfwGetWindowSize(window, &resolution[0], &resolution[1]);

		if(oldResolution[0] != resolution[0] || oldResolution[1] != resolution[1])
		{
			glViewport(0, 0, resolution[0], resolution[1]);
			oldResolution[0] = resolution[0];
			oldResolution[1] = resolution[1];
		}

		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(watermelonShader);
		glActiveTexture(GL_TEXTURE0);
		glUniform2iv(glGetUniformLocation(watermelonShader, "resolution"), 1, resolution);
		glUniform1f(glGetUniformLocation(watermelonShader, "time"), time);
		draw(texture2, watermelonShader);

		glUseProgram(defaultShader);
		glActiveTexture(GL_TEXTURE0);
		glUniform2iv(glGetUniformLocation(defaultShader, "resolution"), 1, resolution);
		glUniform1f(glGetUniformLocation(defaultShader, "time"), time);
		drawText(t, defaultShader);

		glfwSwapBuffers(window);
		glfwPollEvents();

		if(isPressed(&window, GLFW_KEY_F11))
			toggleFullscreen(&window, &vidmodes, count);

		if(isPressed(&window, GLFW_KEY_LEFT))
		{
			currentVidMode = (currentVidMode-1) % (count+1);
			changeVideoMode(&window, &vidmodes, count, currentVidMode-1, 1);
		}

		if(isPressed(&window, GLFW_KEY_RIGHT))
		{
			currentVidMode = (currentVidMode+1) % (count+1);
			changeVideoMode(&window, &vidmodes, count, currentVidMode+1, 1);
		}
		if(isPressed(&window, GLFW_KEY_ESCAPE)) glfwSetWindowShouldClose(window, 1);

	} while(!glfwWindowShouldClose(window));

	glfwDestroyWindow(window);
    return 0;
}
