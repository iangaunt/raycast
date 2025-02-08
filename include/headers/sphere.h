#ifndef SPHERE_H
#define SPHERE_H

class sphere {
    public: 
        double x;
        double y;
        double z;
        int color;

        double r;

        sphere(double xh, double yh, double zh, int colorh, double rh);
        bool contains(double xp, double yp, double zp);
};

#endif