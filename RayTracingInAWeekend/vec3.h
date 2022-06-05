#pragma once
#include<cmath>
#include<iostream>
#include"RTWeekend.h"
using std::sqrt;

class Vec3 {
public :
	double vector[3];
	Vec3() : vector{0, 0, 0}{}
	Vec3(double x, double y, double z) : vector{ x, y, z } {}

	double X() const
	{
		return vector[0];
	}
	double Y() const { return vector[1]; }
	double Z() const { return vector[2]; }

	Vec3 operator-() const { return Vec3(-vector[0], -vector[1], -vector[2]); }
	double operator[](int i) const { return vector[i]; }
	double& operator[](int i) { return vector[i]; }

	Vec3& operator +=(const Vec3& v)
	{
		vector[0] += v[0];
		vector[1] += v[1];
		vector[2] += v[2];
		return *this;
	}

	Vec3& operator *=(const double t)
	{
		vector[0] *= t;
		vector[1] *= t;
		vector[2] *= t;
		return *this;
	}

	Vec3& operator /=(const double t)
	{
		return *this *= 1 / t;
	}

	double Length() const {
		return sqrt(LengthSquared());	
	}

	double LengthSquared() const {
		return vector[0] * vector[0] + vector[1] * vector[1] + vector[2] * vector[2];
	}
	friend std::ostream& operator<<(std::ostream& out, const Vec3& v)
	{
		out<< v.vector[0] << ' ' << v.vector[1] << ' ' << v.vector[2];
		return out;
	}

	

	

	friend Vec3 operator*(const Vec3& u, const Vec3& v)
	{
		return Vec3(u.vector[0] * v.vector[0], u.vector[1] * v.vector[1], u.vector[2] * v.vector[2]);
	}


};
using Point3 = Vec3;
using Color = Vec3;
inline Vec3 operator+(const Vec3& u,const Vec3& v)
{
	return Vec3(u.vector[0] + v.vector[0], u.vector[1] + v.vector[1], u.vector[2] + v.vector[2]);
}

inline Vec3 operator-(const Vec3& u, const Vec3& v)
{
	return Vec3(u.vector[0] - v.vector[0], u.vector[1] - v.vector[1], u.vector[2] - v.vector[2]);
}

inline Vec3 operator*(double t, const Vec3& u)
{
	return Vec3(u[0] * t, u[1] * t, u[2] * t);
}

inline Vec3 operator*( const Vec3& u, double t )
{
	return Vec3(u[0] * t, u[1] * t, u[2] * t);
}

inline Vec3 operator/(Vec3 v, double t)
{
	return (1 / t) * v;
}

inline Vec3 UnitVector(Vec3 v)
{
	return v / v.Length();
}

inline double Dot(const Vec3& u, const Vec3& v) {
	return u.vector[0] * v.vector[0]
		+ u.vector[1] * v.vector[1]
		+ u.vector[2] * v.vector[2];
}

inline Vec3 Cross(const Vec3& u, const Vec3& v) {
	return Vec3(u.vector[1] * v.vector[2] - u.vector[2] * v.vector[1],
		u.vector[2] * v.vector[0] - u.vector[0] * v.vector[2],
		u.vector[0] * v.vector[1] - u.vector[1] * v.vector[0]);
}

inline static Vec3 Random()
{
	return Vec3(Personal::RandomDouble(), Personal::RandomDouble(), Personal::RandomDouble());
}

inline static Vec3 Random(double min, double max)
{
	return Vec3(Personal::RandomDouble(min, max), Personal::RandomDouble(min, max), Personal::RandomDouble(min, max));
}

static Vec3 RandomInUnitSphere()
{
	while (true)
	{
		auto p = Random(-1, 1);
		if (p.LengthSquared() >= 1) continue;
		return p;
	}
}

static Vec3 RandomUnitVector()
{
	return UnitVector(RandomInUnitSphere());
}


