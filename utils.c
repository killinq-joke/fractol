/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 19:54:56 by ztouzri           #+#    #+#             */
/*   Updated: 2021/06/19 13:53:00 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	createcoor(t_coor **coor, t_display *display)
{
	int	i;
	int	y;
	int	x;

	i = 0;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			coor[i] = ft_calloc(1, sizeof (t_coor));
			coor[i]->xdefault = x;
			coor[i]->ydefault = y;
			coor[i]->x = ((double)x - \
			(double)display->xmid) / display->graduationlen;
			coor[i]->y = ((double)y - \
			(double)display->ymid) / display->graduationlen;
			coor[i]->color = 0x00FFFFFF;
			i++;
			x++;
		}
		y++;
	}
}

void	freer(t_params *params)
{
	int	i;

	i = WIDTH * HEIGHT - 1;
	while (i >= 0)
	{
		free(params->coor[i]);
		i--;
	}
	free(params->coor);
	free(params->display);
	free(params->fractol);
	mlx_destroy_window(params->utils->mlx, params->utils->win);
	free(params->utils);
	free(params);
}

int	ft_isfloat(char *str)
{
	int	i;

	if (ft_countchar(str, '.') > 1 && ft_countchar(str, '-'))
		return (0);
	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != '.' && str[i] != '-')
			return (0);
		i++;
	}
	return (1);
}
