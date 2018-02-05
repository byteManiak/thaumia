#ifndef RENDERER_H
#define RENDERER_H

#include <GL/glew.h>
#include <GL/gl.h>
#include "texture.h"

// this file implements the drawcall functions
// needs heavy WIP

void draw(struct drawable *object, GLuint shader)
{
	glBindVertexArray(object->_vao);

	glBindTexture(GL_TEXTURE_2D, object->_texture);
	glUniform1i(glGetUniformLocation(shader, "tex"), 0);

	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

#endif // RENDERER_H
