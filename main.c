/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 21:04:30 by ztouzri           #+#    #+#             */
/*   Updated: 2021/06/13 21:00:11 by ztouzri          ###   ########.fr       */
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

void	ft_putpixel(t_image *img, int x, int y, int color)
{
	char	*dst;

	dst = img->data + (y * img->size_line + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
}

void	print_grid(t_image *fractol, t_mlx *utils)
{
	int	x;
	int	y;
	int	i;
	int	j;

	i = 0;
	x = utils->winx / 2;
	y = utils->winy / 2;

	while (i++ < utils->winx)
	{
		ft_putpixel(fractol, i, y, 0x00FFFFFF);
		j = -5;
		if ((i - x) % 200 == 0)
		{
			while (j++ < 5)
				ft_putpixel(fractol, i, y + j, 0x00FF0000);
		}
	}
	i = 0;
	while (i++ < utils->winy)
	{
		ft_putpixel(fractol, x, i, 0x00FFFFFF);
		if ((i - y) % 200 == 0)
		{
			j = -5;
			while (j++ < 5)
				ft_putpixel(fractol, x + j, i, 0x00FF0000);
		}
	}
}

int		render(t_params *params)
{
	print_grid(params->fractol, params->utils);
	mlx_put_image_to_window(params->utils->mlx, params->utils->win, params->fractol->img, 0, 0);
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
	utils->winx = 1920;
	utils->winy = 1080;
	fractol->img = mlx_new_image(utils->mlx, utils->winx, utils->winy);
	fractol->data = mlx_get_data_addr(fractol->img, &fractol->bpp, &fractol->size_line, &fractol->endian);
	mlx_hook(utils->win, 4, 1L<<2, scrollhandler, NULL);
	mlx_hook(utils->win, 2, 1L<<0, keyhandler, params);
	mlx_loop_hook(utils->mlx, render, params);
	mlx_loop(utils->mlx);
	return (0);
}
