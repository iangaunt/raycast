#ifndef VEC_H
#define VEC_H

class vec {
    public:
        double x = 0;
        double y = 0;
        double z = 0;

        double ox = 0;
        double oy = 0;
        double oz = 0;

        double xi;
        double yj;
        double zk;

        double t;

        vec(double xh, double yh, double zh);
        void set_origin(double x, double y, double z);
        double magnitude(); 
        void calculate_t(double th);
        void print();
};

#endif