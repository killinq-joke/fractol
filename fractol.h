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

typedef struct	s_mlx {
	void	*mlx;
	void	*win;
	int		winx;
	int		winy;
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
}				t_display;


typedef struct	s_params
{
	t_image		*fractol;
	t_mlx		*utils;
	t_display	*display;
}				t_params;


#endif
