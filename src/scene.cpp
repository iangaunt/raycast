#include "headers/scene.h"
#include "headers/sphere.h"
#include "headers/vec.h"

#include <cmath>
#include <iostream>

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

            // std::cout << v->xi << " " << v->yj << " " << v->zk << std::endl;

            for (double t = inner_window; t < outer_window; t += 0.01) {
                v->calculate_t(t);
                
                if (touched) break;

                for (int s = 0; s < spheres.size(); s++) {
                    if (spheres.at(s)->contains(v->x, v->y, v->z)) {
                        sphere* k = spheres.at(s);
                        // std::cout << "(" << v->x << ", " << v->y << ", " << v->z << ")" << std::endl;

                        double d = (t - inner_window) / (outer_window - inner_window) * 10;

                        int r = k->color >> 16;
                        int g = k->color & 0x00FF00 >> 8;
                        int b = k->color & 0x0000FF;

                        int r_fixed = (double) (r) * (1 - d);
                        int g_fixed = (double) (g) * (1 - d);
                        int b_fixed = (double) (b) * (1 - d);

                        if (r_fixed < 0) r_fixed = 0;
                        if (g_fixed < 0) g_fixed = 0;
                        if (b_fixed < 0) b_fixed = 0;

                        // std::cout << r_fixed << " " << g_fixed << " " << b_fixed << std::endl;

                        int col_fixed = ((r_fixed << 16) | (g_fixed << 8) | b_fixed);

                        // std::cout << std::hex << col_fixed << std::endl;

                        pixels[(int) (i) + (int) (j) * width] = col_fixed;
                        touched = true;
                        break;
                    }
                }
            }
        }
    }
}