/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multithread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 17:51:44 by jsaarine          #+#    #+#             */
/*   Updated: 2022/06/14 20:25:01 by jsaarine         ###   ########.fr       */
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

/*

Complex zMinusPoint = new Complex(z);
        zMinusPoint = zMinusPoint.subtract(point);

        double zMinusPointDistance = zMinusPoint.magnitude();
        if (zMinusPointDistance < distance)
            distance = zMinusPointDistance;

 */

double screen_to_world()
{
	return (0.0); // ?????
}

void taskmaster(t_context *ctx)
{
	int task;

	task = ctx->tasks_taken;
	if (task < TASK_QUEUE)
	{

	}
}

void	fractaldraw(t_context *ctx, int task)
{
	int	y;
	int	x;
	double	xc;
	double	yc;
	double	color;

	t_complex c;
	t_complex mouse;

	// get task, share work based on tasks

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

