#include "fractol.h"

void	my_pixel_put(int x, int y, t_img *img, int color)
{
	*(unsigned int *)(img->img_data + (y * img->size_line + x
				* (img->bits_per_pixel / 8))) = color;
}

void	mandelbrot(t_mlx_data *data, int x, int y)
{
	t_complex	c;
	t_complex	z;
	int			iter;
	int			color;

	c.real = (linear_interpol(x, -2, 2, 0, WINDOW_WIDTH) + data->move_x)
		* data->zoom; // Pensar como implementar que me haga el movimineto proporcional y el zoom siga al raton
	c.imag = (linear_interpol(y, 2, -2, 0, WINDOW_HEIGHT) + data->move_y)
		* data->zoom;
	z.real = 0;
	z.imag = 0;
	iter = 0;
	while (iter < MAX_ITER)
	{
		z = complex_add(complex_square(z), c);
		if (module(z) > 2.0)
		{
			color = linear_interpol(iter, BLACK, WHITE, 0, MAX_ITER);
			my_pixel_put(x, y, &data->img, color);
			break ;
		}
		iter++;
	}
	if (iter == MAX_ITER)
		my_pixel_put(x, y, &data->img, BLACK);
}
void	julia(t_mlx_data *data, int x, int y)
{
	t_complex	c;
	t_complex	z;
	int			iter;
	int			color;

	c.real = -0.70176;
	c.imag = 0.3842;
	z.real = (linear_interpol(x, 0, WINDOW_WIDTH, -2, 2) + data->move_x)
		* data->zoom;
	z.imag = (linear_interpol(y, 0, WINDOW_HEIGHT, 2, -2) + data->move_y)
		* data->zoom;
	iter = 0;
	while (iter < MAX_ITER)
	{
		z = complex_add(complex_square(z), c);
		if (module(z) > 2.0)
		{
			color = linear_interpol(iter, BLACK, WHITE, 0, MAX_ITER);
			my_pixel_put(x, y, &data->img, color);
			break ;
		}
		iter++;
	}
	if (iter == MAX_ITER)
		my_pixel_put(x, y, &data->img, BLACK);
}
void	draw_fractal(t_mlx_data *data)
{
	int	x;
	int	y;

	x = 0;
	while (x < WINDOW_WIDTH)
	{
		y = 0;
		while (y < WINDOW_HEIGHT)
		{
			if (data->name[0] == '1')
				mandelbrot(data, x, y);
			else if (data->name[0] == '2')
			{
				julia(data, x, y);
			}
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img_ptr, 0,
		0);
	// mlx_destroy_image(data->mlx_ptr, data->img.img_ptr);
}
