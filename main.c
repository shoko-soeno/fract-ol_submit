/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoeno <ssoeno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 11:54:25 by ssoeno            #+#    #+#             */
/*   Updated: 2024/06/10 17:20:10 by ssoeno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "./minilibx/mlx.h"

long	parse_integer_part(char **s, int *sign)
{
	long	integer_part;

	integer_part = 0;
	while (**s == '+' || **s == '-')
	{
		if (**s == '-')
			*sign *= -1;
		(*s)++;
	}
	while (**s && **s != '.')
	{
		integer_part = (integer_part * 10) + (**s - '0');
		(*s)++;
	}
	return integer_part;
}

float	parse_fraction_part(char **s)
{
	float	fraction_part;
	float	power;

	fraction_part = 0;
	power = 1;
	if (**s == '.')
		(*s)++;
	while (**s)
	{
		power /= 10;
		fraction_part += (**s - '0') * power;
		(*s)++;
	}
	return fraction_part;
}

float ft_atof(char *s)
{
	long	integer_part;
	float	fraction_part;
	int		sign;

	integer_part = 0;
	fraction_part = 0;
	sign = 1;
	while (*s == 32 ||(*s >= 9 && *s <= 13))
		s++;
	integer_part = parse_integer_part(&s, &sign);
	fraction_part = parse_fraction_part(&s);
	return (sign * (integer_part + fraction_part));
}

#include <libc.h>
__attribute__((destructor))
static void destructor() {
    system("leaks -q fract-ol");
}
int main(int ac, char **av)
{
	t_fractal	fractal;

	if ((ac == 2 && ft_strncmp(av[1], "mandelbrot", 10) == 0)
		|| (ac == 4 && ft_strncmp(av[1], "julia", 5) == 0))
	{
		fractal.name = av[1];
		if(!ft_strncmp(av[1], "julia", 5))
		{
			fractal.julia_x = ft_atof(av[2]);
			printf("%f\n", ft_atof(av[2]));
			printf("%f\n", ft_atof(av[3]));
			fractal.julia_y = ft_atof(av[3]);
		}
		fractal_init(&fractal);
		fractal_render(&fractal);
		mlx_loop(fractal.mlx_connection);
	}
	else
	{
		ft_printf(ERROR_MESSAGE);
		exit(EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
