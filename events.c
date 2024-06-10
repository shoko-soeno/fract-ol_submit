/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoeno <ssoeno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 13:48:56 by ssoeno            #+#    #+#             */
/*   Updated: 2024/06/10 17:14:44 by ssoeno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "minilibx/mlx.h"

int close_window(t_fractal *fractal)
{
	mlx_destroy_image(fractal->mlx_connection,
					fractal->img.img_ptr);
	mlx_destroy_window(fractal->mlx_connection, fractal->mlx_window);
	//free(fractal->mlx_connection);
	exit(EXIT_SUCCESS);
	return (0);
}
int key_hook(int keycode, t_fractal *fractal)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_image(fractal->mlx_connection,
					fractal->img.img_ptr);
		mlx_destroy_window(fractal->mlx_connection, fractal->mlx_window);
		exit(EXIT_SUCCESS);
	}
	return 0;
}

int	mouse_handler(int button, int x, int y, t_fractal *fractal)
{
	(void) x;
	(void) y;
	if (button == 4 && fractal->zoom < MAX_ZOOM)
		fractal->zoom *= 1.1;
	else if (button == 5 && fractal->zoom > MIN_ZOOM)
		fractal->zoom *= 0.9;
	else if (button == 2 && fractal->iteration_definition < 200)
		fractal->iteration_definition += 10;
	else if (button == 1 && fractal->iteration_definition > 20)
		fractal->iteration_definition -= 10;
	fractal_render(fractal);
	return 0;
}

int	julia_track(int x, int y, t_fractal *fractal)
{
	if (ft_strncmp(fractal->name, "julia", 5) == 0)
	{
		fractal->julia_x = (map(x, -2, +2, 0, WIDTH) * fractal->zoom) + fractal->shift_x;
		fractal->julia_y = (map(y, +2, -2, 0, HEIGHT) * fractal->zoom) + fractal->shift_y;
		fractal_render(fractal);
	}
	return 0;
}

/*
1. julia_track 関数
この関数はマウスが動くたびに呼び出されます（ON_MOUSEMOVE イベント）。
マウスの位置x,y を取得し、それをジュリア集合のパラメータc の新しい値に変換（handle_pixel 関数）
map 関数を使用して、マウスの画面上の座標をフラクタルの複素平面上の座標に変換し、これが新しい 
c の実部と虚部になる
*/
