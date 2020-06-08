#include <iostream>
#include <complex>
#include <vector>
#include <string>
#include <chrono>
#include <functional>

#include "Window.h"
#include "SaveImage.h"

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
	const std::function<Complex( Complex, Complex)> &func, const char *fname, bool smooth_color, 
	std::string color, int R, int G, int B) 
{
	auto start = std::chrono::steady_clock::now();
	get_number_iterations(scr, fract, iter_max, colors, func);
	auto end = std::chrono::steady_clock::now();
	std::cout << "Time to generate " << fname << " = " << std::chrono::duration <double, std::milli> (end - start).count() << " [ms]" << std::endl;

	// Save (show) the result as an image
	plot(scr, colors, iter_max, fname, smooth_color, color, R, G, B);
}

void mandelbrot(int length, std::string color, int R, int G, int B) {
	// Define the size of the image
	Window<int> scr(0, length, 0, length);
	// The domain in which we test for points
	Window<double> fract(-2.2, 1.2, -1.7, 1.7);

	// The function used to calculate the fractal
	auto func = [] (Complex z, Complex c) -> Complex {return z * z + c; };

	int iter_max = 400;
	const char *fname = "mandelbrot.png";
	bool smooth_color = false;
	std::vector<int> colors(scr.size());
	
	fractal(scr, fract, iter_max, colors, func, fname, smooth_color, color, R, G, B);
}

void triple_mandelbrot(int length, std::string color, int R, int G, int B) {
	// Define the size of the image
	Window<int> scr(0, length, 0, length);
	// The domain in which we test for points
	Window<double> fract(-1.5, 1.5, -1.5, 1.5);

	// The function used to calculate the fractal
	auto func = [] (Complex z, Complex c) -> Complex {return z * z * z + c; };

	int iter_max = 500;
	const char *fname = "triple_mandelbrot.png";
	bool smooth_color = false;
	std::vector<int> colors(scr.size());

	fractal(scr, fract, iter_max, colors, func, fname, smooth_color, color, R, G, B);
}

int main() {

	int length, R, G, B;
	std::string yes, smooth, color;

	std::cout << "Welcome!  We'll generate a Mandelbrot (and triple Mandelbrot) image according to your specifications." << std::endl;
	std::cout << "You will get to choose the size of the image (it's a square) and the main color of the image." << std::endl;
	std::cout << "You will also be able to enter the values to multiply the Red, Green, and Blue rgb values by." << std::endl;
	std::cout << "Type 'yes' to begin!" << std::endl;
	std::cin >> yes;
  	std::cout << "Length of image's side: " << std::endl;
	std::cin >> length;
	std::cout << "Main color of image: (red, green, or blue)" << std::endl;
	std::cin >> color;
	std::cout << "Multiply Red value by: " << std::endl;
	std::cin >> R;
	std::cout << "Multiply Green value by: " << std::endl;
	std::cin >> G;
	std::cout << "Multiply Blue value by: " << std::endl;
	std::cin >> B;

	mandelbrot(length, color, R, G, B);
	triple_mandelbrot(length, color, R, G, B);

	std::cout << "Images have been generated!  Check the /build/ folder." << std::endl;

	return 0;
}