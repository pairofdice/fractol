/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:09:41 by jsaarine          #+#    #+#             */
/*   Updated: 2022/07/14 12:49:23 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	draw_frame(t_context *ctx)
{
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
	if (ctx->help_text == 1)
		help_text(ctx);
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

void	check_args(char *arg, t_context *ctx)
{
	if (!ft_strcmp(arg, "mandelbrot"))
		ctx->choose_fractal = 0;
	else if (!ft_strcmp(arg, "mandelmouse"))
		ctx->choose_fractal = 1;
	else if (!ft_strcmp(arg, "burningship"))
		ctx->choose_fractal = 2;
	else if (!ft_strcmp(arg, "julia"))
		ctx->choose_fractal = 3;
	else if (!ft_strcmp(arg, "mandel_tri"))
		ctx->choose_fractal = 4;
	else if (!ft_strcmp(arg, "julia_quad"))
		ctx->choose_fractal = 5;
	else
	{
		ft_putstr(USAGE);
		exit(1);
	}
}

int	main(int argc, char **argv)
{
	t_context	ctx;

	if (argc == 2)
		check_args(argv[1], &ctx);
	else
	{
		ft_putstr(USAGE);
		return (1);
	}
	init_context(&ctx);
	hook_em_up(&ctx);
	mlx_loop(ctx.mlx);
	return (0);
}
