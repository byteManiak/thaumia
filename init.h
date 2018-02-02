#ifndef INIT_H
#define INIT_H

#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <freetype/freetype.h>
#include "cvar.h"

int init(GLFWwindow **window,
		 const GLFWvidmode **vidmodes, int *count,
		 FT_Library *library,
		 FT_Face *face)
{
	if(!glfwInit()) { fprintf(stderr, "[init] Could not init GLFW.\n"); return 1; }
	*vidmodes = glfwGetVideoModes(glfwGetPrimaryMonitor(), count);

	if(FT_Init_FreeType(library)) { fprintf(stderr, "[init] Could not init FreeType.\n"); return 1;}

	if(FT_New_Face(*library, "VGA.ttf", 0, face)) { fprintf(stderr, "[init] Could not load font.\n"); return 1;}

	FT_Set_Pixel_Sizes(*face, 0, 16);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	*window = glfwCreateWindow(1024, 600,
							   "Thaumia OpenGL test",
							   NULL, NULL);

	glfwMakeContextCurrent(*window);

	glfwSwapInterval(1);

	if(glewInit() != GLEW_OK) { fprintf(stderr, "[init] Could not init GLEW.\n"); return 1; }
	glewExperimental = GL_TRUE;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return 0;
}
#endif // INIT_H
