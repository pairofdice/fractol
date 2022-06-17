/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multithread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 17:51:44 by jsaarine          #+#    #+#             */
/*   Updated: 2022/06/17 14:51:23 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

#include <unistd.h>

/*
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
 */
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

void	taskhandler(void *context)
{
	t_context	*ctx;
	int			task_n;

	ctx = (t_context *) context;
	while (1)
	{
		//printf("hello taskhandler 4\n", pt);
		// pthread_mutex_lock(&ctx->tasks_done_mutex);
		if (ctx->tasks_done == 0)
		{
			//pthread_mutex_unlock(&ctx->tasks_done_mutex);
			pthread_mutex_lock(&ctx->frame_start_mutex);
			pthread_cond_wait(&ctx->frame_start_cv, &ctx->frame_start_mutex);
			pthread_mutex_unlock(&ctx->frame_start_mutex);
		} //else
			//pthread_mutex_unlock(&ctx->tasks_done_mutex);


		//printf("hello taskhandler 4\n");
		pthread_mutex_lock(&ctx->tasks_taken_mutex);
		if ( ctx->tasks_taken < NUM_TASKS)
		{
			task_n = ctx->tasks_taken;
			ctx->tasks_taken++;
		}
		pthread_mutex_unlock(&ctx->tasks_taken_mutex);
		//printf("Task # %d\n", task_n);

		//printf("hello taskhandler 1 %d\n", ctx->tasks_done);
		fractaldraw(ctx,  task_n);

		pthread_mutex_lock(&ctx->tasks_done_mutex);
		pthread_mutex_lock(&ctx->tasks_taken_mutex);
		ctx->tasks_done++;
		//printf("hello taskhandler 2 tasks done: %d\n", ctx->tasks_done);
		if (ctx->tasks_done == NUM_TASKS)
		{
			ctx->tasks_done = 0;
			ctx->tasks_taken = 0;

			pthread_mutex_unlock(&ctx->tasks_taken_mutex);
			pthread_mutex_unlock(&ctx->tasks_done_mutex);

			pthread_mutex_lock(&ctx->frame_end_mutex);
			pthread_cond_broadcast(&ctx->frame_end_cv);
			pthread_mutex_unlock(&ctx->frame_end_mutex);
		}
		else {
			pthread_mutex_unlock(&ctx->tasks_taken_mutex);
			pthread_mutex_unlock(&ctx->tasks_done_mutex);
		}
		//printf("hello taskhandler 3\n");
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
	int mod;
	mod = ctx->frame_n % 2 + 1;

	y = task * mod;
	//printf("hello fractaldraw\n");
	//if (task == 0)
	{

	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W  )
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
			//t_colors color = burning_ship(c, ctx->max_iter);
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
		}
		y += NUM_TASKS * mod;
	}
	}

}
// 255 - (1/ (color + 0.004))
// 255 - color * 100

