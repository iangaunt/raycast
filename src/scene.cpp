#include "headers/scene.h"

#include "headers/plane.h"
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

void scene::set_camera(double x, double y, double z) {
    cx = x;
    cy = y;
    cz = z;
}

void scene::add_sphere(sphere* s) {
    spheres.push_back(s);
}

void scene::add_plane(plane* p) {
    planes.push_back(p);
}

void draw_color(double d, int* pixels, int index, int color) {
    int r = color >> 16;
    int g =  color & 0x00FF00 >> 8;
    int b = color & 0x0000FF;

    int r_fixed = max(0, (double) (r) * (1 - d));
    int g_fixed = max(0, (double) (g) * (1 - d));
    int b_fixed = max(0, (double) (b) * (1 - d));

    int col_fixed = ((r_fixed << 16) | (g_fixed << 8) | b_fixed);
    
    pixels[index] = col_fixed;
}

void scene::generate() {
    for (double i = 0; i < width; i++) {
        for (double j = 0; j < height; j++) {
            pixels[(int) (i) + (int) (j) * width] = 0x0;

            vec* v = new vec(
                1,
                (i - (double) (width / 2)) / ((double) (width / 4)), 
                (j - (double) (height / 2)) / ((double) (height / 4))
            );
            v->set_origin(cx, cy, cz);

            bool touched = false;
            double t = inner_window;

            for (t = inner_window; t < outer_window; t += 1) {
                v->calculate_t(t);

                for (int k = 0; k < max(spheres.size(), planes.size()); k++) {
                    if (touched) break;

                    if (spheres.size() > k) {
                        if (spheres.at(k)->contains(v->x, v->y, v->z)) {
                            touched = true;
                        }
                    }

                    if (planes.size() > k) {
                        if (planes.at(k)->past(v->x, v->y, v->z)) {
                            touched = true;
                        }
                    }
                }
            }

            if (!touched) continue;

            // std::cout << t << std::endl;

            double u = t - 1;
            v->calculate_t(u);
            touched = false;

            while (u < t) {
                if (touched) break;

                for (int s = 0; s < spheres.size(); s++) {
                    if (spheres.at(s)->contains(v->x, v->y, v->z)) {
                        t = u;
                        double d = (t - inner_window) / (outer_window - inner_window) * 10;
                    
                        int col = spheres.at(s)->color;
                        std::cout << col << std::endl;
                        
                        int r = col >> 16;
                        int g = col & 0x00FF00 >> 8;
                        int b = col & 0x0000FF;
                    
                        int r_fixed = max(0, (double) (r) * (1 - d));
                        int g_fixed = max(0, (double) (g) * (1 - d));
                        int b_fixed = max(0, (double) (b) * (1 - d));
                    
                        int col_fixed = ((r_fixed << 16) | (g_fixed << 8) | b_fixed);
                        
                        pixels[(int) (i) + (int) (j) * width] = col_fixed;

                        touched = true;
                    }
                }
                
                for (int p = 0; p < planes.size(); p++) {
                    if (planes.at(p)->past(v->x, v->y, v->z)) {
                        t = u;
                        double d = (t - inner_window) / (outer_window - inner_window) * 10;
                    
                        int col = planes.at(p)->color;
                        int r = col >> 16;
                        int g = col & 0x00FF00 >> 8;
                        int b = col & 0x0000FF;
                    
                        int r_fixed = max(0, (double) (r) * (1 - d));
                        int g_fixed = max(0, (double) (g) * (1 - d));
                        int b_fixed = max(0, (double) (b) * (1 - d));
                    
                        int col_fixed = ((r_fixed << 16) | (g_fixed << 8) | b_fixed);
                        
                        pixels[(int) (i) + (int) (j) * width] = col_fixed;

                        touched = true;
                    }
                }
                
                u += 0.025;
                v->calculate_t(u);
            }
        }
    }
}