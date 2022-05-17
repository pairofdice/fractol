/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 17:51:44 by jsaarine          #+#    #+#             */
/*   Updated: 2022/05/16 21:08:04 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

#include <unistd.h>

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

double	mandelbrot(t_complex c)
{
	t_complex	z;
	t_complex	zMinusPoint;
	t_complex	point;
	int	n;
	int i;
	double distance;
	double zMinusPointDistance;

	z.x = 0;
	z.y	= 0;

	i = 0;
	n = 0;
	distance = 1e20;

	while (i < 64 && n < 100)
	{
		//ft_putstr("HEI");

		z = c_add(c_mult(z, z), c);
		i = z.x * z.x + z.y * z.y;

/* 		zMinusPoint = z;
		point.y = 0;
		point.x = 0;
		 zMinusPoint = c_sub(zMinusPoint, point);
		zMinusPointDistance = c_abs(zMinusPoint);// zMinusPoint.magnitude();
		if (zMinusPointDistance < distance)
			distance = zMinusPointDistance; */
		n++;
	}
	return (n);
}


double	julia(t_complex z)
{
	//t_complex	z;
	t_complex	c;
	t_complex	zMinusPoint;
	t_complex	point;
	int	n;
	int i;
	double distance;
	double zMinusPointDistance;

	//z.x = 0;
	//z.y	= 0;
	c.x = 0.355;
	c.y	= 0.355;

	i = 0;
	n = 0;
	distance = 1e20;

	while (i < 64 && n < 100)
	{
		//ft_putstr("HEI");

		z = c_add(c_mult(z, z), c);
		i = z.x * z.x + z.y * z.y;

		zMinusPoint = z;
		point.y = 0;
		point.x = 0;
		 zMinusPoint = c_sub(zMinusPoint, point);
		zMinusPointDistance = c_abs(zMinusPoint);// zMinusPoint.magnitude();
		if (zMinusPointDistance < distance)
			distance = zMinusPointDistance;
		n++;
	}
	return (distance);
}


/*

Complex zMinusPoint = new Complex(z);
        zMinusPoint = zMinusPoint.subtract(point);

        double zMinusPointDistance = zMinusPoint.magnitude();
        if (zMinusPointDistance < distance)
            distance = zMinusPointDistance;

 */

void	fractaldraw(t_context *ctx)
{
	int	y;
	int	x;
	double	xc;
	double	yc;
	double	color;

	t_complex c;

	y = 0;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			xc = (4 * (float)x /(float)WIN_W) - 2.6;
			yc = (4 * (float)y /(float)WIN_W) - 1.5;
			//xc = lerp(-2, 2, (float)x/(float)WIN_W);
			//yc = lerp(-2, 2, (float)y/(float)4);
			c.x = xc;
			c.y = -yc;

			/* printf("%.2f, %.2f, %.2f ", c.x, c.y, (float)x/(float)4);
			*/
			//printf("HEI\n");

			//color = mandelbrot(c);
			color = julia(c);



			img_pixel_put(&ctx->fb, x, y, rgb_to_int((t_point){
				125 - sin(0.1/ (color + 0.004)) * 125 + color * 30/* color * 50 +(1/ (color + 0.004))  */ ,
				 125 - sin(0.07/ (color + 0.004)) * 125/* 255 - (1.0/color+1.0) */,
				125 + sin(0.13/ (color + 0.004)) * 125/* 200- color*80 */}));
			x++;
		}/*
		if (y % 25 == 0)
			printf("\n"); */
		y++;
	}
}
// 255 - (1/ (color + 0.004))
// 255 - color * 100
