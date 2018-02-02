#ifndef TEXTURE_H
#define TEXTURE_H

#include <stdlib.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <FreeImage.h>

char missingTexture[16] = {255, 0, 255,	255,
						   0, 0, 0, 255,
						   0, 0, 0, 255,
						   255, 0, 255, 255};

struct drawable
{
	GLuint _vao;
	GLuint _vbo;
	GLuint _texture;

};

struct drawable *newTexture(const char *path, float x, float y, float w, float h)
{
	struct drawable *obj = malloc(sizeof(struct drawable));
	glGenTextures(1, &obj->_texture);
	glBindTexture(GL_TEXTURE_2D, obj->_texture);

	FREE_IMAGE_FORMAT format = FreeImage_GetFileType(path, 0);
	FIBITMAP *bitmap = FreeImage_Load(format, path, 0);
	if(bitmap)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
					 FreeImage_GetWidth(bitmap),
					 FreeImage_GetHeight(bitmap),
					 0, GL_BGRA, GL_UNSIGNED_BYTE, FreeImage_GetBits(bitmap));
	}
	else
	{
		fprintf(stderr, "[newTexture] File \"%s\" not found. Using built-in \"missingTexture\" instead.\n", path);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 2, 2,
					 0, GL_RGBA, GL_UNSIGNED_BYTE, missingTexture);
	}
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // GL_NEAREST is pixel-perfect, GL_LINEAR isn't
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, 0);

	FreeImage_Unload(bitmap);

	glGenVertexArrays(1, &obj->_vao);
	glBindVertexArray(obj->_vao);

	float pos[8] = {x, y, x+w, y, x+w, y+h, x, y+h};

	glGenBuffers(1, &obj->_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, obj->_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(pos), pos, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, 0, 0, 0);

	return obj;
}
#endif // TEXTURE_H
