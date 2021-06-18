/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 19:47:51 by ztouzri           #+#    #+#             */
/*   Updated: 2021/06/18 19:48:10 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	scrollhandler(int button, int x, int y, t_params *params)
{
	int	hori;
	int	vert;

	hori = (x - WIDTH / 2) / 5;
	vert = (y - HEIGHT / 2) / 5;
	if (button == 4)
	{
		params->display->graduationlen *= params->display->zoom;
		params->display->radius = params->display->graduationlen * 2;
		move_display(params->display, -hori, vert);
		free(params->coor);
		params->coor = init_coor(params->display);
	}
	else if (button == 5)
	{
		params->display->graduationlen /= params->display->zoom;
		params->display->radius = params->display->graduationlen * 2;
		move_display(params->display, hori, -vert);
		free(params->coor);
		params->coor = init_coor(params->display);
	}
	return (1);
}

void	arrowhandler(int key, t_params *params)
{
	int	hori;
	int	vert;

	hori = 0;
	vert = 0;
	if (key == RIGHT_ARROW)
		hori = 50;
	else if (key == LEFT_ARROW)
		hori = -50;
	else if (key == UP_ARROW)
		vert = -50;
	else
		vert = 50;
	move_display(params->display, hori, vert);
	params->coor = init_coor(params->display);
}

int	keyhandler(int key, t_params *params)
{
	if (key == RIGHT_ARROW || key == LEFT_ARROW \
	|| key == UP_ARROW || key == DOWN_ARROW)
		arrowhandler(key, params);
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
