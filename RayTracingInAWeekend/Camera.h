#pragma once
#include"RTWeekend.h"

class Camera {
private:
	Point3 origin;
	Point3 lowerLeftCorner;
	Vec3 horizontal;
	Vec3 vertical;
	Vec3 u, v, w;
	double lensRadius;
public:
	Camera(Point3 lookFrom, Point3 lookAt, Vec3 vUp, double verticalFOV, double aspectRatio, double aperture, double focusDistance)
	{
		auto theta = Personal::DegToRad(verticalFOV);
		auto h = tan(theta / 2);
		auto viewPortHeight = 2.0 * h;
		auto viewPortWidth = aspectRatio * viewPortHeight;

		w = UnitVector(lookFrom - lookAt);
		u = UnitVector(Cross(vUp, w));
		v = Cross(w, u);

		origin = lookFrom;
		horizontal = focusDistance * viewPortWidth * u;
		vertical = focusDistance * viewPortHeight * v;
		lowerLeftCorner = origin - horizontal / 2 - vertical / 2 -  focusDistance * w;
		lensRadius = aperture / 2;
	}

	Ray GetRay(double s, double t) const {
		Vec3 rd = lensRadius * RandomInUnitDisk();
		Vec3 offset = u * rd.X() + v * rd.Y();
		
		return Ray(origin + offset, lowerLeftCorner + s * horizontal + t * vertical - origin - offset);
	}
};