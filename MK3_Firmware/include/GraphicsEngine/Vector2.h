#ifndef VECTORS_H
#define VECTORS_H

struct Vector2
{
	float X;
	float Y;

	Vector2(float x = 0, float y = 0);
	void Normalize();
};

#endif