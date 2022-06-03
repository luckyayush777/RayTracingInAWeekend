#pragma once
#include"RTWeekend.h"
#include"Color.h"
#include"HittableList.h"
#include"Sphere.h"
#include<iostream>


Color RayColor(const Ray& ray, const Hittable& world)
{
	HitRecord record;
	if (world.Hit(ray, 0, Personal::AYUSH_INFINITY, record))
	{
		return 0.5 * (record.normal + Color(1, 1, 1));
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

	//WORLD
	HittableList world;
	world.Add(make_shared<Sphere>(Point3(0, 0, -1), 0.5));
	world.Add(make_shared<Sphere>(Point3(1, 0, 1), 100));
	world.Add(make_shared<Sphere>(Point3(0, -100.5, 1), 100));

	//CAMERA
	auto viewportHeight = 2.0;
	auto viewportWidth = aspectRatio * viewportHeight;
	auto focalLength = 1.0;

	auto origin = Point3(0, 0, 0);
	auto horizontal = Vec3(viewportWidth, 0, 0);
	auto vertical = Vec3(0, viewportHeight, 0);
	auto lowerLeftCorner = origin - horizontal / 2 - vertical / 2 - Vec3(0, 0, focalLength);

	//RENDER


	std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";
	for (int j = imageHeight - 1; j >= 0; j--)
	{
		std::cerr << "\rScanlines remaining:" << j << ' ' << std::flush;
		for (int i = 0; i < imageWidth; i++)
		{
			auto u = double(i) / (imageWidth - 1);
			auto v = double(j) / (imageHeight - 1);
			Ray ray(origin, lowerLeftCorner + u * horizontal + v * vertical - origin);
			Color pixelColor = RayColor(ray, world);
			WriteColor(std::cout, pixelColor);

		}
	}
	std::cerr << "\nDone. \n";
}
