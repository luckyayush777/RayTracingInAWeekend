#pragma once
#include"Ray.h"
#include"RTWeekend.h"
class Material;
struct HitRecord {
	Point3 point;
	Vec3 normal;
	std::shared_ptr<Material> matPtr;
	double t;
	bool frontFace;

	inline void SetFaceNormal(const Ray& ray, const Vec3& outwardNormal)
	{
		frontFace = Dot(ray.Direction(), outwardNormal) < 0;
		normal = frontFace ? outwardNormal : -outwardNormal;
	}
};

class Hittable {
public :
	virtual bool Hit(const Ray& ray, double tMin, double tMax, HitRecord& record) const = 0;	
};