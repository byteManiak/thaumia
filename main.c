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
#include "fps.h"
#include "context_functions.h"
#include "batch.h"
#include "texture.h"

static unsigned int currentVidMode = 0;

int main()
{
	srand(time(NULL));
	GLFWwindow *window;
	const GLFWvidmode *vidmodes; int count;
	FT_Library fontLibrary; FT_Face fontFace;
	if(init(&window, &vidmodes, &count, &fontLibrary, &fontFace)) return 1;	// init returns 0 on success
	// potential to do: pack all these data types in a struct and abstract them

	printf("[getVidModes] Available modes: %d\n", count);
	for(int i = 0; i < count; i++)
	{
		printf("[getVidModes] Mode %d: %d x %d @ %dHz\n", i, vidmodes[i].width, vidmodes[i].height,
			   vidmodes[i].refreshRate);
	} // to do: implement this function in a different file

	defaultShader = getShader(defaultVertexSource, defaultFragmentSource);
	// initialise shaders. to do: initialise shaders somewhere else and only if needed

	struct rectangle *tex = malloc(sizeof(struct rectangle) * 16384);
	struct GLbatch *batch = newBatch(defaultShader);

	for(int i = 0; i < 128; i++)
		for(int j = 0; j < 128; j++)
	{
		tex[i*4+j] = newRectangle(i*64-683, j*64-384, 64, 64);
		addToBatch(batch, tex[i*4+j]);
	}

	GLuint texture = newTexture("staff.tga");

	GLint resolution[2] = {0, 0}, oldResolution[2] = {0, 0};

	double time = 0;

	do
	{
		time = glfwGetTime();
		getFrameTime();		// to do: see fps.h

		glfwGetWindowSize(window, &resolution[0], &resolution[1]);

		if(oldResolution[0] != resolution[0] || oldResolution[1] != resolution[1])
		{
			glViewport(0, 0, resolution[0], resolution[1]);
			oldResolution[0] = resolution[0];
			oldResolution[1] = resolution[1];
		}

		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(defaultShader);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glUniform2iv(glGetUniformLocation(defaultShader, "resolution"), 1, resolution);
		glUniform1i(glGetUniformLocation(defaultShader, "tex"), 0);
		glUniform1f(glGetUniformLocation(defaultShader, "time"), time);

		drawBatch(batch);

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

	glDeleteShader(defaultShader);
	glDeleteShader(watermelonShader);
	glDeleteShader(testShader);
	glDeleteShader(fontShader);
	deleteBatch(batch);
	free((GLFWvidmode*)vidmodes);

	glfwDestroyWindow(window);

    return 0;
}
