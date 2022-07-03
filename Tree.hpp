#ifndef Tree_hpp
#define Tree_hpp

#include <stdio.h>
#include <png++/png.hpp>

class Tree
{
public:
    static void branch(float, float, float, float, double, double, double, png::image<png::rgb_pixel> &image);
    static double mapToRange(double, double, double, double);
    static void fractalTrees(float, float, float, float, float, float, int, int, png::image<png::rgb_pixel> &image);
};



#endif /* Tree_hpp */
