/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoeno <ssoeno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 13:48:56 by ssoeno            #+#    #+#             */
/*   Updated: 2024/06/09 18:39:58 by ssoeno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "minilibx/mlx.h"

int close_window(t_fractal *fractal)
{
	mlx_destroy_image(fractal->mlx_connection,
					fractal->img.img_ptr);
	mlx_destroy_window(fractal->mlx_connection, fractal->mlx_window);
	//exit(EXIT_SUCCESS);
	return (0);
}

int	key_handler(int keycode, t_fractal *fractal)
{
	if (keycode == KEY_ESC)
		return (close_window(fractal), 0);
	if (keycode == KEY_LEFT_ARROW)
		fractal->shift_x += (0.5 * fractal->zoom);
	else if (keycode == KEY_RIGHT_ARROW)
		fractal->shift_x -= (0.5 * fractal->zoom);
	else if (keycode == KEY_UP_ARROW)
		fractal->shift_y -= (0.5 * fractal->zoom);
	else if (keycode == KEY_DOWN_ARROW)
		fractal->shift_y += (0.5 * fractal->zoom);
	else if (keycode == KEY_PLUS)
		fractal->iteration_definition += 10;
	else if (keycode == KEY_MINUS)
		fractal->iteration_definition -= 10;
	fractal_render(fractal);
	return 0;
}

int	mouse_handler(int button, int x, int y, t_fractal *fractal)
{
	(void) x;
	(void) y;
	if (button == 4 && fractal->zoom < MAX_ZOOM)
	{
		fractal->zoom *= 1.1;
	}
	else if (button == 5 && fractal->zoom > MIN_ZOOM)
	{
		fractal->zoom *= 0.9;
	}
	fractal_render(fractal);
	return 0;
}

int	julia_track(int x, int y, t_fractal *fractal)
{
	if (!ft_strncmp(fractal->name, "julia", 5))
	{
		fractal->julia_x = (map(x, -2, +2, 0, WIDTH) * fractal->zoom) + fractal->shift_x;
		fractal->julia_y = (map(y, +2, -2, 0, HEIGHT) * fractal->zoom) + fractal->shift_y;
		fractal_render(fractal);
	}
	return 0;
}
