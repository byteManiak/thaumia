#ifndef BATCH_H
#define BATCH_H

#include <stdlib.h>
#include <GL/glew.h>
#include "texture.h"

// this file contains the OpenGL batch, which stores
// multiple objects of the same type and draws them in one call

struct GLbatch
{
	GLfloat			*data;
	unsigned int	size;
	GLuint			_vao;
	GLuint			_vbo;
	GLuint			_shader;
};

struct GLbatch *newBatch(GLuint shader)
{
	struct GLbatch *object = malloc(sizeof(struct GLbatch));
	object->data = calloc(0, sizeof(GLfloat));
	object->size = 0;
	object->_shader = shader;
	glGenVertexArrays(1, &object->_vao);
	glGenBuffers(1, &object->_vbo);
	return object;
}

void addToBatch(struct GLbatch *batch, struct texture *tex)
{
	if(!batch->size)
	{
		batch->data = realloc(batch->data, sizeof(GLfloat) * 12);

		batch->data[0] = tex->x;
		batch->data[1] = tex->y;

		batch->data[2] = tex->x;
		batch->data[3] = tex->y + tex->h;

		batch->data[4] = tex->x + tex->w;
		batch->data[5] = tex->y + tex->h;

		batch->data[6] = tex->x;
		batch->data[7] = tex->y;

		batch->data[8] = tex->x + tex->w;
		batch->data[9] = tex->y;

		batch->data[10] = tex->x + tex->w;
		batch->data[11] = tex->y + tex->h;

		// every batch object is drawn in this order:
		// top-left, bottom-left, bottom-right, top-left, top-right, bottom-right

		batch->size = 12;
	}
	else
	{
		batch->data = realloc(batch->data, (batch->size + 12) * sizeof(GLfloat));

		batch->data[batch->size] = tex->x;
		batch->data[batch->size+1] = tex->y;

		batch->data[batch->size+2] = tex->x;
		batch->data[batch->size+3] = tex->y + tex->h;

		batch->data[batch->size+4] = tex->x + tex->w;
		batch->data[batch->size+5] = tex->y + tex->h;

		batch->data[batch->size+6] = tex->x;
		batch->data[batch->size+7] = tex->y;

		batch->data[batch->size+8] = tex->x + tex->w;
		batch->data[batch->size+9] = tex->y;

		batch->data[batch->size+10] = tex->x + tex->w;
		batch->data[batch->size+11] = tex->y + tex->h;

		batch->size += 12;
	}

	glBindVertexArray(batch->_vao);

	glBindBuffer(GL_ARRAY_BUFFER,
				 batch->_vbo);

	glBufferData(GL_ARRAY_BUFFER,
				 batch->size * sizeof(GLfloat),
				 batch->data,
				 GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, 0, 0, 0);
}

void drawBatch(struct GLbatch *batch)
{
	glBindVertexArray(batch->_vao);
	glDrawArrays(GL_TRIANGLES, 0, batch->size/2);
}

void deleteBatch(struct GLbatch *batch)
{
	free(batch->data);
	free(batch);
}
#endif // BATCH_H
