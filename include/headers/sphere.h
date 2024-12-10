#ifndef SPHERE_H
#define SPHERE_H

class sphere {
    public: 
        double x;
        double y;
        double z;
        double r;
        int color;

        sphere(double xh, double yh, double zh, double rh, int colorh);
        bool contains(double xp, double yp, double zp);
};

#endif