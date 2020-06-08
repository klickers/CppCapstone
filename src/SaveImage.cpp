#include <tuple>
#include <iostream>
#include <string>

#include <FreeImage.h>
#include "Window.h"
#include "SaveImage.h"

// From https://github.com/sol-prog/Mandelbrot_set

std::tuple<int, int, int> get_rgb_piecewise_linear(int n, int iter_max) {
	int N = 256; // colors per element
	int N3 = N * N * N;
	// map n on the 0..1 interval (real numbers)
	double t = (double)n/(double)iter_max;
	// expand n on the 0 .. 256^3 interval (integers)
	n = (int)(t * (double) N3);

	int b = n/(N * N);
	int nn = n - b * N * N;
	int r = nn/N;
	int g = nn - r * N;
	return std::tuple<int, int, int>(r, g, b);
}

std::tuple<int, int, int> get_rgb_smooth(int n, int iter_max, std::string color, int R, int G, int B) {
	// map n on the 0..1 interval
	double t = (double)n/(double)iter_max;

	// declare variables
	int r, g, b;

	// Use smooth polynomials for r, g, b
  	if (color == "blue")
    {
      	r = (int)(R*(1-t)*t*t*t*255);
        g = (int)(G*(1-t)*(1-t)*t*t*255);
        b = (int)(B*(1-t)*(1-t)*(1-t)*t*255);
    }
  	else if (color == "red")
    {
    	r = (int)(R*(1-t)*(1-t)*(1-t)*t*255);
        g = (int)(G*(1-t)*t*t*t*255);
        b = (int)(B*(1-t)*(1-t)*t*t*255);
    }
	else {
        r = (int)(R*(1-t)*(1-t)*t*t*255);
        g = (int)(G*(1-t)*(1-t)*(1-t)*t*255);
        b = (int)(B*(1-t)*t*t*t*255);
    }
	return std::tuple<int, int, int>(r, g, b);
}


void plot(Window<int> &scr, std::vector<int> &colors, int iter_max, const char *fname, bool smooth_color, 
	std::string color, int R, int G, int B) 
{
	// active only for static linking
	#ifdef FREEIMAGE_LIB
		FreeImage_Initialise();
	#endif

	unsigned int width = scr.width(), height = scr.height();
	FIBITMAP *bitmap = FreeImage_Allocate(width, height, 32); // RGBA

	int k = 0;
	std::tuple<int, int, int> rgb;
	for(int i = scr.yMin(); i < scr.yMax(); ++i) {
		for(int j = scr.xMin(); j < scr.xMax(); ++j) {
			int n = colors[k];

			if( !smooth_color ) {
				rgb = get_rgb_piecewise_linear(n, iter_max);
			}
			else {
				rgb = get_rgb_smooth(n, iter_max, color, R, G, B);
			}

			RGBQUAD col;
			col.rgbRed = std::get<0>(rgb);
			col.rgbGreen = std::get<1>(rgb);
			col.rgbBlue = std::get<2>(rgb);
			col.rgbReserved = 255;

			FreeImage_SetPixelColor(bitmap, j, i, &col);
			k++;
		}
	}

	// Save the image in a PNG file
	FreeImage_Save(FIF_PNG, bitmap, fname, PNG_DEFAULT);

	// Clean bitmap;
	FreeImage_Unload(bitmap);

	// active only for static linking
	#ifdef FREEIMAGE_LIB
		FreeImage_DeInitialise();
	#endif
}