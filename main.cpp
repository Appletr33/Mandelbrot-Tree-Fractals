#include <iostream>
#include <fstream>
#include <chrono>
#include <math.h>

#include <png++/png.hpp>

#include "Tree.hpp"
#include "mandelbrot.hpp"


std::string fractal = "mandelbrot";



int main(int argc, const char * argv[])
{
    int iteration = 0;
    auto startTime = std::chrono::system_clock::now();
    
    if (fractal == "tree")
    {
        int imageWidth = 1000;
        int imageHeight = 1000;
        std::string filename = "tree" + std::to_string(iteration) + ".png";
        png::image< png::rgb_pixel > image(imageWidth, imageHeight);
        
        while (true)
        {
            Tree::fractalTrees(imageWidth / 2, imageHeight - 50, 100.0, -M_PI / 2.0, 0.8, M_PI / 12.0, 5, 5, image); //Last two are Same
            iteration++;
            if (iteration == 1)
                break;
        }
        std::cout << "Finished" << std::endl;
        image.write(filename);
    }
    
    if (fractal == "mandelbrot")
    {
        mandelbrot::generate(5000, 5000, iteration, startTime, 5, 5);
    }
    
    return 0;
}
