#include <iostream>
#include <fstream> // for files manipulation
#include <complex> // for complex numbers
using namespace std;
 
// Variables
float width =  600;
float height = 600;

// Main Function
int main ()  {
    ofstream my_Image ("mandelbrot.ppm");
    if (my_Image.is_open ()) {
        my_Image << "P3\n" << width << " " << height << " 255\n";
        for (int i = 0; i < width; i++) {
             for (int j = 0; j < height; j++)  {
                  my_Image << 255<< ' ' << 0 << ' ' << 0 << "\n";
             }
        }
        my_Image.close();
    }
    else cout << "Could not open the file";
    return 0;
}