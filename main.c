/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 21:04:30 by ztouzri           #+#    #+#             */
/*   Updated: 2021/06/14 17:43:31y ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	isincircle(int x, int y, t_display *display)
{
	double	distance;

	distance = sqrt(pow((x - display->xmid), 2) + pow((y - display->ymid), 2));
	if (distance < display->radius)
		return (1);
	return (0);
}

void	freecoor(t_coor **coor)
{
	int	i;

	i = 0;
	while (i < WIDTH * HEIGHT)
	{
		free(coor[i]);
		i++;
	}
	free(coor);
}

int	killwindow(t_params *params)
{
	mlx_destroy_image(params->utils->mlx, params->fractol);
	mlx_destroy_window(params->utils->mlx, params->utils->win);
	exit(1);
	return (0);
}

int	main(int ac, char **av)
{
	t_params	*params;

	if (ac > 1)
	{
		if (ft_strcmp(av[1], "mandlebrot") == 0 \
		|| ft_strcmp(av[1], "julia") == 0)
		{
			params = ft_calloc(1, sizeof (t_params));
			firstinit(params, av[1]);
			if (ft_strcmp(av[1], "julia") == 0)
			{
				params->display->xinc = ft_atof(av[2]);
				params->display->yinc = ft_atof(av[3]);
			}
			mlx_hook(params->utils->win, 2, 1L << 0, keyhandler, params);
			mlx_hook(params->utils->win, 4, 1L << 2, scrollhandler, params);
			mlx_hook(params->utils->win, 17, 1L << 0, killwindow, params);
			mlx_loop_hook(params->utils->mlx, render, params);
			mlx_loop(params->utils->mlx);
			return (0);
		}
	}
	ft_putstr("USAGE: ./fractol [mandlebrot || julia realnum imaginarynum]");
	return (0);
}
