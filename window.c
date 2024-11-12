#include "fractol.h"


int	handle_close(t_mlx_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	exit(0);
}
int	handle_input(int keysym, t_mlx_data *data)
{
	if (keysym == 0xff1b)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		exit(0);
	}
	return (0);
}

int	mouse_hook(int button, t_mlx_data *data)
{
	
	if (button == 4)
	{
		write(1, "hola", 4);
		data->zoom *= 1.05;
	}	
	else if (button == 5)
	{
		data->zoom *= 0.95;
	}
	draw_mandelbrot(data);
	return (0);
}

void hooks_init(t_mlx_data data)
{
	mlx_key_hook(data.win_ptr, handle_input, &data);
	mlx_mouse_hook(data.win_ptr, mouse_hook, &data);
	mlx_hook(data.win_ptr, 17, 	(1L<<17), handle_close,
		&data);
}

int	main(void)
{
	t_mlx_data data;
	data.zoom = 1.0;

	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (1);
	data.win_ptr = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT,
			"");
	if (data.win_ptr == NULL)
	{
		mlx_destroy_display(data.mlx_ptr);
		free(data.mlx_ptr);
		return (1);
	}
	hooks_init(data);
	/*data.img.img_ptr = mlx_new_image(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	data.img.img_data = mlx_get_data_addr(data.img.img_ptr, &data.img.bits_per_pixel,
			&data.img.size_line, &data.img.endian);*/
	draw_mandelbrot(&data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
