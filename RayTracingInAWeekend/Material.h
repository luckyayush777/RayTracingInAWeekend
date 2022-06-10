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
	Metal(const Color& a, double f) : albedo(a), fuzziness(f < 1 ? f : 1) {};
	virtual bool Scatter(const Ray& rayIn, const HitRecord& record, Color& attenuation, Ray& scattered) const override 
	{
		Vec3 reflected = Reflect(UnitVector(rayIn.Direction()), record.normal);
		scattered = Ray(record.point, reflected + fuzziness * RandomInUnitSphere());
		attenuation = albedo;
		return (Dot(scattered.Direction(), record.normal) > 0);
	}
public:
	Color albedo;
	double fuzziness;
};

class Dielectric : public Material {
public :
	double refractiveIndex;
public :
	Dielectric(double ir) : refractiveIndex(ir) {}
	virtual bool Scatter(const Ray& rayIn, const HitRecord& record, Color& attenuation, Ray& scattered)  const override
	{
		attenuation = Color(1.0, 1.0, 1.0);
		double refractionRatio = record.frontFace ? (1.0 / refractiveIndex) : refractiveIndex;
		Vec3 unitDirection = UnitVector(rayIn.Direction());
		double cosTheta = fmin(Dot(-unitDirection, record.normal), 1.0);
		double sinTheta = std::sqrt(1.0 - cosTheta * cosTheta);
		
		bool cannotRefract = refractionRatio * sinTheta > 1.0;
		Vec3 direction;
		if (cannotRefract || Reflectance(cosTheta, refractionRatio) > Personal::RandomDouble())
			direction = Reflect(unitDirection, record.normal);
		else
			direction = Refract(unitDirection, record.normal, refractionRatio);

		scattered = Ray(record.point, direction);
		return true;
	}

private :
	static double Reflectance(double cosine, double refIdx)
	{
		auto r0 = (1 - refIdx) / (1 + refIdx);
		r0 = r0 * r0;
		return r0 + (1 - r0) * pow((1 - cosine), 5);
	}
};
