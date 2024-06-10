/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoeno <ssoeno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:30:55 by ssoeno            #+#    #+#             */
/*   Updated: 2024/06/10 17:02:43 by ssoeno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "minilibx/mlx.h"

void mandelbrot_or_julia(t_complex *z, t_complex *c, t_fractal *fractal);

static void ft_mlx_pixel_put(int x, int y, t_img *img, int color)
{
	int	offset;

	offset = (y * img->line_len) + x * (img->bits_per_pixel / 8);
	*(unsigned int*)(img->pixels_ptr + offset) = color;
}

float map(float unscaled_num, float new_min, float new_max, float old_min, float old_max)
{
	return (new_max - new_min) * (unscaled_num - old_min) / (old_max - old_min) + new_min;
}
/*
Converts unscaled_num from one range (old_min to old_max) to a new range (new_min to new_max).
1: Calculate the relative position of unscaled_num from old_min (unscaled_num - old_min), 
2: Divide this relative position by the width of the original range (old_max - old_min) 
3: Multiply the obtained ratio by the width of the new range (new_max - new_min) 
4: add the minimum value of the new range (new_min) to this value 
Example: If unscaled_num = 5 is within a range of old_min = 0 and old_max = 10, 
	and the new range is new_min = 0 and new_max = 100,
	this function will map 5 to 50 in the new range.
*/

t_complex square_and_add(t_complex z, t_complex c)
{
	t_complex result;

	result.x = pow(z.x, 2) - pow(z.y, 2) + c.x;
	result.y = 2 * z.x * z.y + c.y;
	return result;
}

static void	handle_pixel(int x, int y, t_fractal *fractal)
{
	t_complex	z;
	t_complex	c;
	int			i;
	int			color;

	i = 0;
	z.x = map(x, -2, +2, 0, WIDTH) * fractal->zoom + fractal->shift_x;
	z.y = map(y, -2, +2, 0, HEIGHT) * fractal->zoom + fractal->shift_y;
	mandelbrot_or_julia(&z, &c, fractal);
	while (i < fractal->iteration_definition)
	{
		z = square_and_add(z, c);
		if ((z.x * z.x) + (z.y * z.y) > 4)
		{
			color = map(i, PSYCHEDELIC_PURPLE, NEON_YELLOW, 0, fractal->iteration_definition);
			ft_mlx_pixel_put(x, y, &fractal->img, color);
			return ;
		}
		i++;
	}
	ft_mlx_pixel_put(x, y, &fractal->img, WHITE);
}

void	fractal_render(t_fractal *fractal)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			handle_pixel(x, y, fractal);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fractal->mlx_connection, fractal->mlx_window, 
							fractal->img.img_ptr, 0, 0);
}
