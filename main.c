/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 21:04:30 by ztouzri           #+#    #+#             */
/*   Updated: 2021/06/13 17:09:16 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/**
**
**	f c (z) = z ^ 2 + c
**	c++
**	f c (z) = z ^ 2 + c
**
**/

void	ft_putpixel(int x, int y, char *data)
{
	int	*tab;

	tab = (int *)data;
	int i = 0;
	while (i < x)
	{
		tab[y * x + x + i++] = 0x00FF0000;
	}
}

int		render(t_image *fractol)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	ft_putpixel(x, y, fractol->img);
	return (1);
}

/*
** button 4 == scroll down
** button 5 == scroll up
*/

int		scrollhandler(int button, void *a)
{
	a = NULL;
	if (button == 4)
	{

	}
	else if (button == 5)
	{

	}
	return (1);
}

int		keyhandler(int key, t_params *params)
{
	printf("%d\n", key);
	if (key == 53)
	{
		mlx_destroy_image(params->utils->mlx, params->fractol->img);
		mlx_destroy_window(params->utils->mlx, params->utils->win);
		free(params->utils);
		free(params->fractol);
		free(params);
		exit(1);
	}
	return (1);
}

int main(void)
{
	t_mlx		*utils;
	t_image		*fractol;
	t_params	*params;

	utils = ft_calloc(1, sizeof (t_mlx));
	fractol = ft_calloc(1, sizeof (t_image));
	params = ft_calloc(1, sizeof (t_params));
	params->utils = utils;
	params->fractol = fractol;
	utils->mlx = mlx_init();
	utils->win = mlx_new_window(utils->mlx, 1920, 1080, "fractol");
	fractol->img = mlx_new_image(utils->mlx, 1920, 1080);
	fractol->data = mlx_get_data_addr (fractol->img, &fractol->bpp, &fractol->size_line, &fractol->endian);
	// mlx_loop_hook(utils->mlx, &render, );
	mlx_hook(utils->win, 4, 1L<<2, &scrollhandler, NULL);
	mlx_hook(utils->win, 2, 1L<<0, &keyhandler, params);
	mlx_loop(utils->mlx);

	return (0);
}
