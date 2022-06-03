#pragma once
#include<iostream>
#include"vec3.h"
#include"RTWeekend.h"
void WriteColor(std::ostream& out, Color pixelColor, int samplesPerPixel)
{
	auto red = pixelColor.X();
	auto green = pixelColor.Y();
	auto blue = pixelColor.Z();

	auto scale = 1.0 / samplesPerPixel;
	red *= scale;
	green *= scale;
	blue *= scale;
	
	out << static_cast<int>(256 * Personal::Clamp(red, 0.0, 0.999)) << ' '
		<< static_cast<int>(256 * Personal::Clamp(green, 0.0, 0.999)) << ' '
		<< static_cast<int>(256 * Personal::Clamp(blue, 0.0, 0.999)) << '\n';
}
