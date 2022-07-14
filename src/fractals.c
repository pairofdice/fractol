/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 15:29:50 by jsaarine          #+#    #+#             */
/*   Updated: 2022/07/14 13:04:20 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_colors	mandelbrot(t_complex sxy, t_complex c, t_context *ctx)
{
	t_fr_dat	d;
	t_colors	colors;

	d.z.x = 0;
	d.z.y = 0;
	d.i = 0;
	d.n = 0;
	(void)sxy;
	d.distance = 1e20;
	while (d.i < 64 && d.n < ctx->max_iter)
	{
		d.z = c_add(c_mult(d.z, d.z), c);
		d.i = d.z.x * d.z.x + d.z.y * d.z.y;
		d.z_minus_point = d.z;
		d.point.y = 0;
		d.point.x = 0;
		d.zmp_distance = c_abs(c_sub(d.z_minus_point, d.point));
		if (d.zmp_distance < d.distance)
			d.distance = d.zmp_distance;
		d.n++;
	}
	colors.a = d.n;
	colors.b = d.distance;
	return (colors);
}

t_colors	burning_ship(t_complex sxy, t_complex c, t_context *ctx)
{
	t_fr_dat	d;
	t_colors	colors;

	d.z.x = 0;
	d.z.y = 0;
	d.i = 0;
	d.n = 0;
	d.distance = 1e20;
	(void)sxy;
	while (d.i < 64 && d.n < ctx->max_iter)
	{
		d.z.x = ft_fabs(d.z.x);
		d.z.y = ft_fabs(d.z.y);
		d.z = c_add(c_mult(d.z, d.z), c);
		d.i = d.z.x * d.z.x + d.z.y * d.z.y;
		d.z_minus_point = d.z;
		d.point.y = 0;
		d.point.x = 0;
		if (c_abs(c_sub(d.z_minus_point, d.point)) < d.distance)
			d.distance = c_abs(c_sub(d.z_minus_point, d.point));
		d.n++;
	}
	colors.a = d.n;
	colors.b = d.distance;
	return (colors);
}

t_colors	julia(t_complex sxy, t_complex c, t_context *ctx)
{
	t_fr_dat	d;
	t_colors	colors;

	d.i = 0;
	d.n = 0;
	d.distance = 1e20;
	while (d.i < 64 && d.n < ctx->max_iter)
	{
		sxy = c_add(c_pow(sxy, 2), c);
		d.i = sxy.x * sxy.x + sxy.y * sxy.y;
		d.z_minus_point = sxy;
		d.point.y = 0;
		d.point.x = 0;
		d.zmp_distance = c_abs(c_sub(d.z_minus_point, d.point));
		if (d.zmp_distance < d.distance)
			d.distance = d.zmp_distance;
		d.n++;
	}
	colors.a = d.n;
	colors.b = d.distance;
	return (colors);
}

t_colors	julia_mess(t_complex sxy, t_complex c, t_context *ctx)
{
	t_fr_dat	d;
	t_colors	colors;

	d.i = 0;
	d.n = 0;
	d.distance = 1e20;
	while (d.i < 64 && d.n < ctx->max_iter)
	{
		sxy = c_mult(sxy, sxy);
		sxy = c_add(c_mult(sxy, sxy), c);
		d.i = sxy.x * sxy.x + sxy.y * sxy.y;
		d.z_minus_point = sxy;
		d.point.y = 0;
		d.point.x = 0;
		d.zmp_distance = c_abs(c_sub(d.z_minus_point, d.point));
		if (d.zmp_distance < d.distance)
			d.distance = d.zmp_distance;
		d.n++;
	}
	colors.a = d.n;
	colors.b = d.distance;
	return (colors);
}
