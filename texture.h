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

GLuint newTexture(const char *path)
{
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

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
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering. texture won't render without these parameters

	FreeImage_Unload(bitmap);

	return texture;
}

#endif // TEXTURE_H
