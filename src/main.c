/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:09:41 by jsaarine          #+#    #+#             */
/*   Updated: 2022/06/28 17:26:26 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

	 #include <time.h>
	 #include <stdio.h>
int	draw_frame(t_context *ctx)
{
	clock_t		start_time;

	start_time	= clock();
	ctx->frame_n++;
	pthread_mutex_lock(&ctx->tasks_taken_mutex);
	ctx->tasks_taken = 0;
	ctx->tasks_done = 0;
	pthread_mutex_unlock(&ctx->tasks_taken_mutex);
	pthread_mutex_lock(&ctx->tasks_done_mutex);
	pthread_mutex_unlock(&ctx->tasks_done_mutex);
	pthread_mutex_lock(&ctx->frame_start_mutex);
	pthread_cond_broadcast(&ctx->frame_start_cv);
	pthread_mutex_unlock(&ctx->frame_start_mutex);
	pthread_mutex_lock(&ctx->frame_end_mutex);
	pthread_cond_wait(&ctx->frame_end_cv, &ctx->frame_end_mutex);
	pthread_mutex_unlock(&ctx->frame_end_mutex);
	mlx_put_image_to_window(ctx->mlx, ctx->win, ctx->fb.img, 0, 0);
	double cpu_time_used;
	cpu_time_used = ((double)(clock() -start_time)) / CLOCKS_PER_SEC;
	printf("%f\n", cpu_time_used);
	return (1);
}

static void	hook_em_up(t_context *ctx)
{
	mlx_hook(ctx->win, ON_KEYDOWN, 1L << 0, on_keypress, ctx);
	mlx_hook(ctx->win, ON_MOUSEDOWN, 0x04, on_mouse_down, ctx);
	mlx_hook(ctx->win, ON_MOUSEMOVE, 0x40, on_mouse_move, ctx);
	mlx_hook(ctx->win, ON_MOUSEUP, 0, on_mouse_up, ctx);
	mlx_hook(ctx->win, ON_DESTROY, 0, fdf_close, ctx);
	mlx_loop_hook(ctx->mlx, draw_frame, ctx);
}

int	main(/* int argc, char **argv */)
{
	t_context	ctx;

	init_context(&ctx);
	hook_em_up(&ctx);
	mlx_loop(ctx.mlx);
	return (0);
}
