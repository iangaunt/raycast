#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "sphere.h"

using std::vector;

class scene {
    public: 
        int width;
        int height;

        int inner_window;
        int outer_window;

        int* pixels;
        vector<sphere*> spheres;

        scene(int w, int h, int inner_windowh, int outer_windowh);
        void add(sphere* s);
        void generate();
};

#endif