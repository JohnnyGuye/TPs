/*************************************************************************
                           Vector2D  -  description
                             -------------------
    début                : 13 Janvier 2016
    copyright            : (C) 2015 par Quentin "Johnny" Guye et Lucas Ono
*************************************************************************/

using namespace std;

#include "Vector2D.h"

double Vector2D::GetX() const {	return x;	}
double Vector2D::GetY() const {	return y;	}

Vector2D::Vector2D (const double x, const double y)
{
	this->x = x;
	this->y = y;
}

Vector2D::Vector2D (const int x, const int y)
{
	this->x = x;
	this->y = y;
}

Vector2D::Vector2D (Vector2D const &vec2D)
{
	this->x = vec2D.GetX();
	this->y = vec2D.GetY();
}

Vector2D Vector2D::operator+(const Vector2D& other) const
{
    return Vector2D(x + other.x, y + other.y);
}

Vector2D Vector2D::operator-(const Vector2D& other) const
{
    return Vector2D(x - other.x, y - other.y);
}

Vector2D Vector2D::operator-() const
{
    return Vector2D(-x, -y);
}

Vector2D Vector2D::operator*(const double num) const
{
    return Vector2D(x * num, y * num);
}

Vector2D Vector2D::operator/(const double num) const
{
    return Vector2D(x/num, y/num);
}

Vector2D& Vector2D::operator=(const Vector2D& other)
{
    x = other.x;
    y = other.y;
    return *this;
}

Vector2D& Vector2D::operator+=(const Vector2D& other)
{
    x += other.x;
    y += other.y;
    return *this;
}

Vector2D& Vector2D::operator-=(const Vector2D& other)
{
    x -= other.x;
    y -= other.y;
    return *this;
}

Vector2D& Vector2D::operator*=(const double num)
{
    x *= num;
    y *= num;
    return *this;
}

Vector2D& Vector2D::operator/=(const double num)
{
    x /= num;
    y /= num;
    return *this;
}

bool Vector2D::operator==(const Vector2D& other) const
{
        return (other.x == x && other.y == y);
}

bool Vector2D::operator!=(const Vector2D& other) const
{
    return !(*this == other);
}

Vector2D& Vector2D::normalize()
{
    return ((*this)/=length());
}

double Vector2D::length() const
{
    return sqrt(x * x + y * y);
}

double Vector2D::scalarProduct(const Vector2D & other) const
{
    return (other.x * x + other.y * y);
}

Vector2D::~Vector2D(){}
