#ifndef BATCH_H
#define BATCH_H

#include <stdlib.h>
#include <GL/glew.h>
#include "rectangle.h"

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

void addToBatch(struct GLbatch *batch, struct rectangle rec)
{
	if(!batch->size)
	{
		batch->data = realloc(batch->data, sizeof(GLfloat) * 12);

		batch->data[0] = rec.x;
		batch->data[1] = rec.y;

		batch->data[2] = rec.x;
		batch->data[3] = rec.y + rec.h;

		batch->data[4] = rec.x + rec.w;
		batch->data[5] = rec.y + rec.h;

		batch->data[6] = rec.x;
		batch->data[7] = rec.y;

		batch->data[8] = rec.x + rec.w;
		batch->data[9] = rec.y;

		batch->data[10] = rec.x + rec.w;
		batch->data[11] = rec.y + rec.h;

		// every batch object is drawn in this order:
		// top-left, bottom-left, bottom-right, top-left, top-right, bottom-right

		batch->size = 12;
	}
	else
	{
		batch->data = realloc(batch->data, (batch->size + 12) * sizeof(GLfloat));

		batch->data[batch->size] = rec.x;
		batch->data[batch->size+1] = rec.y;

		batch->data[batch->size+2] = rec.x;
		batch->data[batch->size+3] = rec.y + rec.h;

		batch->data[batch->size+4] = rec.x + rec.w;
		batch->data[batch->size+5] = rec.y + rec.h;

		batch->data[batch->size+6] = rec.x;
		batch->data[batch->size+7] = rec.y;

		batch->data[batch->size+8] = rec.x + rec.w;
		batch->data[batch->size+9] = rec.y;

		batch->data[batch->size+10] = rec.x + rec.w;
		batch->data[batch->size+11] = rec.y + rec.h;

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
