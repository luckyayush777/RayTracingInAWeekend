#pragma once
#include"Hittable.h"
#include"vec3.h"

class Sphere : public Hittable {
public : 
	Sphere() {}
	Sphere(Point3 cen, double r, std::shared_ptr<Material> m) : center(cen), radius(r), matPtr(m) {};
	virtual bool Hit(const Ray& ray, double tMin, double tMax, HitRecord& record) const override;
public:
	Point3 center;
	double radius;
	std::shared_ptr<Material> matPtr;
};

bool Sphere::Hit(const Ray& ray, double tMin, double tMax, HitRecord& record) const{
	Vec3 oc = ray.Origin() - center;
	auto a = ray.Direction().LengthSquared();
	auto halfB = Dot(oc, ray.Direction());
	auto c = oc.LengthSquared() - radius * radius;

	auto discriminant = halfB * halfB - a * c;
	if (discriminant < 0) return false;
	auto sqrtd = sqrt(discriminant);
	auto root = (-halfB - sqrtd) / a;
	if (root < tMin || tMax < root)
	{
		root = (-halfB + sqrtd) / a;
		if (root < tMin || tMax < root)
			return false;
	}
	record.t = root;
	record.point = ray.PointAt(record.t);
	Vec3 outwardNormal = (record.point - center) / radius;
	record.SetFaceNormal(ray, outwardNormal);
	record.matPtr = matPtr;
	return true;
}