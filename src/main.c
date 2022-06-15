/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:09:41 by jsaarine          #+#    #+#             */
/*   Updated: 2022/06/15 18:17:45 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"


void	colorslide(t_frame_buffer *fb)
{
	int	y;
	int	x;
	int	xc;
	int	yc;

	y = 0;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			xc = (float)x / (float)WIN_W * 60;
			yc = (float)y / (float)WIN_H * 60;
			img_pixel_put(fb, x, y,
				rgb_to_int((t_point){xc + 10, yc + 10, 10
					+ (float)(xc + yc) / (float)2, 0}));
			x++;
		}
		y++;
	}
}



double	lerp(a, b, t)
{
	return ((1 - t) * a + b);
}

double	eerp(a, b, t)
{
	return (a^(1 - t) * b^t);
}


void rotate_around(t_point *p, t_point pivot, t_context *ctx)
{
	double x;
	double y;
	float	rotation;



	rotation = ctx->frame_n / 1000.0;
	x = p->x;
	y = p->y;
	pivot.x++;

	p->x = x * cos(rotation) - y * sin(rotation);
	p->y = y * cos(rotation) + x * sin(rotation);
}


int	draw_frame(t_context *ctx)
{
	ctx->frame_n++;

    double cpu_time_used;
     
     
     clock_t curr;
	curr = clock();
	cpu_time_used = ((double)(curr - ctx->prev)) / CLOCKS_PER_SEC;
	printf("%f\n", 1/cpu_time_used);
	ctx->prev = clock();
	/*
	t_line	line;

	line.a.x = WIN_W / 2;
	line.a.y = WIN_H / 2;

	t_complex a;
	a.x = 0.999;
	a.y = 0.01;
	int i = 0;


	while (i < ctx->frame_n)
	{
		a = c_mult(a, a);
		i++;
	}

	line.b.x = WIN_H / 2 + a.x;
	line.b.y = WIN_H / 2 + a.y; */


	//draw_line(&line, ctx);
/* 	int task;

	task = 0;
	while (task < TASK_QUEUE)
	{ */
		fractaldraw(ctx, ctx->frame_n % MAX_THREADS);
/* 		task++;
	} */
	mlx_put_image_to_window(ctx->mlx, ctx->win, ctx->fb.img, 0, 0);
	return (1);
}
static void	hook_em_up(t_context *ctx)
{
	mlx_loop_hook(ctx->mlx, draw_frame, ctx);
	mlx_hook(ctx->win, ON_KEYDOWN, 1L << 0, on_keypress, ctx);
	mlx_hook(ctx->win, ON_DESTROY, 0, fdf_close, ctx);
	mlx_hook(ctx->win, ON_MOUSEDOWN, 0, on_mouse_down, ctx);
	mlx_hook(ctx->win, ON_MOUSEUP, 0, on_mouse_up, ctx);
}

int	main(/* int argc, char **argv */)
{
	t_context	ctx;
	t_complex	a;
	t_complex	b;
	t_complex	res;

	a.x = 3;
	a.y = 2;
	b.x = 3;
	b.y = 2;

	res = c_mult(a, b);
	/* printf("%f %f", res.x, res.y); */



	init_context(&ctx);
	// handle_args(argc, argv, &ctx);
	//colorslide(&ctx.fb);
	mlx_loop_hook(ctx.mlx, draw_frame, &ctx);
	colorslide(&ctx.fb);
	//fractaldraw(&ctx, 0);


	mlx_put_image_to_window(ctx.mlx, ctx.win, ctx.fb.img, 0, 0);

	// max_dimensions(&ctx);
	// hook_em_up(&ctx);
	hook_em_up(&ctx);
	mlx_hook(ctx.win, ON_MOUSEMOVE, 0, on_mouse_move, &ctx);

	mlx_loop(ctx.mlx);
	return (0);
}
