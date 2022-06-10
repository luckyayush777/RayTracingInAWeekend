#pragma once
#include"RTWeekend.h"
#include"Color.h"
#include"HittableList.h"
#include"Sphere.h"
#include"Camera.h"
#include<iostream>
#include"Material.h"
Color RayColor(const Ray& ray, const Hittable& world, int depth)
{
	HitRecord record;
	if (depth <= 0)
		return Color(0, 0, 0);
	if (world.Hit(ray, 0.001, Personal::AYUSH_INFINITY, record))
	{
		Ray scattered;
		Color attenuation;
		if (record.matPtr->Scatter(ray, record, attenuation, scattered))
			return attenuation * RayColor(scattered, world, depth - 1);
		return Color(0, 0, 0);

	}
	Vec3 unitDirection = UnitVector(ray.Direction());
	auto t = 0.5 * (unitDirection.Y() + 1.0);
	return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
}

int main()
{
	//IMAGE
	const auto aspectRatio = 16.0 / 9.0;
	const int imageWidth = 400;
	const int imageHeight = static_cast<int>(imageWidth / aspectRatio);
	const int samplesPerPixel = 100;
	const int maxDepth = 50;

	//WORLD
	HittableList world;

	auto materialGround = std::make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
	auto materialCenter = std::make_shared<Lambertian>(Color(0.1, 0.2, 0.5));
	auto materialLeft = std::make_shared<Dielectric>(1.5);
	auto materialRight = std::make_shared<Metal>(Color(0.8, 0.6, 0.2), 1.0);

	world.Add(make_shared<Sphere>(Point3(0.0, -100.5, -1.0), 100.0, materialGround));
	world.Add(make_shared<Sphere>(Point3(0.0, 0.0, -1.0), 0.5, materialCenter));
	world.Add(make_shared<Sphere>(Point3(-1.0, 0.0, -1.0), 0.5, materialLeft));
	world.Add(make_shared<Sphere>(Point3(-1.0, 0.0, -1.0), -0.4, materialLeft));

	world.Add(make_shared<Sphere>(Point3(1.0, 0.0, -1.0), 0.5, materialRight));



	//CAMERAs
	Camera cam;

	//RENDER


	std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";
	for (int j = imageHeight - 1; j >= 0; j--)
	{
		std::cerr << "\rScanlines remaining:" << j << ' ' << std::flush;
		for (int i = 0; i < imageWidth; i++)
		{
			Color pixelColor(0, 0, 0);
			for (int s = 0; s < samplesPerPixel; ++s)
			{
				auto u = (i + Personal::RandomDouble()) / (imageWidth - 1);
				auto v = (j + Personal::RandomDouble()) / (imageHeight - 1);
				Ray ray = cam.GetRay(u, v);
				pixelColor += RayColor(ray, world, maxDepth);
			}
			WriteColor(std::cout, pixelColor, samplesPerPixel);

		}
	}
	std::cerr << "\nDone. \n";
}
