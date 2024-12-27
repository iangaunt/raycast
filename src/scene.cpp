#include "headers/scene.h"
#include "headers/sphere.h"
#include "headers/vec.h"

#include <cmath>
#include <iostream>

int max(double a, double b) {
    return a > b ? a : b;
}

scene::scene(int w, int h, int inner_windowh, int outer_windowh) {
    width = w;
    height = h;
    inner_window = inner_windowh;
    outer_window = outer_windowh;

    pixels = new int[width * height];
}

void scene::add(sphere* s) {
    spheres.push_back(s);
}

void scene::generate() {
    for (int i = 0; i < width * height; i++) {
        pixels[i] = 0x0;
    }

    for (double i = 0; i < width; i++) {
        for (double j = 0; j < height; j++) {
            pixels[(int) (i) + (int) (j) * width] = 0x0;

            vec* v = new vec(
                1,
                (i - (double) (width / 2)) / ((double) (width / 4)), 
                (j - (double) (height / 2)) / ((double) (height / 4))
            );

            bool touched = false;

            for (double t = inner_window; t < outer_window; t += 1) {
                v->calculate_t(t);
                
                if (touched) break;

                for (int s = 0; s < spheres.size(); s++) {
                    if (spheres.at(s)->contains(v->x, v->y, v->z)) {
                        sphere* k = spheres.at(s);

                        double u = t - 1;
                        v->calculate_t(u);

                        while (!k->contains(v->x, v->y, v->z)) {
                            u += 0.01;
                            v->calculate_t(u);
                        }
                        t = u;

                        double d = (t - inner_window) / (outer_window - inner_window) * 10;

                        int r = k->color >> 16;
                        int g = (k->color & 0x00FF00) >> 8;
                        int b = k->color & 0x0000FF;

                        int r_fixed = max(0, (double) (r) * (1 - d));
                        int g_fixed = max(0, (double) (g) * (1 - d));
                        int b_fixed = max(0, (double) (b) * (1 - d));

                        int col_fixed = ((r_fixed << 16) | (g_fixed << 8) | b_fixed);
                        
                        pixels[(int) (i) + (int) (j) * width] = col_fixed;
                        touched = true;
                        break;
                    }
                }
            }
        }
    }
}