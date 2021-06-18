/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 18:58:52 by ztouzri           #+#    #+#             */
/*   Updated: 2021/06/18 19:45:14 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_display	*move_display(t_display *display, int hori, int vert)
{
	static int	xmid = WIDTH / 2;
	static int	ymid = HEIGHT / 2;

	xmid += hori;
	ymid += vert;
	display->xmid = xmid;
	display->ymid = ymid;
	display->xleftbound = xmid - display->radius;
	display->xrightbound = xmid + display->radius;
	display->yupbound = ymid + display->radius;
	display->ydownbound = ymid - display->radius;
	return (display);
}

void	mandlebrotloop(int i, t_display *display, t_coor **coor)
{
	double	xx;
	double	yy;

	xx = coor[i]->x * coor[i]->x - coor[i]->y * coor[i]->y;
	yy = 2.0 * coor[i]->x * coor[i]->y;
	coor[i]->x = xx + (coor[i]->xdefault - \
	(double)display->xmid) / display->graduationlen;
	coor[i]->y = yy + (coor[i]->ydefault - \
	(double)display->ymid) / display->graduationlen;
}

int	mandlebrot(t_image *img, t_display *display, t_coor **coor)
{
	int		i;

	i = 0;
	while (i < WIDTH * HEIGHT - 1)
	{
		mandlebrotloop(i, display, coor);
		if (isincircle(coor[i]->x * display->graduationlen + display->xmid, \
		coor[i]->y * display->graduationlen + display->ymid, display))
		{
			coor[i]->color = 0x00000000;
			ft_putpixel(img, coor[i]->xdefault, \
			coor[i]->ydefault, coor[i]->color);
		}
		else
		{
			coor[i]->color += 1000000;
			ft_putpixel(img, coor[i]->xdefault, \
			coor[i]->ydefault, coor[i]->color);
			if (coor[i]->color >= 0xFFFFFFF)
				coor[i]->color = 100;
		}
		i++;
	}
	return (1);
}

void	julialoop(int i, t_image *img, t_display *display, t_coor **coor)
{
	double	xx;
	double	yy;

	xx = coor[i]->x * coor[i]->x - coor[i]->y * coor[i]->y;
	yy = 2.0 * coor[i]->x * coor[i]->y;
	coor[i]->x = xx + display->xinc;
	coor[i]->y = yy + display->yinc;
	if (isincircle(coor[i]->x * display->graduationlen + display->xmid, \
	coor[i]->y * display->graduationlen + display->ymid, display))
	{
		coor[i]->color = 0x00FFFFFF;
		ft_putpixel(img, coor[i]->xdefault, \
		coor[i]->ydefault, coor[i]->color);
	}
	else
	{
		if (coor[i]->color == 0x00FFFFFF)
			coor[i]->color = 0x00FF0000;
		else if (coor[i]->color >= 0x00F00000)
			coor[i]->color -= (0x00FFFFFF - 0x00F00000) / 10;
		else
			coor[i]->color = 0x00000000;
		ft_putpixel(img, coor[i]->xdefault, \
		coor[i]->ydefault, coor[i]->color);
	}
}

int	julia(t_image *img, t_display *display, t_coor **coor)
{
	int		i;

	i = 0;
	while (i < WIDTH * HEIGHT - 1)
	{
		julialoop(i, img, display, coor);
		i++;
	}
	return (1);
}
