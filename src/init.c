/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:14:51 by jsaarine          #+#    #+#             */
/*   Updated: 2022/07/14 14:43:46 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	init_pthread(t_context *ctx)
{
	ctx->tasks_done_mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	ctx->tasks_taken_mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	ctx->frame_start_mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	ctx->frame_end_mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	ctx->frame_start_cv = (pthread_cond_t)PTHREAD_COND_INITIALIZER;
	ctx->frame_end_cv = (pthread_cond_t)PTHREAD_COND_INITIALIZER;
	ctx->tasks_done = 0;
	ctx->tasks_taken = 0;
}

static void	create_threads(t_context *ctx)
{
	int	i;

	i = 0;
	while (i < NUM_THREADS)
	{
		pthread_create(&ctx->threadpool[i],
			NULL, (void *(*)(void *))taskhandler, (void *)ctx);
		i++;
	}
}

void	init_context(t_context *ctx)
{
	ctx->mlx = mlx_init();
	ctx->fb.img = mlx_new_image(ctx->mlx, WIN_W, WIN_H);
	ctx->fb.data = mlx_get_data_addr(ctx->fb.img,
			&ctx->fb.bits_per_pixel, &ctx->fb.line_length, &ctx->fb.endian);
	ctx->win = mlx_new_window(ctx->mlx, WIN_W, WIN_H, "Machine State");
	ctx->frame_n = 123;
	ctx->s_offset_x = x_offset_selector(ctx);
	ctx->s_offset_y = 0;
	ctx->zoom_xos = 0;
	ctx->scale = 1;
	ctx->left_mouse_dn = 0;
	ctx->right_mouse_dn = 0;
	ctx->max_iter = 234;
	ctx->pause = 0;
	ctx->world_w = 2.5;
	ctx->world_h = ctx->world_w * (float) WIN_H / (float) WIN_W;
	ctx->help_text = 1;
	init_pthread(ctx);
	create_threads(ctx);
}

double	x_offset_selector(t_context *ctx)
{
	if (ctx->choose_fractal == 3
		|| ctx->choose_fractal == 4
		|| ctx->choose_fractal == 5)
		return (1.0);
	return (0.25);
}
