/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 15:29:50 by jsaarine          #+#    #+#             */
/*   Updated: 2022/07/07 15:13:22 by jsaarine         ###   ########.fr       */
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

t_colors	my_brot_backup(t_complex sxy, t_complex c, t_context *ctx)
{
	t_complex	z;
	t_complex	zMinusPoint;
	t_complex	point;
	int	n;
	int i;
	double distance;
	double zMinusPointDistance;
	t_colors colors;

	z.x = 0;
	z.y	= 0;

	i = 0;
	n = 0;
	distance = 1e20;

	while (i < 64 && n < ctx->max_iter)
	{


		z = c_mult(z, z);
		z.x = sin(z.x);
		z = c_add(c_mult(z, z), c);
		z.y = ft_fabs(z.y);
		i = z.x * z.x * z.y + z.y * z.y;

 		zMinusPoint = z;
		point.y = z.y * z.x;
		point.x = 0;
		 zMinusPoint = c_sub(zMinusPoint, point);
		zMinusPointDistance = c_abs(zMinusPoint);
		if (zMinusPointDistance < distance)
			distance = zMinusPointDistance;
		n++;
	}
	colors.a = n;
	colors.b = distance;
	return (colors);
}


t_colors	mandelbrot(t_complex sxy, t_complex c, t_context *ctx)
{
	t_fr_dat	d;
	t_colors	colors;

	d.i = 0;
	d.n = 0;
	d.distance = 1e20;
	while (d.i < 64 && d.n < ctx->max_iter)
	{
		d.z = c_add(c_mult(d.z, d.z), c);
		d.i = d.z.x * d.z.x + d.z.y * d.z.y;
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

t_colors	mandelbrot_backup(t_complex sxy, t_complex c, t_context *ctx)
{
	t_complex	z;
	t_complex	zMinusPoint;
	t_complex	point;
	int	n;
	int i;
	double distance;
	double zMinusPointDistance;
	t_colors colors;

	z.x = 0;
	z.y	= 0;

	i = 0;
	n = 0;
	distance = 1e20;

	while (i < 64 && n < ctx->max_iter)
	{
		z = c_add(c_mult(z, z), c);
		i = z.x * z.x + z.y * z.y;

 		zMinusPoint = z;
		point.y = z.y * z.x;
		point.x = 0;
		 zMinusPoint = c_sub(zMinusPoint, point);
		zMinusPointDistance = c_abs(zMinusPoint);
		if (zMinusPointDistance < distance)
			distance = zMinusPointDistance;
		n++;
	}
	colors.a = n;
	colors.b = distance;
	return (colors);
}

t_colors	burning_ship(t_complex sxy, t_complex c, t_context *ctx)
{
	t_complex	z;
	t_complex	zMinusPoint;
	t_complex	point;
	int	n;
	int i;
	double distance;
	double zMinusPointDistance;
	t_colors colors;

	z.x = 0;
	z.y	= 0;

	i = 0;
	n = 0;
	distance = 1e20;

	while (i < 64 && n < ctx->max_iter)
	{
		z.x = ft_fabs(z.x);
		z.y = ft_fabs(z.y);
		z = c_add(c_mult(z, z), c);
		i = z.x * z.x + z.y * z.y;

 		zMinusPoint = z;
		point.y = z.y * z.x;
		point.x = 0;
		 zMinusPoint = c_sub(zMinusPoint, point);
		zMinusPointDistance = c_abs(zMinusPoint);
		if (zMinusPointDistance < distance)
			distance = zMinusPointDistance;
		n++;
	}
	colors.a = n;
	colors.b = distance;
	return (colors);
}


t_colors	julia(t_complex sxy, t_complex c, t_context *ctx)
{
	//t_complex	z;
	//t_complex	c;
	t_complex	zMinusPoint;
	t_complex	point;
	int	n;
	int i;
	double distance;
	double zMinusPointDistance;
	t_colors colors;

	//z.x = 0;
	//z.y	= 0;
/* 	c.x = 0.355;
	c.y	= 0.355; */



	// koita laittaa siihen sun juliaan tää kaava
	// ((((z^8 / c) + z^11) + c) * z) * c
	// tai tää ((z^9 + z) + (z^2 * c)^2) / z
	// tai mandelbrotiin tää  z^3 + c

	i = 0;
	n = 0;
	distance = 1e20;
	while (i < 64 && n < ctx->max_iter)
	{
		//ft_putstr("HEI");
		// sxy =		c_mult(sxy, sxy);
//		c_mult(sxy, sxy);
		sxy = c_add(c_mult(sxy, sxy), c);
		i = sxy.x * sxy.x + sxy.y * sxy.y;

		zMinusPoint = sxy;
		point.y = 0;
		point.x = 0;
		 zMinusPoint = c_sub(zMinusPoint, point);
		zMinusPointDistance = c_abs(zMinusPoint);// zMinusPoint.magnitude();
		if (zMinusPointDistance < distance)
			distance = zMinusPointDistance;
		n++;
	}
	colors.a = n;
	colors.b = distance;
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

t_colors	fractal_base(t_complex sxy, t_complex c, t_context *ctx)
{
	//t_complex	z;
	//t_complex	c;
	t_complex	zMinusPoint;
	t_complex	point;
	int	n;
	int i;
	double distance;
	double zMinusPointDistance;
	t_colors colors;

	//z.x = 0;
	//z.y	= 0;
/* 	c.x = 0.355;
	c.y	= 0.355; */


	i = 0;
	n = 0;
	distance = 1e20;

	// koita laittaa siihen sun juliaan tää kaava
	// ((((z^8 / c) + z^11) + c) * z) * c
	// tai tää ((z^9 + z) + (z^2 * c)^2) / z
	// tai mandelbrotiin tää  z^3 + c

	while (i < 64 && n < ctx->max_iter)
	{
		//ft_putstr("HEI");
		c_mult(sxy, sxy);
		c_mult(sxy, sxy);
		sxy = c_add(c_mult(sxy, sxy), c);
		i = sxy.x * sxy.x + sxy.y * sxy.y;

		zMinusPoint = sxy;
		point.y = 0;
		point.x = 0;
		 zMinusPoint = c_sub(zMinusPoint, point);
		zMinusPointDistance = c_abs(zMinusPoint);// zMinusPoint.magnitude();
		if (zMinusPointDistance < distance)
			distance = zMinusPointDistance;
		n++;
	}
	colors.a = n;
	colors.b = distance;
	return (colors);
}



/*

 t_ci	amandelbrot(t_complex sxy, t_complex c, int max_iter)
{
	t_ci	result;
	//t_complex	c;

	int			i;

	result.z = c_add(c_mult(result.z, result.z), c);
	result.i = result.z.x * result.z.x + result.z.y * result.z.y;

	return (result);
} 

 */
