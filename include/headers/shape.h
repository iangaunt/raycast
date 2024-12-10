#ifndef SHAPE_H
#define SHAPE_H

class shape {
    public:
        double x;
        double y;
        double z;
        int color;

        shape();
        shape(double xh, double yh, double zh, int colorh);
        bool contains(double xp, double yp, double zp);
};

#endif