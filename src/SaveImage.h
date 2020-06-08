#include <vector>
#include <string>

#ifndef SAVEIMAGE__H
#define SAVEIMAGE__H

#include "Window.h"

// From https://github.com/sol-prog/Mandelbrot_set

void plot(Window<int> &scr, 
          std::vector<int> &colors, 
          int iter_max, 
          const char *fname, 
          bool smooth_color, 
          std::string color, 
          int R, 
          int G, 
          int B);

#endif