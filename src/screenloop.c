/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenloop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 18:34:17 by jsaarine          #+#    #+#             */
/*   Updated: 2022/07/14 18:03:29 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static t_colors	choose_fractal(t_complex mouse, t_complex c, t_colors color,
				t_context *ctx)
{
	if (ctx->choose_fractal == 0)
		color = mandelbrot(mouse, c, ctx);
	if (ctx->choose_fractal == 1)
		color = julia(mouse, c, ctx);
	if (ctx->choose_fractal == 2)
		color = burning_ship(mouse, c, ctx);
	if (ctx->choose_fractal == 3)
		color = julia(c, mouse, ctx);
	if (ctx->choose_fractal == 4)
		color = julia_mess(mouse, c, ctx);
	if (ctx->choose_fractal == 5)
		color = julia_mess(c, mouse, ctx);
	return (color);
}

static void	draw(int x, int y, t_context *ctx)
{
	static t_complex	mouse;
	double				xc;
	double				yc;
	t_colors			color;
	t_complex			c;

	xc = (3 * ctx->scale * (float)x / (float)WIN_W) - 2.5 * ctx->scale;
		ctx->zoom_xos = 0;
	yc = (3 * ctx->scale * (float)y / (float)WIN_W) - 1.5 * ctx->scale;
	c.x = xc + ctx->s_offset_x;
	c.y = yc + ctx->s_offset_y;
	if (!ctx->pause)
	{
		mouse.x = (ctx->mouse_x - WIN_W / 2) / 666.0;
		mouse.y = (ctx->mouse_y - WIN_W / 2) / 666.0;
	}
	color = (t_colors){0.0, 0.0};
	color = choose_fractal(mouse, c, color, ctx);
	img_pixel_put(&ctx->fb, x, y, rgb_to_int((t_point){
			125 - sin(0.181 / (color.b + 0.008) + ctx->frame_n / 21.0) * 125,
			125 - sin(0.193 / (color.b + 0.008) + ctx->frame_n / 29.0) * 125,
			125 + sin(0.563 / (color.b + 0.004) + ctx->frame_n / 31.0) * 125}));
	x++;
}

void	screenloop(t_context *ctx, int task)
{
	int	y;
	int	x;
	int	mod;

	mod = ctx->frame_n % 2;
	y = task + mod;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			draw(x, y, ctx);
			x++;
		}
		y += NUM_TASKS;
	}
}
