#include "headers/plane.h"

plane::plane(double ah, double bh, double ch, double dh, int colorh) {
    a = ah;
    b = bh;
    c = ch;
    d = dh;
    color = colorh;
}

bool plane::past(double x, double y, double z) {
    return (a * x + b * y + c * z) > d;
}