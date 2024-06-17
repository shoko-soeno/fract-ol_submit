/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoeno <ssoeno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 13:14:41 by ssoeno            #+#    #+#             */
/*   Updated: 2024/06/17 16:33:09 by ssoeno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

static void	error_and_exit(void)
{
	perror("error");
	exit(EXIT_FAILURE);
}

static void	data_init(t_fractal *fractal)
{
	fractal->escape_value = 4;
	fractal->iteration = 50;
	fractal->shift_x = 0.0;
	fractal->shift_y = 0.0;
	fractal->zoom = 1.0;
}

static void	events_init(t_fractal *fractal)
{
	mlx_hook(fractal->mlx_window, ON_DESTROY, 0, close_window, fractal);
	mlx_key_hook(fractal->mlx_window, key_hook, fractal);
	mlx_mouse_hook(fractal->mlx_window, mouse_handler, fractal);
}
// if (ft_strncmp(fractal->name, "julia", 5) == 0)
// 	mlx_hook(fractal->mlx_window, ON_MOUSEMOVE, 0, julia_track, fractal);

void	fractal_init(t_fractal *fractal)
{
	fractal->mlx_connection = mlx_init();
	if (fractal->mlx_connection == NULL)
		error_and_exit();
	fractal->mlx_window = mlx_new_window(fractal->mlx_connection,
			WIDTH, HEIGHT, fractal->name);
	if (fractal->mlx_window == NULL)
	{
		error_and_exit();
	}
	fractal->img.img_ptr = mlx_new_image(fractal->mlx_connection,
			WIDTH, HEIGHT);
	if (fractal->img.img_ptr == NULL)
	{
		mlx_destroy_window(fractal->mlx_connection, fractal->mlx_window);
		error_and_exit();
	}
	fractal->img.pixels_ptr = mlx_get_data_addr(fractal->img.img_ptr,
			&fractal->img.bits_per_pixel,
			&fractal->img.line_len, &fractal->img.endian);
	events_init(fractal);
	data_init(fractal);
}
