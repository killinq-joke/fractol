/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 18:55:39 by ztouzri           #+#    #+#             */
/*   Updated: 2021/06/18 20:05:00 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_coor	**init_coor(t_display *display)
{
	t_coor	**coor;

	coor = ft_calloc(WIDTH * HEIGHT, sizeof (t_coor *));
	createcoor(coor, display);
	return (coor);
}

t_display	*init_display(t_mlx *utils)
{
	t_display	*display;
	int			xmid;
	int			ymid;
	int			graduationlen;
	int			radius;

	display = ft_calloc(1, sizeof (t_display));
	xmid = utils->winx / 2;
	ymid = utils->winy / 2;
	display->xmid = xmid;
	display->ymid = ymid;
	graduationlen = 100;
	radius = graduationlen;
	display->graduationlen = graduationlen;
	display->radius = graduationlen * 2;
	display->xleftbound = xmid - radius;
	display->xrightbound = xmid + radius;
	display->yupbound = ymid + radius;
	display->ydownbound = ymid - radius;
	display->zoom = 1.1;
	return (display);
}

t_mlx	*init_utils(void)
{
	t_mlx	*utils;

	utils = ft_calloc(1, sizeof (t_mlx));
	utils->mlx = mlx_init();
	utils->win = mlx_new_window(utils->mlx, WIDTH, HEIGHT, "fractol");
	utils->winx = WIDTH;
	utils->winy = HEIGHT;
	return (utils);
}

t_image	*init_image(t_mlx *utils)
{
	t_image	*fractol;

	fractol = ft_calloc(1, sizeof (t_image));
	fractol->img = mlx_new_image(utils->mlx, utils->winx, utils->winy);
	fractol->data = mlx_get_data_addr(fractol->img, \
	&fractol->bpp, &fractol->size_line, &fractol->endian);
	return (fractol);
}

void	firstinit(t_params *params, char *name)
{
	params->utils = init_utils();
	params->utils->name = name;
	params->fractol = init_image(params->utils);
	params->display = init_display(params->utils);
	params->coor = init_coor(params->display);
}
