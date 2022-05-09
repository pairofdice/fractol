/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:09:41 by jsaarine          #+#    #+#             */
/*   Updated: 2022/05/09 18:20:20 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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
void	colorslide(t_frame_buffer *fb)
{
	int	y;
	int	x;
	int	xc;
	int	yc;
	int color;

	t_complex c;

	y = 0;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			xc = (((float)x / (float)WIN_W) -1) * 2;
			yc = (((float)y / (float)WIN_H ) -1) * 2;
			c.x = xc;
			c.y = -yc;
			color = mandelbrot(c);
			img_pixel_put(fb, x, y,
				rgb_to_int((t_point){color * 5, color * 5, color * 5}));
			x++;
		}
		y++;
	}
}


int	draw_frame(t_context *ctx)
{
	t_line	line;

	ctx->frame_n++;
	line.a.x = WIN_W / 2;
	line.a.y = WIN_H / 2;

	t_complex a;
	a.x = 0.999;
	a.y = 0.01;
	int i = 0;

	while (i < ctx->frame_n)
	{
		a = cmplx_mult(a, a);
		i++;
	}

	line.b.x = WIN_H / 2 + a.x;
	line.b.y = WIN_H / 2 + a.y;


	draw_line(&line, ctx);	
	
	mlx_put_image_to_window(ctx->mlx, ctx->win, ctx->fb.img, 0, 0);
	
	return (1);
}



int	main(/* int argc, char **argv */)
{
	t_context	ctx;
	

	init_context(&ctx);
	colorslide(&ctx.fb);




	// handle_args(argc, argv, &ctx);
	//colorslide(&ctx.fb);
	mlx_loop_hook(ctx.mlx, draw_frame, &ctx);
	mlx_put_image_to_window(ctx.mlx, ctx.win, ctx.fb.img, 0, 0);
	// max_dimensions(&ctx);
	// hook_em_up(&ctx);
	mlx_loop(ctx.mlx);
	return (0);
}