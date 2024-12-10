#include "headers/vec.h"

#include <cmath>

vec::vec(double xih, double yjh, double zkh) {
    xi = xih;
    yj = yjh;
    zk = zkh;
}

double vec::magnitude() {
    return sqrt(x * x + y * y + z * z);
}

void vec::calculate_t(double th) {
    t = th;

    x = xi * t;
    y = yj * t;
    z = zk * t;
}