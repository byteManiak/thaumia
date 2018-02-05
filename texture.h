#ifndef TEXTURE_H
#define TEXTURE_H

#include <stdlib.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <FreeImage.h>

// this file implements texture creation
// needs heavy WIP

char missingTexture[16] = {255, 0, 255,	255,
						   0, 0, 0, 255,
						   0, 0, 0, 255,
						   255, 0, 255, 255};

struct texture
{
	GLfloat x, y, w, h;
	GLuint _texture;
};

struct texture *newTexture(const char	*path,
							float		x,
							float		y,
							float		w,
							float		h)
{
	struct texture *obj = malloc(sizeof(struct texture));

	obj->x = x; obj->y = y; obj->w = w; obj->h = h;

	glGenTextures(1, &obj->_texture);
	glBindTexture(GL_TEXTURE_2D, obj->_texture);

	FREE_IMAGE_FORMAT format = FreeImage_GetFileType(path, 0);
	FIBITMAP *bitmap = FreeImage_Load(format, path, 0);
	if(bitmap)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
					 FreeImage_GetWidth(bitmap),
					 FreeImage_GetHeight(bitmap),
					 0, GL_RGBA, GL_UNSIGNED_BYTE, FreeImage_GetBits(bitmap));
	}
	else
	{
		fprintf(stderr, "[newTexture] File \"%s\" not found. Using built-in \"missingTexture\" instead.\n", path);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 2, 2,
					 0, GL_RGBA, GL_UNSIGNED_BYTE, missingTexture);
	}
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering. texture won't render without these parameters

	FreeImage_Unload(bitmap);

	glBindTexture(GL_TEXTURE_2D, 0);
	return obj;
}

void deleteTexture(struct texture **texture)
{
	glDeleteTextures(1, &(*texture)->_texture);
	free(*texture);
}

#endif // TEXTURE_H
