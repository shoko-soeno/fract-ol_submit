/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoeno <ssoeno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 11:54:25 by ssoeno            #+#    #+#             */
/*   Updated: 2024/06/17 17:40:21 by ssoeno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

static void	print_error_message(void)
{
	ft_printf("Please enter \n\t\"./fractol mandelbrot\" or\n");
	ft_printf("\t\"./fractol julia value1 value2\" or\n");
	ft_printf("\t\"./fractol burning_ship\"\n");
	ft_printf("\tFor example, \"./fractol julia -0.45 0.6\"\n");
	return ;
}

// #include <libc.h>
// __attribute__((destructor))
// static void destructor() {
//     system("leaks -q fract-ol");
// }
int	main(int ac, char **av)
{
	t_fractal	fractal;

	if ((ac == 2 && ft_strncmp(av[1], "mandelbrot", 11) == 0)
		|| ((ac == 4 && ft_strncmp(av[1], "julia", 6) == 0
				&& is_double(av[2]) && is_double(av[3])))
		|| (ac == 2 && ft_strncmp(av[1], "burning_ship", 13) == 0))
	{
		fractal.name = av[1];
		if (ft_strncmp(av[1], "julia", 6) == 0)
		{
			fractal.julia_x = ft_atolf(av[2]);
			fractal.julia_y = ft_atolf(av[3]);
		}
		fractal_init(&fractal);
		fractal_render(&fractal);
		mlx_loop(fractal.mlx_connection);
	}
	else
	{
		print_error_message();
		exit(EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
