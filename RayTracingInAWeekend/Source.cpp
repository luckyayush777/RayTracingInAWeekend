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

HittableList RandomScene()
{
	HittableList world;
	auto groundMaterial = std::make_shared<Lambertian>(Color(0.5, 0.5, 0.5));
	world.Add(make_shared<Sphere>(Point3(0, -1000, 0), 1000, groundMaterial));

	for (int a = -11; a < 11; a++)
	{
		for (int b = -11; b < 11; b++)
		{
			auto chooseMat = Personal::RandomDouble();
			Point3 center(a + 0.9 * Personal::RandomDouble(), 0.2, b + 0.9 * Personal::RandomDouble());

			if ((center - Point3(4, 0.2, 0)).Length() > 0.9)
			{
				std::shared_ptr<Material> sphereMaterial;

				if (chooseMat < 0.8)
				{
					//DIFFUSE
					auto albedo = Random() * Random();
					sphereMaterial = std::make_shared<Lambertian>(albedo);
					world.Add(std::make_shared<Sphere>(center, 0.2, sphereMaterial));
				} 
				else if (chooseMat < 0.95)
				{
					auto albedo = Random(0.5, 1);
					auto fuzz = Personal::RandomDouble(0, 0.5);
					sphereMaterial = std::make_shared<Metal>(albedo, fuzz);
					world.Add(std::make_shared<Sphere>(center, 0.2, sphereMaterial));
				}
				else
				{
					sphereMaterial = std::make_shared<Dielectric>(1.5);
					world.Add(make_shared<Sphere>(center, 0.2, sphereMaterial));
				}
			}
		}
	}

	auto material1 = std::make_shared<Dielectric>(1.5);
	world.Add(std::make_shared<Sphere>(Point3(0, 1, 0), 1.0, material1));

	auto material2 = std::make_shared<Lambertian>(Color(0.4, 0.2, 0.1));
	world.Add(std::make_shared<Sphere>(Point3(-4, 1, 0), 1.0, material2));

	auto material3 = std::make_shared<Metal>(Color(0.7, 0.6, 0.5), 0.0);
	world.Add(std::make_shared<Sphere>(Point3(4, 1, 0), 1.0, material3));

	return world;



}

int main()
{
	//IMAGE
	const auto aspectRatio = 3.0 / 2.0;
	const int imageWidth = 1200;
	const int imageHeight = static_cast<int>(imageWidth / aspectRatio);
	const int samplesPerPixel = 500;
	const int maxDepth = 50;

	//WORLD
	auto world = RandomScene();





	//CAMERAs
	Point3 lookFrom(13, 2, 3);
	Point3 lookAt(0, 0, 0);
	Vec3 vUp(0, 1, 0);
	auto distToFocus = 10.0;
	auto aperture = 0.1;
	Camera cam(lookFrom, lookAt, vUp, 20, aspectRatio, aperture, distToFocus);

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
