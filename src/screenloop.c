/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenloop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 18:34:17 by jsaarine          #+#    #+#             */
/*   Updated: 2022/07/06 19:20:17 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h" 

void	inner_loop(int x, int y, t_context *ctx)
{
	double		xc;
	double		yc;
	t_colors	color;
	t_complex	c;
	t_complex	mouse;

	xc = (3 * ctx->scale * (float)x / (float)WIN_W) - 2.5 * ctx->scale;
	yc = (3 * ctx->scale * (float)y / (float)WIN_W) - 1.5 * ctx->scale;
	c.x = xc + ctx->SOffsetX;
	c.y = yc + ctx->SOffsetY;
	if (!ctx->pause)
	{
		mouse.x = (ctx->mouse_x - WIN_W / 2) / 666.0;
		mouse.y = (ctx->mouse_y - WIN_W / 2) / 666.0;
	}
	color = julia(mouse, c, ctx);
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
			inner_loop(x, y, ctx);
			x++;
		}
		y += NUM_TASKS;
	}
}
