/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multithread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 17:51:44 by jsaarine          #+#    #+#             */
/*   Updated: 2022/07/04 20:25:01 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

void	taskhandler(void *context)
{
	t_context	*ctx;
	int			task_n;

	ctx = (t_context *) context;
	while (1)
	{
 		pthread_mutex_lock(&ctx->frame_start_mutex);
		pthread_cond_wait(&ctx->frame_start_cv, &ctx->frame_start_mutex);
		pthread_mutex_unlock(&ctx->frame_start_mutex);
		while (1)
		{
 			pthread_mutex_lock(&ctx->tasks_taken_mutex);
			if (ctx->tasks_taken >= NUM_TASKS)
			{
 				pthread_mutex_unlock(&ctx->tasks_taken_mutex);
				pthread_mutex_lock(&ctx->frame_start_mutex);
				pthread_cond_wait(&ctx->frame_start_cv, &ctx->frame_start_mutex);
				pthread_mutex_unlock(&ctx->frame_start_mutex);
			} else
			{
				task_n = ctx->tasks_taken;
				ctx->tasks_taken++;
 				pthread_mutex_unlock(&ctx->tasks_taken_mutex);
				fractaldraw(ctx,  task_n);
				pthread_mutex_lock(&ctx->tasks_done_mutex);
				ctx->tasks_done++;
				if (ctx->tasks_done >= NUM_TASKS)
				{
					pthread_mutex_unlock(&ctx->tasks_done_mutex);
					pthread_mutex_lock(&ctx->frame_end_mutex);
					pthread_cond_broadcast(&ctx->frame_end_cv);
					pthread_mutex_unlock(&ctx->frame_end_mutex);
					break ;
				} else
					pthread_mutex_unlock(&ctx->tasks_done_mutex);
			}
		}
		}
}

void	fractaldraw(t_context *ctx, int task)
{
	int	y;
	int	x;
	double	xc;
	double	yc;
	t_complex c;
	t_complex mouse;
	int mod;
	mod = ctx->frame_n % 2; 
	y = task + mod;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W  )
		{
			xc = (3 * ctx->scale * (float)x /(float)WIN_W) - 2.5 * ctx->scale;
			yc = (3 * ctx->scale * (float)y /(float)WIN_W) - 1.5 * ctx->scale;

			c.x = xc + ctx->SOffsetX;
			c.y = yc + ctx->SOffsetY;
			if (!ctx->pause)
			{
				mouse.x = (ctx->mouse_x - WIN_W/2) /666.0;
				mouse.y = (ctx->mouse_y- WIN_W/2) /666.0;
			}
			if (ctx->choose_fractal == 1)
				t_colors color = fractal_base(mouse, c, ctx);
			else
				t_colors color = fractal_base(mouse, c, ctx);
			img_pixel_put(&ctx->fb, x, y, rgb_to_int((t_point){
				125 - sin(0.181/ (color.b + 0.008) + ctx->frame_n /21.0) * 125  /* color * 50 +(1/ (color + 0.004))  */ ,
				 125 - sin(0.193/ (color.b + 0.008) + ctx->frame_n / 29.0) * 125 /* 255 - (1.0/color+1.0) */,
				125 + sin(0.563/ (color.b + 0.004) + ctx->frame_n /31.0) * 125/* 200- color*80 */}));
			x++;
		}
		y += NUM_TASKS;
	}
}
