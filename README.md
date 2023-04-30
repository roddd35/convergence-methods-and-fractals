# convergence-methods-and-fractals
A project developed for the Numerical Methods Laboratory class at University of São Paulo, where we try to find the roots to functions based on the Fixed-Point theorem, Newton method and generate newton basins, so we can analyse fractals on the images 

To compile the project, use the followings commands:

$ gcc -o fixed-point-iteration fixed-point-iteration.c -lm
$ gcc -Wall -pedantic -o newtonMethod newtonMethod.c -lm

To generate the fractal images, use: 

$ gnuplot
$ set terminal png size (1200, 800)
$ set output ”imagename.png”
$ plot ”output.txt”with image pixel
