#pragma once
#include<cmath>
#include<limits>
#include<memory>
#include<random>

namespace Personal {
    // Usings

    using std::shared_ptr;
    using std::make_shared;
    using std::sqrt;

    // Constants

    const double AYUSH_INFINITY = std::numeric_limits<double>::infinity();
    const double PI = 3.1415926535897932385;

    // Utility Functions

    inline double degrees_to_radians(double degrees) {
        return degrees * PI / 180.0;
    }

    inline double Clamp(double x, double min, double max)
    {
        if (x < min) return min;
        if (x > max) return max;
        return x;
    }

    inline double RandomDouble() {
        static std::uniform_real_distribution<double> distribution(0.0, 1.0);
        static std::mt19937 generator;
        return distribution(generator);
    }

    inline double RandomDouble(double min, double max)
    {
        return min + (max - min) * RandomDouble();
    }
}

#include"Ray.h"
#include"vec3.h"