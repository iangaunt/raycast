#include "headers/shape.h"

shape::shape() {
    x = 0;
    y = 0;
    z = 0;
    color = 0;
}

shape::shape(double xh, double yh, double zh, int colorh) {
    x = xh;
    y = yh;
    z = zh;
    color = colorh;
}

bool shape::contains(double xp, double yp, double zp) {
    return true;
}