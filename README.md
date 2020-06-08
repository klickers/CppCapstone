# CPPND: Capstone Mandelbrot

This project generates a Mandelbrot set image (and a third-order Mandelbrot set image) according to specifications from user input.

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

Make sure that the [C++ FreeImage library](https://freeimage.sourceforge.io/) is installed as well.

## File Structure
The project consists of the following files:
- `Window.h` - Creates a "window" for the image to be generated.
- `SaveImage.cpp` - Plots the pixels of the image and saves it to a file.
- `SaveImage.h` - Header file for `SaveImage.cpp`.
- `main.cpp` - Runs the program.

## Rubric Points
- **The project demonstrates an understanding of C++ functions and control structures.**  The `SaveImage.cpp` and `main.cpp` files are divided into functions.  An `if-elseif-else` statement is used in the `void() get_rgb_smooth()` function in `SaveImage.cpp`.
- **The project reads data from a file and process the data, or the program writes data to a file.**  In `void plot()` in `SaveImage.cpp`, the FreeImage library is used to write PNG files of the Mandelbrot set.
- **The project accepts user input and processes the input.**  In the `main()` function in `main.cpp`, users are allowed to input the size and color(s) of the Mandelbrot sets generated.
- **The project uses Object Oriented Programming techniques.**  In the `Window.h` file, a class `Window` is declared.
- **Classes use appropriate access specifiers for class members.**  In the `Window.h` file, class members are specified as `public` and `private`.
- **Class constructors utilize member initialization lists.**  In the `Window.h` file, a member initialization list is used in the `Window()` constructor.

## Basic Build Instructions
1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./Capstone`.
5. Follow the instructions.
6. View generated images in the `/build/` folder.
