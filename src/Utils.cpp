#include "Utils.h"

// From https://github.com/sol-prog/Mandelbrot_set

// Experimental zoom functions - use with care
void zoom(const double window_ratio, 
          const double x0, 
          const double x1,
          const double y0, 
          const double y1, 
          Window<double> &fract) 
{
	double y = (x1 - x0) * window_ratio;
	fract.reset(x0, x1, y0, y + y0);
}