#pragma once
#include<cmath>
#include<limits>
#include<memory>

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
}

#include"Ray.h"
#include"vec3.h"