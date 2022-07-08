/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 15:29:50 by jsaarine          #+#    #+#             */
/*   Updated: 2022/07/08 16:37:09 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_colors	my_brot(t_complex sxy, t_complex c, t_context *ctx)
{
	t_fr_dat	d;
	t_colors	colors;

	d.i = 0;
	d.n = 0;
	d.distance = 1e20;
	while (d.i < 64 && d.n < ctx->max_iter)
	{
		d.z = c_mult(d.z, d.z);
		d.z.x = sin(d.z.x);
		d.z = c_add(c_mult(d.z, d.z), c);
		d.z.y = ft_fabs(d.z.y);
		d.i = d.z.x * d.z.x * d.z.y + d.z.y * d.z.y;
		d.z_minus_point = d.z;
		d.point.y = d.z.y * d.z.x;
		d.point.x = 0;
		d.z_minus_point = c_sub(d.z_minus_point, d.point);
		d.zmp_distance = c_abs(d.z_minus_point);
		if (d.zmp_distance < d.distance)
			d.distance = d.zmp_distance;
		d.n++;
	}
	colors.a = d.n;
	colors.b = d.distance;
	return (colors);
}

t_colors	mandelbrot(t_complex sxy, t_complex c, t_context *ctx)
{
	t_fr_dat	d;
	t_colors	colors;

	d.z.x = 0;
	d.z.y = 0;
	d.i = 0;
	d.n = 0;
	d.distance = 1e20;
	while (d.i < 64 && d.n < ctx->max_iter)
	{
		d.z = c_add(c_mult(d.z, d.z), c);
		d.i = d.z.x * d.z.x + d.z.y * d.z.y;
		d.z_minus_point = d.z;
		d.point.y = 0;
		d.point.x = 0;
		d.z_minus_point = c_sub(d.z_minus_point, d.point);
		d.zmp_distance = c_abs(d.z_minus_point);
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
	while (d.i < 64 && d.n < ctx->max_iter)
	{
		d.z.x = ft_fabs(d.z.x);
		d.z.y = ft_fabs(d.z.y);
		d.z = c_add(c_mult(d.z, d.z), c);
		d.i = d.z.x * d.z.x + d.z.y * d.z.y;
		d.z_minus_point = d.z;
		d.point.y = 0;
		d.point.x = 0;
		d.z_minus_point = c_sub(d.z_minus_point, d.point);
		d.zmp_distance = c_abs(d.z_minus_point);
		if (d.zmp_distance < d.distance)
			d.distance = d.zmp_distance;
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
		sxy = c_add(c_mult(sxy, sxy), c);
		d.i = sxy.x * sxy.x + sxy.y * sxy.y;
		d.z_minus_point = sxy;
		d.point.y = 0;
		d.point.x = 0;
		d.z_minus_point = c_sub(d.z_minus_point, d.point);
		d.zmp_distance = c_abs(d.z_minus_point);
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
		d.z_minus_point = c_sub(d.z_minus_point, d.point);
		d.zmp_distance = c_abs(d.z_minus_point);
		if (d.zmp_distance < d.distance)
			d.distance = d.zmp_distance;
		d.n++;
	}
	colors.a = d.n;
	colors.b = d.distance;
	return (colors);
}

t_colors	julia_mess_b(t_complex sxy, t_complex c, t_context *ctx)
{
	t_fr_dat	d;
	t_colors	colors;

	// koita laittaa siihen sun juliaan tää kaava
	// ((((z^8 / c) + z^11) + c) * z) * c
	// tai tää ((z^9 + z) + (z^2 * c)^2) / z
	// tai mandelbrotiin tää  z^3 + c

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
		d.z_minus_point = c_sub(d.z_minus_point, d.point);
		d.zmp_distance = c_abs(d.z_minus_point);
		if (d.zmp_distance < d.distance)
			d.distance = d.zmp_distance;
		d.n++;
	}
	colors.a = d.n;
	colors.b = d.distance;
	return (colors);
}
