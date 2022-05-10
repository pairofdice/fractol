/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:15:52 by jsaarine          #+#    #+#             */
/*   Updated: 2022/05/10 15:26:27 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdio.h>
# include "mlx.h"
# include <math.h>

enum {
	WIN_W = 1536,
	WIN_H = 1024,
	MAX_ITER = 0,
	
};

typedef struct s_complex
{
	double x;
	double y;
}	t_complex;

typedef struct s_point
{
	double	x;
	double	y;
	double	z;
	double	c;
}	t_point;

typedef struct s_deltas
{
	double	x;
	double	y;
	double	z;
	double	r;
	double	g;
	double	b;
}	t_deltas;

typedef struct s_line
{
	t_point	a;
	t_point	b;
}	t_line;

typedef struct s_frame_buffer
{
	void	*img;
	char	*data;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		height;

}	t_frame_buffer;

typedef struct s_context
{
	void			*mlx;
	void			*win;
	t_frame_buffer	fb;
	int				w;
	int				h;
	int				mouse_x;
	int				mouse_y;
	int				right_mouse_dn;
	int				left_mouse_dn;
	int				frame_n;
}	t_context;

void	init_context(t_context *ctx);
void	draw_line(t_line *line, t_context *ctx);
int	neither_point_in_window(t_line *l, t_context *ctx);
int	points_in_window(t_line *l, t_context *ctx);

void	img_pixel_put(t_frame_buffer *fb, int x, int y, int color);
void	checked_pixel_put(t_frame_buffer *fb, int x, int y, int color);

t_complex	c_add(t_complex a, t_complex b);
t_complex	c_sub(t_complex a, t_complex b);
t_complex	c_abs(t_complex a);
t_complex	c_mult(t_complex a, t_complex b);

int	rgb_to_int(t_point c);
int	mandelbrot(t_complex c);

#endif
