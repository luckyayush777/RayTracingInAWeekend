#pragma once
#include<iostream>
#include"vec3.h"

void WriteColor(std::ostream& out, Color pixelColor)
{
	out << static_cast<int>(255.99 * pixelColor.X()) << ' '
		<< static_cast<int>(255.99 * pixelColor.Y()) << ' '
		<< static_cast<int>(255.99 * pixelColor.Z()) << '\n';
}
