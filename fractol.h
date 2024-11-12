#ifndef FRACTOL_H
# define FRACTOL_H

#include "minilibx-linux/mlx.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800
#define MAX_ITER 216
#define BLACK 0x000000 
#define WHITE 0xFFFFFF 

typedef struct	s_img
{
	void	*img_ptr;
	char	*img_data;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}				t_img;

typedef struct s_mlx_data
{
	char	*name;
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
	double	zoom;
}				t_mlx_data;

typedef struct
{
	double	real;
	double	imag;
}			t_complex;

int	handle_close(t_mlx_data *data);
int	handle_input(int keysym, t_mlx_data *data);
int	mouse_hook(int button, t_mlx_data *data);
void	draw_mandelbrot(t_mlx_data *data);
t_complex	complex_add(t_complex a, t_complex b);
t_complex	complex_square(t_complex z);
double	module(t_complex z);
double linear_interpol(double value, double new_min, double new_max, double old_min, double old_max);

#endif