#pragma once
#include"RTWeekend.h"
#include"Hittable.h"

struct HitRecord;
class Material {
public:
	virtual bool Scatter(const Ray& rayIn, const HitRecord& record, Color& attenuation, Ray& scattered)
		const = 0;
};

class Lambertian : public Material {
public :
	Color albedo;
public :
	Lambertian(const Color& a) : albedo(a) {}
	virtual bool Scatter(const Ray& rayIn, const HitRecord& record, Color& attenuation, Ray& scattered) const override {
		auto scatterDirection = record.normal + RandomUnitVector();

		if (scatterDirection.NearZero())
			scatterDirection = record.normal;
		scattered = Ray(record.point, scatterDirection);
		attenuation = albedo;
		return true;
	}
};

class Metal : public Material {
public:
	Metal(const Color& a) : albedo(a) {};
	virtual bool Scatter(const Ray& rayIn, const HitRecord& record, Color& attenuation, Ray& scattered) const override {
		Vec3 reflected = Reflect(UnitVector(rayIn.Direction()), record.normal);
		scattered = Ray(record.point, reflected);
		attenuation = albedo;
		return (Dot(scattered.Direction(), record.normal) > 0);
	}
public:
	Color albedo;
};
