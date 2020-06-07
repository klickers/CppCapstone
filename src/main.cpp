#include <iostream>
#include <complex>
#include <vector>
#include <string>
#include <chrono>
#include <functional>

#include "Window.h"
#include "SaveImage.h"
#include "Utils.h"

// From https://github.com/sol-prog/Mandelbrot_set

// clang++ -std=c++11 -stdlib=libc++ -O3 save_image.cpp utils.cpp mandel.cpp -lfreeimage

// Use an alias to simplify the use of complex type
using Complex = std::complex<double>;

// Convert a pixel coordinate to the complex domain
Complex scale(Window<int> &scr, Window<double> &fr, Complex c) {
	Complex aux(c.real() / (double)scr.width() * fr.width() + fr.xMin(),
		c.imag() / (double)scr.height() * fr.height() + fr.yMin());
	return aux;
}

// Check if a point is in the set or escapes to infinity, return the number if iterations
int escape(Complex c, int iter_max, const std::function<Complex( Complex, Complex)> &func) {
	Complex z(0);
	int iter = 0;

	while (abs(z) < 2.0 && iter < iter_max) {
		z = func(z, c);
		iter++;
	}

	return iter;
}

// Loop over each pixel from our image and check if the points associated with this pixel escape to infinity
void get_number_iterations(Window<int> &scr, Window<double> &fract, int iter_max, std::vector<int> &colors,
	const std::function<Complex( Complex, Complex)> &func) {
	int k = 0, progress = -1;
	for(int i = scr.yMin(); i < scr.yMax(); ++i) {
		for(int j = scr.xMin(); j < scr.xMax(); ++j) {
			Complex c((double)j, (double)i);
			c = scale(scr, fract, c);
			colors[k] = escape(c, iter_max, func);
			k++;
		}
		if(progress < (int)(i*100.0/scr.yMax())){
			progress = (int)(i*100.0/scr.yMax());
			std::cout << progress << "%\n";
		}
	}
}

void fractal(Window<int> &scr, Window<double> &fract, int iter_max, std::vector<int> &colors,
	const std::function<Complex( Complex, Complex)> &func, const char *fname, bool smooth_color) {
	auto start = std::chrono::steady_clock::now();
	get_number_iterations(scr, fract, iter_max, colors, func);
	auto end = std::chrono::steady_clock::now();
	std::cout << "Time to generate " << fname << " = " << std::chrono::duration <double, std::milli> (end - start).count() << " [ms]" << std::endl;

	// Save (show) the result as an image
	plot(scr, colors, iter_max, fname, smooth_color);
}

void mandelbrot(int width, int height) {
	// Define the size of the image
	Window<int> scr(0, width, 0, height);
	// The domain in which we test for points
	// Window<double> fract(-2.2, 1.2, -1.7, 1.7);
  	Window<double> fract(-1.2, 2.2, -2.7, 2.7);

	// The function used to calculate the fractal
	auto func = [] (Complex z, Complex c) -> Complex {return z * z + c; };

	int iter_max = 400;
	const char *fname = "mandelbrot.png";
	bool smooth_color = true;
	std::vector<int> colors(scr.size());

	// Experimental zoom (bugs ?). This will modify the fract window (the domain in which we calculate the fractal function) 
	//zoom(1.0, -1.225, -1.22, 0.15, 0.16, fract); //Z2
	
	fractal(scr, fract, iter_max, colors, func, fname, smooth_color);
}

void triple_mandelbrot(int width, int height) {
	// Define the size of the image
	Window<int> scr(0, width, 0, height);
	// The domain in which we test for points
	Window<double> fract(-1.5, 1.5, -1.5, 1.5);

	// The function used to calculate the fractal
	auto func = [] (Complex z, Complex c) -> Complex {return z * z * z + c; };

	int iter_max = 500;
	const char *fname = "triple_mandelbrot.png";
	bool smooth_color = true;
	std::vector<int> colors(scr.size());

	fractal(scr, fract, iter_max, colors, func, fname, smooth_color);
}

int main() {

	int width, height;

  	std::cout << "Width of image: " << std::endl;
	std::cin >> width;
	std::cout << "Height of image: " << std::endl;
  	std::cin >> height;

	mandelbrot(width, height);
	triple_mandelbrot(width, height);

	return 0;
}