/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 19:54:56 by ztouzri           #+#    #+#             */
/*   Updated: 2021/06/18 20:05:05 by ztouzri          ###   ########.fr       */
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
