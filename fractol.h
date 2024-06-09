/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoeno <ssoeno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 11:54:25 by ssoeno            #+#    #+#             */
/*   Updated: 2024/06/09 17:41:28 by ssoeno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRATOL_H
# define FRATOL_H

# include "./minilibx/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
// # include <X11/X.h>
// # include <X11/keysym.h>

#define KEY_ESC 53
#define WIDTH 500
#define HEIGHT 500
#define MAX_ITER 50
#define ON_MOUSEDOWN 4
#define ON_MOUSEUP 5
#define ON_DESTROY 17
#define ON_KEYDOWN 2

#define KEY_LEFT_ARROW	123 //65361
#define KEY_UP_ARROW 126 //65362
#define KEY_RIGHT_ARROW	124 //65363
#define KEY_DOWN_ARROW	125 //65364

#define KEY_PLUS 69
#define KEY_MINUS 78

#define MAX_ZOOM 10.0
#define MIN_ZOOM 0.1
#define ERROR_MESSAGE "Please enter \n\t\"./fract-ol mandelbrot\" or \n\t\"./fract-ol julia <value_1> <value_2>\"\n"

#define BLACK 0x000000
#define WHITE 0xFFFFFF
#define RED 0xFF0000
#define GREEN 0x00FF00
#define BLUE 0x0000FF

// Psychedelic colors
#define MAGENTA_BURST 0xFF00FF
#define LIME_SHOCK 0xCCFF00
#define NEON_ORANGE 0xFF6600
#define PSYCHEDELIC_PURPLE 0x660066
#define AQUA_DREAM 0x33CCCC
#define HOT_PINK 0xFF66B2
#define ELECTRIC_BLUE 0x0066FF
#define LAVA_RED 0xFF3300

// typedef struct	s_data {
// 	void	*img;
// 	char	*addr;
// 	int		bits_per_pixel;
// 	int		line_length;
// 	int		endian;
// 	float	c_r;
// 	float	c_i;
// 	float	z_r;
// 	float	z_i;
// 	float	max_r;
// 	float	min_r;
// 	float	max_i;
// 	float	min_i;
// 	float	delta_r;
// 	float	delta_i;
// 	float	zoom;
// }				t_data;

// typedef struct	s_vars {
// 	void	*mlx;
// 	void	*win;
// 	int		pos_x;
// 	int		pos_y;
// 	int		radius;
// 	t_data	img;
// }				t_vars;

typedef struct	s_complex
{
	float	x;
	float	y;
}				t_complex;
//x real, y imaginary

typedef struct	s_img
{
	void	*img_ptr;
	char	*pixels_ptr;
	int		bits_per_pixel;
	int		endian;
	int		line_len;
}				t_img;

typedef struct	s_fractal
{
	char	*name;
	void	*mlx_connection; //mlx_init()
	void	*mlx_window;	//mls_new_window()
	t_img	img;
	
	float	escape_value; //hypotenuse
	int		iteration_definition;
	float	shift_x;
	float	shift_y;
	float	zoom;
	float	julia_x;
	float	julia_y;
}				t_fractal;

int		ft_strncmp(char *s1, char *s2, int n);
int		ft_printf(const char *str, ...);
float	atodbl(char *s);
void	fractal_init(t_fractal *fractal);
void	fractal_render(t_fractal *fractal);
float		map(float unscaled_num, float new_min, float new_max, float old_min, float old_max);
t_complex	sum_complex(t_complex z1, t_complex z2);
t_complex	square_complex(t_complex z);

int		close_handler(t_fractal *fractal);
int		key_hander(int keycode, t_fractal *fractal);
int		mouse_handler(int button, int x, int y, t_fractal *fractal);
int		julia_track(int x, int y, t_fractal *fractal);

#endif