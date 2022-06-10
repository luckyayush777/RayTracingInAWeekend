#pragma once
#include"RTWeekend.h"

class Camera {
private:
	Point3 origin;
	Point3 lowerLeftCorner;
	Vec3 horizontal;
	Vec3 vertical;
public:
	Camera()
	{
		double verticalFOV;
		auto aspectRatio = 16.0 / 9.0;
		auto viewPortHeight = 2.0;
		auto viewPortWidth = aspectRatio * viewPortHeight;
		auto focalLength = 1.0;


		origin = Point3(0, 0, 0);
		horizontal = Vec3(viewPortWidth, 0.0, 0.0);
		vertical = Vec3(0, viewPortHeight, 0);
		lowerLeftCorner = origin - horizontal / 2 - vertical / 2 - Vec3(0, 0, focalLength);
	}

	Ray GetRay(double u, double v) const {
		return Ray(origin, lowerLeftCorner + u * horizontal + v * vertical - origin);
	}
};