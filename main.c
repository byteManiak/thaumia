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

#define CHUNKSIZE 256

GLint resolution[2] = {0, 0}, oldResolution[2] = {0, 0};
float offset[2] = {0, 0};

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
		printf("[getVidModes] Mode %d: %d x %d @ %dHz\n", i,
			   vidmodes[i].width,
			   vidmodes[i].height,
			   vidmodes[i].refreshRate);
	} // to do: implement this function in a different file

	defaultShader = getShader(defaultVertexSource, defaultFragmentSource);
	// initialise shaders. to do: initialise shaders somewhere else and only if needed

	struct rectangle *tex = malloc(sizeof(struct rectangle) * 65536);
	struct GLbatch **batches = malloc(sizeof(struct GLbatch*) * 65536/CHUNKSIZE);

	for(int i = 0; i < 65536/CHUNKSIZE; i++)
		batches[i] = newBatch(defaultShader);

	for(int i = 0; i < 256; i++)
		for(int j = 0; j < 256; j++)
		{
			tex[i*256+j] = newRectangle(j*32, i*32, 32, 32);
			addToBatch(batches[i], tex[i*256+j], 4);
		}

	for(int i = 0; i < 65536/CHUNKSIZE; i++)
		finaliseBatch(batches[i]);

	GLuint texture = newTexture("tileTest.tga");

	do
	{
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
		glUniform1f(glGetUniformLocation(defaultShader, "time"), glfwGetTime());
		glUniform2fv(glGetUniformLocation(defaultShader, "offset"), 1, offset);

		for(int i = 0; i < 65536/CHUNKSIZE; i++)
			drawBatch(batches[i]);

		glfwSwapBuffers(window);
		glfwPollEvents();

		if(isHeld(&window, GLFW_KEY_RIGHT))
			offset[0] -= 250.0f * deltaTime;

		if(isHeld(&window, GLFW_KEY_LEFT))
			offset[0] += 250.0f * deltaTime;

		if(isHeld(&window, GLFW_KEY_UP))
			offset[1] += 250.0f * deltaTime;

		if(isHeld(&window, GLFW_KEY_DOWN))
			offset[1] -= 250.0f * deltaTime;

		if(isPressed(&window, GLFW_KEY_F11))
			toggleFullscreen(&window, &vidmodes, count);

		if(isPressed(&window, GLFW_KEY_Q))
		{
			currentVidMode = (currentVidMode-1) % (count+1);
			changeVideoMode(&window, &vidmodes, count, currentVidMode-1, 1);
		}

		if(isPressed(&window, GLFW_KEY_W))
		{
			currentVidMode = (currentVidMode+1) % (count+1);
			changeVideoMode(&window, &vidmodes, count, currentVidMode+1, 1);
		}

		if(isPressed(&window, GLFW_KEY_ESCAPE)) glfwSetWindowShouldClose(window, 1);

		updateDeltaTime();

	} while(!glfwWindowShouldClose(window));

	for(int i = 0; i < CHUNKSIZE; i++)
		deleteBatch(batches[i]);

	free(batches);
	free((GLFWvidmode*)vidmodes);

	glfwDestroyWindow(window);

    return 0;
}
