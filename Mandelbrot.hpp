#ifndef mandelbrot_hpp
#define mandelbrot_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <math.h>

#include <png++/png.hpp>

class mandelbrot
{
    static double mapToRange(double min1, double max1, double min2, double max2);
public:
    static void generate(int imageWidth, int imageHeight, int iteration, std::chrono::time_point<std::chrono::system_clock> startTime, double valX, double valY);
};

#endif /* mandelbrot_hpp */
