#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "plane.h"
#include "sphere.h"

using std::vector;

class scene {
    public: 
        int width;
        int height;

        double cx = 0;
        double cy = 0;
        double cz = 0;

        int inner_window;
        int outer_window;

        int* pixels;
        vector<sphere*> spheres;
        vector<plane*> planes;

        scene(int w, int h, int inner_windowh, int outer_windowh);
        void set_camera(double x, double y, double z);
        void add_sphere(sphere* s);
        void add_plane(plane* p);
        void generate();
};

#endif