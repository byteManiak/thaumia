#ifndef RECTANGLE_H
#define RECTANGLE_H

struct rectangle { float x, y, w, h; };

struct rectangle newRectangle(float x, float y, float w, float h)
{
	struct rectangle rec;
	rec.x = x; rec.y = y; rec.w = w; rec.h = h;
	return rec;
}

#endif // RECTANGLE_H
