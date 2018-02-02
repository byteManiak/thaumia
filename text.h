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
	struct drawable **chars;
	int size;
};

struct drawable *glyphFromChar(unsigned char, FT_Face*, float, float);

struct text *newText(const char *source, FT_Face *face, float x, float y)
{
	if(!strlen(source))
	{
		fprintf(stderr, "[newText] Cannot create texture from empty string.\n");
		return NULL;
	}
	struct text *obj = malloc(sizeof(struct text));
	obj->size = strlen(source);
	obj->chars = malloc(sizeof(struct drawable*) * obj->size);
	for(int i = 0; i < obj->size; i++)
		obj->chars[i] = glyphFromChar(source[i], face, x+i*32, y);
	return obj;
}

void drawText(struct text *textToDraw, GLuint shader)
{
	for(int i = 0; i < textToDraw->size; i++)
		draw(textToDraw->chars[i], shader);
}

struct drawable *glyphFromChar(unsigned char t, FT_Face *face, float x, float y)
{
	struct drawable *obj = malloc(sizeof(struct drawable));
	glGenTextures(1, &obj->_texture);
	glBindTexture(GL_TEXTURE_2D, obj->_texture);

	FT_Load_Glyph(*face, t+1, FT_LOAD_RENDER);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED,
				 (*face)->glyph->bitmap.width,
				 (*face)->glyph->bitmap.rows,
				 0, GL_RED, GL_UNSIGNED_BYTE, (*face)->glyph->bitmap.buffer);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glGenVertexArrays(1, &obj->_vao);
	glBindVertexArray(obj->_vao);

	float pos[8] = {x, y,
					x+(*face)->glyph->bitmap.width * 4, y,
					x+(*face)->glyph->bitmap.width * 4, y-(*face)->glyph->bitmap.rows * 4,
					x, y-(*face)->glyph->bitmap.rows * 4};

	glGenBuffers(1, &obj->_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, obj->_vao);
	glBufferData(GL_ARRAY_BUFFER, sizeof(pos), pos, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, 0, 0, 0);

	return obj;
}
#endif // TEXT_H
