#include "Vector.h"

Vector::Vector() {
	x = 0.0f;
	y = 0.0f;
}

Vector::Vector(float x, float y) {
	this->x = x;
	this->y = y;
}

Vector& Vector::Add(const Vector& vec) {
	this->x += vec.x;
	this->y += vec.y;

	return *this;
}

Vector& Vector::Substract(const Vector& vec) {
	this->x -= vec.x;
	this->y -= vec.y;

	return *this;
}

Vector& Vector::Multyply(const Vector& vec) {
	this->x *= vec.x;
	this->y *= vec.y;

	return *this;
}

Vector& Vector::Multyply(double power) {
	this->x *= power;
	this->y *= power;

	return *this;
}

Vector& Vector::Divide(const Vector& vec) {
	this->x /= vec.x;
	this->y /= vec.y;

	return *this;
}

Vector& Vector::Divide(double power) {
	this->x /= power;
	this->y /= power;

	return *this;
}

Vector& operator+(Vector& v1, const Vector& v2) {
	return v1.Add(v2);
}

Vector& operator-(Vector& v1, const Vector& v2) {
	return v1.Substract(v2);
}

Vector& operator*(Vector& v1, const Vector& v2) {
	return v1.Multyply(v2);
}

Vector& operator/(Vector& v1, const Vector& v2) {
	return v1.Divide(v2);
}

Vector& Vector::operator+=(const Vector& vec) {
	return this->Add(vec);
}

Vector& Vector::operator-=(const Vector& vec) {
	return this->Substract(vec);
}

Vector& Vector::operator*=(const Vector& vec) {
	return this->Multyply(vec);
}

Vector& Vector::operator/=(const Vector& vec) {
	return this->Divide(vec);
}