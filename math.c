#include "fractol.h"

t_complex	complex_add(t_complex a, t_complex b)
{
	t_complex	result;

	result.real = a.real + b.real;
	result.imag = a.imag + b.imag;
	return (result);
}

t_complex	complex_square(t_complex z)
{
	t_complex	result;

	result.real = z.real * z.real - z.imag * z.imag;
	result.imag = 2 * z.real * z.imag;
	return (result);
}

double	module(t_complex z)
{
	return (sqrt(z.real * z.real + z.imag * z.imag));
}

double linear_interpol(double value, double new_min, double new_max, double old_min, double old_max)
{
    return (new_max - new_min) * (value - old_min) / (old_max - old_min) + new_min;
}