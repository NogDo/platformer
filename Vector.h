#pragma once
#include "Graphics.h"

class Vector {
public:
	float x;
	float y;

	Vector();
	Vector(float x, float y);

	Vector& Add(const Vector& vec);
	Vector& Substract(const Vector& vec);
	Vector& Multyply(const Vector& vec);
	Vector& Multyply(double power);
	Vector& Divide(const Vector& vec);
	Vector& Divide(double power);

	friend Vector& operator+(Vector& v1, const Vector& v2);
	friend Vector& operator-(Vector& v1, const Vector& v2);
	friend Vector& operator*(Vector& v1, const Vector& v2);
	friend Vector& operator/(Vector& v1, const Vector& v2);

	Vector& operator+=(const Vector& vec);
	Vector& operator-=(const Vector& vec);
	Vector& operator*=(const Vector& vec);
	Vector& operator/=(const Vector& vec);
};