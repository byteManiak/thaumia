#ifndef CURSOR_H
#define CURSOR_H

#include <GLFW/glfw3.h>
#include "shader.h"
#include "texture.h"
#include "renderer.h"

struct cursor
{
	struct drawable *glyph;
	double x, y;
} mainCursor;

const GLchar *cursorVertexSource[];
GLuint cursorShader;

void initCursor()
{
	mainCursor.glyph = newTexture("cursor.tga", 0, 0, 0, 0);
	cursorShader = getShader(cursorVertexSource, defaultFragmentSource);
}

void updateCursor(GLFWwindow *window)
{
	glfwGetCursorPos(window, &mainCursor.x, &mainCursor.y);
}

void drawCursor(GLint resolution[2])
{
	draw(mainCursor.glyph, cursorShader, resolution);
}

const GLchar *cursorVertexSource[] =
{
	"#version 330 core\n"
	"out vec2 uv;\n"
	"uniform vec2 position;\n"
	"uniform ivec2 resolution;\n"
	"void main() {"
	"   const vec2 uv_verts[4] = vec2[4]( vec2(0, 0),"
	"                                vec2(1, 0),"
	"                                vec2(1, 1),"
	"                                vec2(0, 1));"
	"   gl_Position = vec4(position - resolution/2, 1, 1);"
	"	 uv = uv_verts[gl_VertexID]; }"
};

#endif // CURSOR_H
