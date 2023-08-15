#pragma once
#include <iostream>

class Vector2
{
public:
	double x, y;
public:
	Vector2();
	Vector2(double x,double y);
	~Vector2();

	bool operator == (const Vector2& vec);
	bool operator != (Vector2& vec);
	Vector2 operator+(Vector2& vec);
	Vector2 operator-(Vector2& vec);
	Vector2 operator*(double d);
	Vector2 operator/(double d);

	double Length();
	Vector2 Normalize();
	
	double Dot(Vector2& v1);
	Vector2 Cross(Vector2& v1);
	double Angle(Vector2& v1);

	friend Vector2 operator* (double n, const Vector2& vec);
	friend std::ostream& operator<<(std::ostream& os, const Vector2& v);

};

