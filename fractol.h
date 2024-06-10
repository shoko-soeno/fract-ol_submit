/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoeno <ssoeno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 11:54:25 by ssoeno            #+#    #+#             */
/*   Updated: 2024/06/10 17:06:33 by ssoeno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRATOL_H
# define FRATOL_H

# include "./minilibx/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>

#define WIDTH 500
#define HEIGHT 500
#define KEY_ESC 53
#define ON_MOUSEDOWN 4
#define ON_MOUSEUP 5
#define ON_MOUSEMOVE 6
#define ON_DESTROY 17
#define ON_KEYDOWN 2

#define MAX_ZOOM 10.0
#define MIN_ZOOM 0.1
#define ERROR_MESSAGE "Please enter \n\t\"./fract-ol mandelbrot\" or \n\t\"./fract-ol julia -0.4 0.6\"\n"

#define BLACK 0x000000
#define WHITE 0xFFFFFF
// Psychedelic colors
#define NEON_YELLOW 0xFFFFFF00
#define PSYCHEDELIC_PURPLE 0x660066

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
int		mouse_handler(int button, int x, int y, t_fractal *fractal);
int		julia_track(int x, int y, t_fractal *fractal);

#endif