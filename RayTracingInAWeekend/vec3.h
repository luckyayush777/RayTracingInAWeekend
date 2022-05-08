#pragma once
#include<cmath>
#include<iostream>

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

	double length() const {
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

	friend Vec3 operator+(const Vec3& u, const Vec3& v)
	{
		return Vec3(u.vector[0] + v.vector[0], u.vector[1] + v.vector[1], u.vector[2] + v.vector[2]);
	}

	friend Vec3 operator+(const Vec3& u, const Vec3& v)
	{
		return Vec3(u.vector[0] - v.vector[0], u.vector[1] - v.vector[1], u.vector[2] - v.vector[2]);
	}

	friend Vec3 operator*(const Vec3& u, const Vec3& v)
	{
		return Vec3(u.vector[0] * v.vector[0], u.vector[1] * v.vector[1], u.vector[2] * v.vector[2]);
	}
};

using Point3 = Vec3;
using Color = Vec3;	