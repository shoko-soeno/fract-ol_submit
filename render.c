/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoeno <ssoeno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:30:55 by ssoeno            #+#    #+#             */
/*   Updated: 2024/06/09 18:26:24 by ssoeno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "minilibx/mlx.h"

static void ft_mlx_pixel_put(int x, int y, t_img *img, int color)
{
	int	offset;

	offset = (y * img->line_len) + x * (img->bits_per_pixel / 8);
	*(unsigned int*)(img->pixels_ptr + offset) = color;
}

static void mandelbrot_or_julia(t_complex *z, t_complex *c, t_fractal *fractal)
{
	if(!ft_strncmp(fractal->name, "julia", 5))
	{
		c->x = fractal->julia_x;
		c->y = fractal->julia_y;
	}
	else
	{
		c->x = z->x;
		c->y = z->y;
	}
}
/* フラクタルの種類に応じて、複素数 c の初期値を設定
ジュリア集合の場合は定数を設定, マンデルブロットの場合は現在のピクセル位置に基づいた値を設定 */

float map(float unscaled_num, float new_min, float new_max, float old_min, float old_max)
{
	return (new_max - new_min) * (unscaled_num - old_min) / (old_max - old_min) + new_min;
}

/*
unscaled_num（元の数値）を、ある範囲 (old_min から old_max) から新しい範囲 (new_min から new_max) に変換
1: unscaled_num の old_min からの相対位置を計算 (unscaled_num - old_min) 元の範囲内での数値の位置を示す
2: この相対位置を元の範囲の幅 old_max - old_min で割ることで、元の範囲における相対的な比率（正規化された値）を得る
3: 得られた比率を新しい範囲の幅 new_max - new_min に乗算し、新しい範囲での相対的な位置を得る。
4: 最後に、この値に新しい範囲の最小値 new_min を加えることで、最終的な変換後の数値を得る
例）unscaled_num = 5 が old_min = 0、old_max = 10 の範囲内にあり、
新しい範囲が new_min = 0、new_max = 100 だとすると、この関数は 5 を 0 から 100 の範囲にマッピングする
計算すると、5 は元の範囲の中央に位置するため、新しい範囲でも中央の 50 にマッピングされる。
*/

/*
 *		MANDELBROT
 *		z = z^2 + c
 *		z initially is (0, 0)
 *		c is the actual point
 *		z = z^2 + c -> z1 = c + c
 *
 *		JULIA
 *		./fractol julia <real> <i> 
 *		z = pixel_point + constant
*/

t_complex   sum_complex(t_complex z1, t_complex z2)
{
    t_complex   result;

    result.x = z1.x + z2.x;
    result.y = z1.y + z2.y;
    return result;
}
/* 複素数の和 */

t_complex	square_complex(t_complex z)
{
	t_complex	result;

	result.x = pow(z.x, 2) - pow(z.y, 2); //新しい複素数の実部
	result.y = 2 * z.x * z.y; //新しい複素数の虚部
	return result;
}
/* 複素数の二乗
複素数 z が z=x+yi の形（x は実部、y は虚部）で表される場合、その自乗の実部はx^2-y^2
虚部は2xyになる
*/

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
		z = sum_complex(square_complex(z), c);
		if ((z.x * z.x) + (z.y * z.y) > 4)
		{
			color = map(i, BLACK, WHITE, 0, fractal->iteration_definition);
			ft_mlx_pixel_put(x, y, &fractal->img, color);
			return ;
		}
		i++;
	}
	ft_mlx_pixel_put(x, y, &fractal->img, WHITE);
}

// int	ft_draw_mandelbrot(t_data *data)
// {
// 	int	x;
// 	int	y;

// 	data->delta_r = (data->max_r - data->min_r) / (float)WIDTH / data->zoom;
// 	data->delta_i = (data->max_i - data->min_i) / (float)HEIGHT / data->zoom;
// 	y = - HEIGHT / 2;
// 	while(y < HEIGHT / 2)
// 	{
// 		x = - WIDTH / 2;
// 		while (x < WIDTH / 2)
// 		{
// 			data->c_r = data->min_r + (x + WIDTH/2) * data->delta_r;
// 			data->c_i = data->min_i + (y + HEIGHT/2) * data->delta_i;
// 			data->z_r = 0;
// 			data->z_i = 0;
// 			ft_mlx_pixel_put(data, x+ WIDTH/2, y+ HEIGHT/2, ft_pick_color(data));
// 			x++;
// 		}
// 		y++;
// 	}
// 	return 0;
// }

void	fractal_render(t_fractal *fractal)
{
	int x;
	int y;

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