/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:14:51 by jsaarine          #+#    #+#             */
/*   Updated: 2022/06/17 22:35:32 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init_context(t_context *ctx)
{
	ctx->mlx = mlx_init();
	ctx->fb.img = mlx_new_image(ctx->mlx, WIN_W, WIN_H);
	ctx->fb.data = mlx_get_data_addr(ctx->fb.img, &ctx->fb.bits_per_pixel,
			&ctx->fb.line_length, &ctx->fb.endian);
	ctx->win = mlx_new_window(ctx->mlx, WIN_W, WIN_H, "Machine State");
	ctx->frame_n = 123;
	//ctx->frame_n = 1234567890;

	ctx->SOffsetX = 0;
	ctx->SOffsetY = 0;

	ctx->scale = 1;
	ctx->left_mouse_dn = 0;
	ctx->right_mouse_dn = 0;
	ctx->max_iter = 80;
	ctx->pause = 0;
	ctx->n = 0;

	ctx->tasks_done = 0;
	ctx->tasks_taken = 0;
	ctx->tasks_doing = 0;

	ctx->world_w = 2.5;
	ctx->world_h = ctx->world_w * (float)WIN_H/(float)WIN_W;
	//ctx->task_mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	ctx->tasks_done_mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	ctx->tasks_taken_mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	ctx->frame_start_mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	ctx->frame_end_mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	ctx->frame_start_cv = (pthread_cond_t)PTHREAD_COND_INITIALIZER;
	ctx->frame_end_cv = (pthread_cond_t)PTHREAD_COND_INITIALIZER;
	//ctx->task_list = malloc(sizeof(t_thread_task) * NUM_TASKS); // malloc needs a check for success
	int i = 0;
	while (i < NUM_THREADS)
	{
		//pthread_create(&thr[i], NULL, (void *(*)(void *))threads, (void *)&thread[i]))
		//printf("hello, creating threads\n");

		pthread_create(&ctx->threadpool[i], NULL,  (void *(*)(void *))taskhandler, (void *)ctx);
		i++;
	}

	ctx->fn_ptrs[0] = mandelbrot;
	ctx->fn_ptrs[1] = julia;
	ctx->fn_ptrs[2] = my_brot;
	ctx->fn_ptrs[3] = burning_ship;


}
