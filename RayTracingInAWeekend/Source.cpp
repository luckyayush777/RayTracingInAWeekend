#include<iostream>
#include"vec3.h"
#include"Color.h"
#include"Ray.h"
Color RayColor(const Ray& ray
)
{
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
			Color pixelColor = RayColor(ray);
			WriteColor(std::cout, pixelColor);

		}
	}
	std::cerr << "\nDone. \n";
}
