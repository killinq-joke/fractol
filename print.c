/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 19:48:30 by ztouzri           #+#    #+#             */
/*   Updated: 2021/06/18 19:49:04 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	ft_putpixel(t_image *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || y > HEIGHT || x > WIDTH)
		return ;
	dst = img->data + \
	(img->size_line * HEIGHT - (y + 1) * img->size_line + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

int	render(t_params *params)
{
	if (ft_strcmp(params->utils->name, "mandlebrot") == 0)
		mandlebrot(params->fractol, params->display, params->coor);
	else if (ft_strcmp(params->utils->name, "julia") == 0)
		julia(params->fractol, params->display, params->coor);
	mlx_put_image_to_window(params->utils->mlx, \
	params->utils->win, params->fractol->img, 0, 0);
	return (1);
}
