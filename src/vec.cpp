#include "headers/vec.h"

#include <cmath>
#include <iostream>

vec::vec(double xih, double yjh, double zkh) {
    xi = xih;
    yj = yjh;
    zk = zkh;
}

void vec::set_origin(double x, double y, double z) {
    ox = x;
    oy = y;
    oz = z;
}

double vec::magnitude() {
    return sqrt(x * x + y * y + z * z);
}

void vec::calculate_t(double th) {
    t = th;

    x = ox + xi * t;
    y = oy + yj * t;
    z = oz + zk * t;
}

void vec::print() {
    std::cout << "[" << x << ", " << y << ", " << z << "]" << std::endl;
}