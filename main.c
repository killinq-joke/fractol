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

	if (x < 0 || y < 0 || y > HEIGHT || x > WIDTH)
		return ;
	dst = img->data +\
	(img->size_line * HEIGHT - (y + 1) * img->size_line + x * (img->bpp / 8));
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

int		isincircle(int x, int y, t_display *display)
{
	double	distance;

	distance = sqrt(pow((x - display->xmid), 2) + pow((y - display->ymid), 2));
	if (distance < display->radius)
		return (1);
	return (0);
}

void	print_circle(t_image *img, t_display *display)
{
	int		x;
	int		y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (isincircle(x, y, display))
				ft_putpixel(img, x, y, 0x00FF0000);
			x++;
		}
		y++;
	}
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

t_coor	**zoom_coor(t_coor **coor, t_display *display)
{
	t_coor	**newcoor;
	int		x;
	int		xmax;
	int		y;
	int		ymax;
	int		i;
	int		j;
	int		o;

	// printf("x == %d && xmax == %d\n", x, xmax);
	// printf("y == %d && ymax == %d\n", y, ymax);
	y = (1 - 1 / display->zoom) / 2 * HEIGHT;
	ymax = HEIGHT - y;
	xmax = WIDTH - (1 - 1 / display->zoom) / 2 * WIDTH;
	newcoor = ft_calloc(WIDTH * HEIGHT, sizeof (t_coor *));
	i = 0;
	while (y < ymax)
	{
		x = (1 - 1 / display->zoom) / 2 * WIDTH;
		while (x < xmax)
		{
			j = 0;
			while (j < display->zoom)
			{
				o = 0;
				while (o < display->zoom)
				{
					newcoor[i + o + j * WIDTH]  = coor[WIDTH * y + x];
					o++;
				}
				j++;
			}
			i++;
			x++;
		}
		i += WIDTH;
		y++;
	}
	freecoor(coor);
	return (newcoor);
}

t_coor	**init_coor(t_display *display)
{
	t_coor	**coor;
	int		y;
	int		x;
	int		i;

	coor = ft_calloc(WIDTH * HEIGHT, sizeof (t_coor *));
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
			coor[i]->x = ((double)x - (double)display->xmid) / display->graduationlen;
			coor[i]->y = ((double)y - (double)display->ymid) / display->graduationlen;
			// printf("%f, %d, %d\n", (double)y - (double)display->ymid, y, display->ymid);
			coor[i]->color = 0x00FFFFFF;
			i++;
			x++;
		}
		y++;
	}
	return (coor);
}


int		mandlebrot(t_image *img, t_display *display, t_coor **coor)
{
	double	xx;
	double	yy;
	int		i;

	i = 0;
	while (i < WIDTH * HEIGHT - 1)
	{
		xx = coor[i]->x * coor[i]->x - coor[i]->y * coor[i]->y;
		yy = 2.0 * coor[i]->x * coor[i]->y;
		coor[i]->x = xx + (coor[i]->xdefault - (double)display->xmid) / display->graduationlen;
		coor[i]->y = yy + (coor[i]->ydefault - (double)display->ymid) / display->graduationlen;
		if (isincircle(coor[i]->x * display->graduationlen + display->xmid, coor[i]->y * display->graduationlen + display->ymid, display))
		{
			coor[i]->color = 0x00000000;
			ft_putpixel(img, coor[i]->xdefault, coor[i]->ydefault, coor[i]->color);
		}
		else
		{
			coor[i]->color += 1000000;
			ft_putpixel(img, coor[i]->xdefault, coor[i]->ydefault, coor[i]->color);
			if (coor[i]->color >= 0xFFFFFFF)
				coor[i]->color = 100;
		}
		i++;
	}
	return (1);
}

int		julia(t_image *img, t_display *display, t_coor **coor)
{
	double	xx;
	double	yy;
	int		i;

	i = 0;
	while (i < WIDTH * HEIGHT - 1)
	{
		xx = coor[i]->x * coor[i]->x - coor[i]->y * coor[i]->y;
		yy = 2.0 * coor[i]->x * coor[i]->y;
		coor[i]->x = xx + display->xinc;
		coor[i]->y = yy + display->yinc;
		if (isincircle(coor[i]->x * display->graduationlen + display->xmid, coor[i]->y * display->graduationlen + display->ymid, display))
		{
			coor[i]->color = 0x00FFFFFF;
			ft_putpixel(img, coor[i]->xdefault, coor[i]->ydefault, coor[i]->color);
		}
		else
		{
			if (coor[i]->color == 0x00FFFFFF)
				coor[i]->color = 0x00FF0000;
			else if (coor[i]->color >= 0x00F00000)
				coor[i]->color -= (0x00FFFFFF - 0x00F00000) / 10;
			else
				coor[i]->color = 0x00000000;
			ft_putpixel(img, coor[i]->xdefault, coor[i]->ydefault, coor[i]->color);
		}
		i++;
	}
	return (1);
}

int		render(t_params *params)
{
	if (ft_strcmp(params->utils->name, "mandlebrot") == 0)
		mandlebrot(params->fractol, params->display, params->coor);
	else if (ft_strcmp(params->utils->name, "julia") == 0)
		julia(params->fractol, params->display, params->coor);
	mlx_put_image_to_window(params->utils->mlx, params->utils->win, params->fractol->img, 0, 0);
	return (1);
}

int		scrollhandler(int button, int x, int y, t_params *params)
{
	if (button == 4)
	{
		params->display->graduationlen *= params->display->zoom;
		params->display->radius = params->display->graduationlen * 2;
		move_display(params->display, -(x - WIDTH / 2) / 5, (y - HEIGHT / 2) / 5);
		free(params->coor);
		params->coor = init_coor(params->display);
		render(params);
	}
	else if (button == 5)
	{
		params->display->graduationlen /= params->display->zoom;
		params->display->radius = params->display->graduationlen * 2;
		move_display(params->display, (x - WIDTH / 2) / 5, -(y - HEIGHT / 2) / 5);
		free(params->coor);
		params->coor = init_coor(params->display);
		render(params);
	}
	return (1);
}

int		keyhandler(int key, t_params *params)
{
	int hori;
	int vert;

	hori = 0;
	vert = 0;
	if (key == RIGHT_ARROW || key == LEFT_ARROW || key == UP_ARROW || key == DOWN_ARROW)
	{
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
		render(params);
	}
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
	fractol->data = mlx_get_data_addr(fractol->img, &fractol->bpp, &fractol->size_line, &fractol->endian);
	return (fractol);
}

int		killwindow(t_params *params)
{
	mlx_destroy_image(params->utils->mlx, params->fractol);
	mlx_destroy_window(params->utils->mlx, params->utils->win);
	exit(1);
	return (0);
}

void	firstinit(t_params *params, char *name)
{
	params->utils = init_utils();
	params->utils->name = name;
	params->fractol = init_image(params->utils);
	params->display = init_display(params->utils);
	params->coor = init_coor(params->display);
}

int	main(int ac, char **av)
{
	t_params	*params;

	if (ac > 1)
	{
		if (ft_strcmp(av[1], "mandlebrot") == 0 || ft_strcmp(av[1], "julia") == 0)
		{
			params = ft_calloc(1, sizeof (t_params));
			firstinit(params, av[1]);
			if (ft_strcmp(av[1], "julia") == 0)
			{
				params->display->xinc = ft_atof(av[2]);
				params->display->yinc = ft_atof(av[3]);
			}
			mlx_hook(params->utils->win, 2, 1L<<0, keyhandler, params);
			mlx_hook(params->utils->win, 4, 1L<<2, scrollhandler, params);
			mlx_hook(params->utils->win, 17, 1L<<0, killwindow, params);
			mlx_loop_hook(params->utils->mlx, render, params);
			mlx_loop(params->utils->mlx);
		}
	}
	return (0);
}
