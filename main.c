/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 21:04:30 by ztouzri           #+#    #+#             */
/*   Updated: 2021/06/13 21:56:25 by ztouzri          ###   ########.fr       */
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

void	print_grid(t_image *fractol, t_mlx *utils, t_display *display)
{
	int	i;
	int	j;

	i = 0;
	while (i++ < utils->winx)
	{
		ft_putpixel(fractol, i, display->ymid, 0x00FFFFFF);
		j = -5;
		if ((i - display->xmid) % display->graduationlen == 0)
		{
			while (j++ < 5)
				ft_putpixel(fractol, i, display->ymid + j, 0x00FF0000);
		}
	}
	i = 0;
	while (i++ < utils->winy)
	{
		ft_putpixel(fractol, display->xmid, i, 0x00FFFFFF);
		if ((i - display->ymid) % display->graduationlen == 0)
		{
			j = -5;
			while (j++ < 5)
				ft_putpixel(fractol, display->xmid + j, i, 0x00FF0000);
		}
	}
}

void	print_circle(t_image *img, t_display *display)
{
	int	x;
	int	y;

	y = display->yupbound;
	while (y < display->ydownbound)
	{
		x = display->xleftbound;
		while (x < display->xrightbound)
		{
			ft_putpixel(img, x, y, 0x00FF0000);
			x++;
		}
		y++;
	}
}

//next step:
//find a way to print a circle
//then a way to iterate on each point of the circle and change color if the point goes south. maybe store every point in an array
int		render(t_params *params)
{
	print_grid(params->fractol, params->utils, params->display);
	// printf("xleft = %d, xright = %d\n", params->display->xleftbound, params->display->xrightbound);
	// for(int i = 0; i < 100; i++)
	// 	ft_putpixel(params->fractol, params->display->xleftbound, params->display->ymid + i, 0x000000FF);
	// for(int i = 0; i < 100; i++)
	// 	ft_putpixel(params->fractol, params->display->xrightbound, params->display->ymid + i, 0x000000FF);
	// for(int i = 0; i < 100; i++)
	// 	ft_putpixel(params->fractol, params->display->xmid + i, params->display->yupbound, 0x000000FF);
	// for(int i = 0; i < 100; i++)
	// 	ft_putpixel(params->fractol, params->display->xmid + i, params->display->ydownbound, 0x000000FF);
	// print_circle(params->fractol, params->display);
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

t_display	*init_display(t_display *display, t_mlx *utils)
{
	int	xmid;
	int	ymid;
	int	graduationlen;

	xmid = utils->winx / 2;
	ymid = utils->winy / 2;
	graduationlen = 200;
	display->xmid = xmid;
	display->ymid = ymid;
	display->graduationlen = graduationlen;
	display->xleftbound = xmid - graduationlen * 2;
	display->xrightbound = xmid + graduationlen * 2;
	display->yupbound = ymid - graduationlen * 2;
	display->ydownbound = ymid + graduationlen * 2;
	return (display);
}

int main(void)
{
	t_mlx		*utils;
	t_image		*fractol;
	t_display	*display;
	t_params	*params;

	utils = ft_calloc(1, sizeof (t_mlx));
	fractol = ft_calloc(1, sizeof (t_image));
	display = ft_calloc(1, sizeof (t_display));
	params = ft_calloc(1, sizeof (t_params));
	params->utils = utils;
	params->fractol = fractol;
	params->display = display;
	utils->mlx = mlx_init();
	utils->win = mlx_new_window(utils->mlx, 1920, 1080, "fractol");
	utils->winx = 1920;
	utils->winy = 1080;
	fractol->img = mlx_new_image(utils->mlx, utils->winx, utils->winy);
	fractol->data = mlx_get_data_addr(fractol->img, &fractol->bpp, &fractol->size_line, &fractol->endian);
	init_display(display, utils);
	mlx_hook(utils->win, 4, 1L<<2, scrollhandler, NULL);
	mlx_hook(utils->win, 2, 1L<<0, keyhandler, params);
	mlx_loop_hook(utils->mlx, render, params);
	mlx_loop(utils->mlx);
	return (0);
}
