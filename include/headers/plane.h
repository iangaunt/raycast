#ifndef PLANE_H
#define PLANE_H

// Expresses a plane in the form ax + by + cz = d.
class plane {
    public:
        double a;
        double b;
        double c;
        double d;
        int color;
        
        plane(double ah, double bh, double ch, double dh, int colorh);
        bool past(double x, double y, double z);
};

#endif