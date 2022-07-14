/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multithread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 17:51:44 by jsaarine          #+#    #+#             */
/*   Updated: 2022/07/14 17:32:58 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	worker_wait(t_context *ctx)
{
	pthread_mutex_unlock(&ctx->tasks_taken_mutex);
	pthread_mutex_lock(&ctx->frame_start_mutex);
	pthread_cond_wait(&ctx->frame_start_cv, &ctx->frame_start_mutex);
	pthread_mutex_unlock(&ctx->frame_start_mutex);
}

static void	worker_task(int *task_n, t_context *ctx)
{
	*task_n = ctx->tasks_taken;
	ctx->tasks_taken++;
	pthread_mutex_unlock(&ctx->tasks_taken_mutex);
	screenloop(ctx, *task_n);
	pthread_mutex_lock(&ctx->tasks_done_mutex);
	ctx->tasks_done++;
}

static void	worker_broadcast(t_context *ctx)
{
	pthread_mutex_unlock(&ctx->tasks_done_mutex);
	pthread_mutex_lock(&ctx->frame_end_mutex);
	pthread_cond_broadcast(&ctx->frame_end_cv);
	pthread_mutex_unlock(&ctx->frame_end_mutex);
}

void	taskhandler(void *context)
{
	t_context	*ctx;
	int			task_n;

	ctx = (t_context *) context;
	while (1)
	{
		while (1)
		{
			pthread_mutex_lock(&ctx->tasks_taken_mutex);
			if (ctx->tasks_taken >= NUM_TASKS)
				worker_wait(ctx);
			else
			{
				worker_task(&task_n, ctx);
				if (ctx->tasks_done >= NUM_TASKS)
				{
					worker_broadcast(ctx);
					break ;
				}
				else
					pthread_mutex_unlock(&ctx->tasks_done_mutex);
			}
		}
	}
}
