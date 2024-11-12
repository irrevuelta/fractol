#include "fractol.h"

void	my_pixel_put(int x, int y, t_img *img, int color)
{
	*(unsigned int *)(img->img_data + (y * img->size_line + x
						* (img->bits_per_pixel / 8))) = color;
}

void	draw_mandelbrot(t_mlx_data *data)
{
	t_complex	c;
	t_complex	z;
	int			iter;
	int			color;
    int x;
    int y;

    x = 0;
	data->img.img_ptr = mlx_new_image(data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	data->img.img_data = mlx_get_data_addr(data->img.img_ptr, &data->img.bits_per_pixel,
			&data->img.size_line, &data->img.endian);
	while(x < WINDOW_WIDTH)
	{
        y = 0;
		
		while(y < WINDOW_HEIGHT)
		{
			c.real = linear_interpol(x, -2, +2, 0, WINDOW_WIDTH)*data->zoom;
			c.imag = linear_interpol(y, -2, +2, 0, WINDOW_HEIGHT)*data->zoom;
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
			//my_pixel_put(x, y, &data->img, WHITE); //-> ponerlo en una función aparteeee todo lo del bucle y salir con return
            y++;
		}
        x++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img_ptr, 0,
		0);
	mlx_destroy_image(data->mlx_ptr, data->img.img_ptr);
}
