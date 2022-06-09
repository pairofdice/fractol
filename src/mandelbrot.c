/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 17:51:44 by jsaarine          #+#    #+#             */
/*   Updated: 2022/06/09 18:24:27 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

#include <unistd.h>

double ft_fabs(double n)
{
	if (n < 0)
		return (-n);
	return (n);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char const *s)
{
	if (!s)
		return ;
	while (*s)
		ft_putchar(*s++);
}
t_colors	mandelbrotb(t_complex c, int max_iter)
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

	while (i < 64 && n < max_iter)
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
		zMinusPointDistance = c_abs(zMinusPoint);// zMinusPoint.magnitude();
		if (zMinusPointDistance < distance)
			distance = zMinusPointDistance;
		n++;
	}
	colors.a = n;
	colors.b = distance;
	return (colors);
}


t_colors	mandelbrot(t_complex c, int max_iter)
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

	while (i < 64 && n < max_iter)
	{
		z = c_add(c_mult(z, z), c);
		i = z.x * z.x + z.y * z.y;

 		zMinusPoint = z;
		point.y = z.y * z.x;
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

t_colors	burning_ship(t_complex c, int max_iter)
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

	while (i < 64 && n < max_iter)
	{
		z.x = ft_fabs(z.x);
		z.y = ft_fabs(z.y);
		z = c_add(c_mult(z, z), c);
		i = z.x * z.x + z.y * z.y;

 		zMinusPoint = z;
		point.y = z.y * z.x;
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


t_colors	julia(t_complex sxy, t_complex c, int max_iter)
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

	while (i < 64 && n < max_iter)
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

Complex zMinusPoint = new Complex(z);
        zMinusPoint = zMinusPoint.subtract(point);

        double zMinusPointDistance = zMinusPoint.magnitude();
        if (zMinusPointDistance < distance)
            distance = zMinusPointDistance;

 */

double screen_to_world()
{
	return (0.0);
}

void	fractaldraw(t_context *ctx)
{
	int	y;
	int	x;
	double	xc;
	double	yc;
	double	color;

	t_complex c;
	t_complex mouse;


	y = 0;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{

			xc = (3 * ctx->scale * (float)x /(float)WIN_W) - 2.5 * ctx->scale;
			yc = (3 * ctx->scale * (float)y /(float)WIN_W) - 1.5 * ctx->scale;



			c.x = xc + ctx->SOffsetX;
			c.y = yc + ctx->SOffsetY;

			/* printf("%.2f, %.2f, %.2f ", c.x, c.y, (float)x/(fl oat)4);
			*/
			//printf("HEI\n");

			t_colors color = mandelbrot(c, ctx->max_iter);
			// t_colors color = mandelbrotb(c, ctx->max_iter);
			// t_colors color = burning_ship(c, ctx->max_iter);
			if (!ctx->pause)
			{
				mouse.x = (ctx->mouse_x - WIN_W/2) /666.0;
				mouse.y = (ctx->mouse_y- WIN_W/2) /666.0;
			}
			//t_colors color = julia(c, mouse, ctx->max_iter);



			img_pixel_put(&ctx->fb, x, y, rgb_to_int((t_point){
				125 - sin(0.181/ (color.b + 0.008) + ctx->frame_n /11.0) * 125  /* color * 50 +(1/ (color + 0.004))  */ ,
				 125 - sin(0.193/ (color.b + 0.008) + ctx->frame_n / 13.0) * 125 /* 255 - (1.0/color+1.0) */,
				125 + sin(0.563/ (color.b + 0.004) + ctx->frame_n / 17.0) * 125/* 200- color*80 */}));
			x++;
		}/*
		if (y % 25 == 0)
			printf("\n"); */
		y++;
	}
}
// 255 - (1/ (color + 0.004))
// 255 - color * 100

