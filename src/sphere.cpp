#include "headers/sphere.h"

sphere::sphere(double xh, double yh, double zh, double rh, int colorh) {
    x = xh;
    y = yh;
    z = zh;
    r = rh;
    color = colorh;
}

bool sphere::contains(double xp, double yp, double zp) {
    double xd = x - xp;
    double yd = y - yp;
    double zd = z - zp;

    return (xd * xd + yd * yd + zd * zd) < r;
}