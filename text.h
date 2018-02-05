#ifndef TEXT_H
#define TEXT_H

#include <string.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <ft2build.h>
#include <freetype/freetype.h>
#include "texture.h"

struct text
{
	struct texture **chars;
	int size;
};

struct texture *glyphFromChar(unsigned char, FT_Face*, float, float);

struct text *newText(const char		*source,
					 FT_Face		*face,
					 float			x,
					 float			y)
{
	if(!strlen(source))
	{
		fprintf(stderr, "[newText] Cannot create texture from empty string.\n");
		return NULL;
	}
	struct text *obj = malloc(sizeof(struct text));
	obj->size = strlen(source);
	obj->chars = malloc(sizeof(struct texture*) * obj->size);
	for(int i = 0; i < obj->size; i++)
		obj->chars[i] = glyphFromChar(source[i], face, x+i*32, y);
	return obj;
}

struct texture *glyphFromChar(unsigned char	t,
							   FT_Face			*face,
							   float			x,
							   float			y)
{
	struct texture *obj = malloc(sizeof(struct texture));

	obj->x = x; obj->y = y;

	glGenTextures(1, &obj->_texture);
	glBindTexture(GL_TEXTURE_2D, obj->_texture);

	FT_Load_Glyph(*face, t+1, FT_LOAD_RENDER);

	GLint prevAlignment;

	glGetIntegerv(GL_UNPACK_ALIGNMENT, &prevAlignment);		// get previous pixel packing mode

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	// set pixel packing to 1 byte padding - this line is absolutely needed for FreeType fonts in GL

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED,		// we only read one byte that will be used as alpha in a shader
				 (*face)->glyph->bitmap.width,
				 (*face)->glyph->bitmap.rows,
				 0, GL_RED, GL_UNSIGNED_BYTE, (*face)->glyph->bitmap.buffer);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	// set texture filtering. texture won't render without these parameters

	glPixelStorei(GL_UNPACK_ALIGNMENT, prevAlignment);		// set pixel packing back to normal

	return obj;
}
#endif // TEXT_H
