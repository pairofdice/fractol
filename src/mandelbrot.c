/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 17:51:44 by jsaarine          #+#    #+#             */
/*   Updated: 2022/05/30 13:26:12 by jsaarine         ###   ########.fr       */
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


double	julia(t_complex sxy, t_complex c, int max_iter)
{
	//t_complex	z;
	//t_complex	c;
	t_complex	zMinusPoint;
	t_complex	point;
	int	n;
	int i;
	double distance;
	double zMinusPointDistance;

	//z.x = 0;
	//z.y	= 0;
/* 	c.x = 0.355;
	c.y	= 0.355; */


	i = 0;
	n = 0;
	distance = 1e20;

	while (i < 64 && n < max_iter)
	{
		//ft_putstr("HEI");

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
	return (distance);
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
			//int osx = ctx->SOffsetX / WIN_W;
			xc = (4 * ctx->scale * (float)x /(float)WIN_W) - 2.6 * ctx->scale ;
			yc = (4 * ctx->scale * (float)y /(float)WIN_W) - 1.5 * ctx->scale;
			//xc = lerp(-2, 2, (float)x/(float)WIN_W);
			//yc = lerp(-2, 2, (float)y/(float)4);
			c.x = xc + ctx->SOffsetX;
			c.y = -yc + ctx->SOffsetY;

			/* printf("%.2f, %.2f, %.2f ", c.x, c.y, (float)x/(fl oat)4);
			*/
			//printf("HEI\n");

			t_colors color = mandelbrot(c, ctx->max_iter);
			mouse.x = (ctx->mouse_x - WIN_W/2) /666.0;
			mouse.y = (ctx->mouse_y- WIN_W/2) /666.0;
			//color = julia(c, mouse, ctx->max_iter);



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
