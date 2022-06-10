#pragma once
#include"RTWeekend.h"

class Camera {
private:
	Point3 origin;
	Point3 lowerLeftCorner;
	Vec3 horizontal;
	Vec3 vertical;
public:
	Camera(Point3 lookFrom, Point3 lookAt, Vec3 vUp, double verticalFOV, double aspectRatio)
	{
		auto theta = Personal::DegToRad(verticalFOV);
		auto h = tan(theta / 2);
		auto viewPortHeight = 2.0 * h;
		auto viewPortWidth = aspectRatio * viewPortHeight;

		auto w = UnitVector(lookFrom - lookAt);
		auto u = UnitVector(Cross(vUp, w));
		auto v = Cross(w, u);

		origin = lookFrom;
		horizontal = viewPortWidth * u;
		vertical = viewPortHeight * v;
		lowerLeftCorner = origin - horizontal / 2 - vertical / 2 - w;
	}

	Ray GetRay(double s, double t) const {
		return Ray(origin, lowerLeftCorner + s * horizontal + t * vertical - origin);
	}
};