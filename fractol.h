/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 21:11:30 by ztouzri           #+#    #+#             */
/*   Updated: 2021/06/12 21:17:12 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft.h"
# include "math.h"
# include "mlx.h"
# include <stdio.h>

# define WIDTH 640
# define HEIGHT 480
# define RIGHT_ARROW 124
# define LEFT_ARROW 123
# define UP_ARROW 126
# define DOWN_ARROW 125
typedef struct	s_mlx {
	void	*mlx;
	void	*win;
	int		winx;
	int		winy;
	char	*name;
}				t_mlx;

typedef struct	s_image {
	int		bpp;
	int		size_line;
	int		endian;
	void	*img;
	char	*data;
}				t_image;

typedef struct	s_display
{
	int	xleftbound;
	int	xmid;
	int	xrightbound;
	int	yupbound;
	int	ymid;
	int	ydownbound;
	int	graduationlen;
	int	radius;
	double	xinc;
	double	yinc;
	double	zoom;
}				t_display;

typedef struct	s_coor
{
	int16_t	xdefault;
	int16_t	ydefault;
	double	x;
	double	y;
	int		color;
}				t_coor;

typedef struct	s_complex
{
	double	real;
	double	imaginary;
}				t_complex;

typedef struct	s_color
{
	char	transparency;
	char	red;
	char	green;
	char	blue;
}				t_color;


typedef struct	s_params
{
	t_image		*fractol;
	t_mlx		*utils;
	t_coor		**coor;
	t_display	*display;
}				t_params;

t_image		*init_image(t_mlx *utils);
t_display	*move_display(t_display *display, int hori, int vert);

#endif
