#include "Vector2.h"

Vector2::Vector2()
{
    x = 0;
    y = 0;
}

Vector2::Vector2(double x, double y)
{
    this->x = x;
    this->y = y;
}

Vector2::~Vector2()
{
    x = 0;
    y = 0;
}

bool Vector2::operator==(const Vector2& vec)
{
    if (x == vec.x && y == vec.y) return true;
    else return false;
}

bool Vector2::operator!=(Vector2& vec)
{
    if (!(x == vec.x && y == vec.y)) return true;
    else return false;
}

Vector2 Vector2::operator+(Vector2& vec)
{
    Vector2 v1;
    v1.x = x + vec.x;
    v1.y = y + vec.y;
    return v1;
}

Vector2 Vector2::operator-(Vector2& vec)
{
    Vector2 v1;
    v1.x = x - vec.x;
    v1.y = y - vec.y;
    return v1;
}

Vector2 Vector2::operator*(double d)
{
    Vector2 v1;
    v1.x = x * d;
    v1.y = y * d;
    return v1;
}

Vector2 Vector2::operator/(double d)
{
    Vector2 v1;
    v1.x = x / d;
    v1.y = y / d;
    return v1;
}

double Vector2::Length()
{
    double v2;
    v2 = sqrt(pow(x, 2) + pow(y, 2));
    return v2;
}

Vector2 Vector2::Normalize()
{
    Vector2 v2;
    double length = sqrt(pow(x, 2) + pow(y, 2));
    v2.x = x / length;
    v2.y = y / length;
    return v2;
}

double Vector2::Dot(Vector2& v1)
{
    double v2;
    v2 = (x * v1.x) + (y * v1.y);

    return v2;
}

Vector2 Vector2::Cross(Vector2& v1)
{
    return Vector2();
}

double Vector2::Angle(Vector2& v1)
{
    double v2, v3;
    v2 = sqrt(pow(x, 2) + pow(y, 2));
    v3 = sqrt(pow(v1.x, 2) + pow(v1.y, 2));
    return acos(Dot(v1)/(v2*v3))*(180/3.14);
}



Vector2 operator*(double n, const Vector2& vec)
{
    Vector2 v1;
    v1.x = n * vec.x;
    v1.y = n * vec.y;
    return v1;
}

std::ostream& operator<<(std::ostream& os, const Vector2& v)
{
    os << " " << v.x << " " << v.y;
    return os;
    // TODO: 여기에 return 문을 삽입합니다.
}
