#include "fractol.h"
# include <string.h>

int	handle_close(t_mlx_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_image(data->mlx_ptr, data->img.img_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	exit(0);
}

int	handle_input(int keysym, t_mlx_data *data)
{
	if (keysym == ESC_KEY)
		handle_close(data);
	if (keysym == DOWN_KEY)
		data->move_y += 0.1;
	if (keysym == UP_KEY)
		data->move_y -= 0.1;
	if (keysym == LEFT_KEY)
		data->move_x -= 0.1;
	if (keysym == RIGTH_KEY)
		data->move_x += 0.1;
	image_reset(data);
	draw_fractal(data);
	return (0);
}

void image_reset(t_mlx_data *data)
{
	mlx_destroy_image(data->mlx_ptr, data->img.img_ptr);
	data->img.img_ptr = mlx_new_image(data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	data->img.img_data = mlx_get_data_addr(data->img.img_ptr, &data->img.bits_per_pixel,
			&data->img.size_line, &data->img.endian);
}

int	mouse_hook(int button, int x, int y, t_mlx_data *data)
{
	if (button == ON_MOUSEUP)
	{
		data->zoom *= 1.1;
		data->move_x += (linear_interpol(x, 0, WINDOW_WIDTH, -2, 2) * data->zoom) - (linear_interpol(x, 0, WINDOW_WIDTH, -2, 2) * data->zoom);
        data->move_y += (linear_interpol(y, 0, WINDOW_HEIGHT, 2, -2) * data->zoom) - (linear_interpol(y, 0, WINDOW_HEIGHT, 2, -2) * data->zoom);
	}
		
	else if (button == ON_MOUSEDOWN)
		data->zoom *= 0.90;
	data->mouse_x = x;
	data->mouse_y = y;
	//printf("%i %i\n", data->mouse_x, data->mouse_y);
	image_reset(data);
	draw_fractal(data);
	return (0);
}

void hooks_init(t_mlx_data *data)
{
	mlx_key_hook(data->win_ptr, handle_input, data);
	mlx_mouse_hook(data->win_ptr, mouse_hook, data);
	mlx_hook(data->win_ptr, ON_DESTROY, StructureNotifyMask, handle_close,
		data);
}

int data_init(t_mlx_data *data, char *argv[])
{
		data->name = argv[1];
		data->zoom = 1.0;
		data->move_x = 0;
		data->move_y = 0;
		data->mlx_ptr = mlx_init();
		if (data->mlx_ptr == NULL)
			return (1);
		data->win_ptr = mlx_new_window(data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT,
				"");
		if (data->win_ptr == NULL)
		{
			mlx_destroy_display(data->mlx_ptr);
			free(data->mlx_ptr);
			return (1);
		}
		data->img.img_ptr = mlx_new_image(data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
		data->img.img_data = mlx_get_data_addr(data->img.img_ptr, &data->img.bits_per_pixel,
			&data->img.size_line, &data->img.endian);
		return (0);
}

int main(int argc, char *argv[])
{
	if (argc == 2 && (strcmp(argv[1], "1") == 0 || strcmp(argv[1], "2") == 0) ) // Comprobar que los parametros de julia está bien
	{
		t_mlx_data data;

		if (data_init(&data, argv) == 1)
			return (1);
		hooks_init(&data);
		draw_fractal(&data);
		mlx_loop(data.mlx_ptr);
	}
	else
		write(1, MESSAGE, 64);
	return (0);
}
