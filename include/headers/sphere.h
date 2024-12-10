#ifndef SPHERE_H
#define SPHERE_H

#include "shape.h"

class sphere: public shape {
    public: 
        double x;
        double y;
        double z;
        int color;

        double r;

        sphere(double xh, double yh, double zh, int colorh) : shape(xh, yh, zh, colorh) {}
        sphere(double xh, double yh, double zh, int colorh, double rh);
        bool contains(double xp, double yp, double zp);
};

#endif