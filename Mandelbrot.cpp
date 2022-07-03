#include "mandelbrot.hpp"


double mandelbrot::mapToRange(double min1, double max1, double min2, double max2)
{
    double range = max2 - min2;
    return min1 * (range / max1) + min2;
}

void mandelbrot::generate(int imageWidth, int imageHeight, int iteration, std::chrono::time_point<std::chrono::system_clock> startTime, double valX, double valY)
{
    //Get current time
    std::chrono::duration<float> iterationTime;
    auto previousTime = std::chrono::system_clock::now();
    auto itterStartTime = previousTime;
    
    
    // Open the output file,  write the PPM header
    std::string filename = "output/" + std::to_string(iteration) + ".png";
    png::image< png::rgb_pixel > image(imageWidth, imageHeight);
    
    std::chrono::duration<float> retard = std::chrono::system_clock::now() - startTime;
    int maxiterations = 1000; // Change around and stuff
    valY /= powf(1.5f, retard.count());
    valX /= powf(1.5f, retard.count());
    valY += 0.1f;
    valX -= 0.1f;
    valY -= sqrtf(0.755 * 0.755 - 0.1 * 0.1);
    valX -= sqrtf(0.755 * 0.755 - 0.1 * 0.1);
    std::cout << "Y: "<< valY << std::endl;
    std::cout << "X: "<< valX << std::endl;
    
    
    for (int y = 0; y < imageHeight; y++)
    {
        for (int x = 0; x < imageWidth; x++)
        {
            double a = mapToRange(x, imageWidth, -valX, valX);
            double b = mapToRange(y, imageHeight, -valY, valY);
            
            double ca = a;
            double cb = b;
            
            int n = 0;

            while (n < maxiterations) //Don't iterate too many times
            {
                double aa = a * a - b * b;
                double bb = 2 * a * b;
                a = aa + ca;
                b = bb + cb;
                if (a + b > 16)
                {
                    break;
                }
                n++;
            }
            
            double bright = mapToRange((double)n, (double)maxiterations, 0.0f, 1.0f);
            bright = mapToRange(sqrtf(bright), 1.0f, 0.0f, 255.0f);
                                    
            if (n == maxiterations)
            {
                bright = 0.0;
            }
            
            double R = bright * sinf(bright);
            double G = (bright * bright);
            double B = bright;
            
            image[y][x] = png::rgb_pixel(R, G, B);
        }
        
        // Display Time
        std::chrono::duration<float> elapsedTime = std::chrono::system_clock::now() - previousTime;
        if ( elapsedTime.count() >= 10.0)
        {
            iterationTime = std::chrono::system_clock::now() - itterStartTime;
            
            std::cout << y << "/" << imageHeight << "\tRUNNING: " << iterationTime.count() << "s\t" << ((float)y / (float)imageHeight) * 100 << "%" << std::endl;
            previousTime = std::chrono::system_clock::now();
        }
    }
    image.write(filename);
    
    //Display Itteration Stats
    iterationTime = std::chrono::system_clock::now() - itterStartTime;
    std::chrono::duration<float> totalTime = std::chrono::system_clock::now() - startTime;
    std::cout << "-------------------------------------------\n\t\t" << iteration << " Iteration Finsished\n" << "\t\t TIME TO COMPLETE ITERATION: " << iterationTime.count() << "\n\t\t TOTAL RUNNING TIME: " << totalTime.count() << "\n-------------------------------------------\n" << std::endl;
}

