#ifndef VEC_H
#define VEC_H

class vec {
    public:
        double x = 0;
        double y = 0;
        double z = 0;

        double xi;
        double yj;
        double zk;

        double t;

        vec(double xh, double yh, double zh);
        double magnitude(); 
        void calculate_t(double th);
};

#endif