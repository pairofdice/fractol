/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 12:05:55 by jsaarine          #+#    #+#             */
/*   Updated: 2022/05/09 16:20:21 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	set_points(t_point *p, t_deltas *deltas, t_line *line)
{
	*p = line->a;
	line->a.x = (int)line->a.x;
	line->a.y = (int)line->a.y;
	line->b.x = (int)line->b.x;
	line->b.y = (int)line->b.y;
	deltas->x = line->b.x - line->a.x;
	deltas->y = line->b.y - line->a.y;
}

static void	delta_divide(t_deltas *deltas, int steps)
{
	deltas->x /= steps;
	deltas->y /= steps;
/* 	deltas->r /= steps;
	deltas->g /= steps;
	deltas->b /= steps; */
}

static void	delta_increment(t_point *p, /* t_point *color, */ t_deltas *deltas)
{
	p->x += deltas->x;
	p->y += deltas->y;
/* 	color->x += deltas->r;
	color->y += deltas->g;
	color->z += deltas->b; */
}
int	rgb_to_int(t_point c)
{
	return ((int)c.x << 16 | (int)c.y << 8 | (int)c.z);
}

int	ft_abs(int a)
{
	if (a < 0)
		return (-a);
	return (a);
}


void	draw_line(t_line *line, t_context *ctx)
{
	t_deltas	deltas;
	t_point		p;
	int			steps;
	t_point		color;

	set_points(&p, &deltas, line);
	//set_color(&color, &deltas, line, ctx);
	if (ft_abs(deltas.x) >= ft_abs(deltas.y))
		steps = ft_abs(deltas.x);
	else
		steps = ft_abs(deltas.y);
	delta_divide(&deltas, steps);
	color.x = 255;
	color.y = 255;
	color.z = 255;
	/* if (!neither_point_in_window(line, ctx)) 
	{*/
		while (steps >= 0)
		{
			/* if (points_in_window(line, ctx))
				img_pixel_put(&ctx->fb, p.x, p.y, rgb_to_int(color));
			else */
			img_pixel_put(&ctx->fb, p.x, p.y, rgb_to_int(color));
			delta_increment(&p, /* &color, */ &deltas);
			steps--;
		}
	/* } */
}
