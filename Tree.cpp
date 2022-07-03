#include <iostream>
#include <math.h>
#include <png++/png.hpp>

#include "Tree.hpp"

void Tree::branch(float x, float yy, float len, float angle, double R, double G, double B, png::image< png::rgb_pixel > &image)
{
    std::cout << "Branching" << std::endl;
    double y1 = yy;
    double y2 = yy + len * sin(angle);
    double x1 = x;
    double x2 = x + len * cos(angle);
    
    // Bresenham's line algorithm
    const bool steep = (fabs(y2 - y1) > fabs(x2 - x1));
    if(steep)
    {
        std::swap(x1, y1);
        std::swap(x2, y2);
    }

    if(x1 > x2)
    {
        std::swap(x1, x2);
        std::swap(y1, y2);
    }

    const double dx = x2 - x1;
    const double dy = fabs(y2 - y1);

    double error = dx / 2.0f;
    const int ystep = (y1 < y2) ? 1 : -1;
    double y = y1;

    const int maxX = (int)x2;

    for(int x=(int)x1; x<=maxX; x++)
    {
        if(steep)
        {
            image[x][y] = png::rgb_pixel(R, G, B);
        }
        else
        {
            image[y][x] = png::rgb_pixel(R, G, B);
        }

        error -= dy;
        if(error < 0)
        {
           y += ystep;
           error += dx;
        }
    }

}

double Tree::mapToRange(double min1, double max1, double min2, double max2)
{
    double range = max2 - min2;
    return min1 * (range / max1) + min2;
}

void Tree::fractalTrees(float x, float y, float len, float angle, float len_div, float angle_dif, int depth, int maxDepth, png::image< png::rgb_pixel > &image)
{
    double R = depth * sinf(depth);
    R = (mapToRange(R, depth, 200, 255));
    double G = 255;
    double B = 255;
    branch(x, y, len, angle, R, G, B, image);
    if (depth == 0)
        return;
    
    //Left
    fractalTrees(x + len * cos(angle), y + len * sin(angle), len * len_div, angle - angle_dif, len_div, angle_dif, depth - 1, maxDepth, image);
    
    //Right
    fractalTrees(x + len * cos(angle), y + len * sin(angle), len * len_div, angle + angle_dif, len_div, angle_dif, depth - 1, maxDepth, image);
}
