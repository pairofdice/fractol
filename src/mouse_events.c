/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 15:13:58 by jsaarine          #+#    #+#             */
/*   Updated: 2022/07/14 14:13:52 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	on_mouse_down(int button, int x, int y, t_context *ctx)
{
	if (x >= 0 && x < WIN_W && y - Y_OFFSET >= 0 && y - Y_OFFSET < WIN_H)
	{
		if (button == 2)
			ctx->right_mouse_dn = 1;
		if (button == 1)
			ctx->left_mouse_dn = 1;
		if (button == 4)
			zoom_to_mouse(ctx, 0.90);
		if (button == 5)
			zoom_to_mouse(ctx, 0.90);
	}
	return (0);
}

int	on_mouse_move(int x, int y, t_context *ctx)
{
	double	dx;
	double	dy;

	dx = ctx->mouse_x - x;
	dy = ctx->mouse_y + Y_OFFSET - y;
	if (ctx->right_mouse_dn == 1)
	{
		ctx->s_offset_x += dx / 260.0 * ctx->scale;
		ctx->s_offset_y += dy / 260.0 * ctx->scale;
	}
	if (ctx->left_mouse_dn == 1)
		zoom_to_mouse(ctx, 0.9);
	else
	{
		ctx->mouse_x = x;
		ctx->mouse_y = y - Y_OFFSET;
	}
	return (0);
}

int	on_mouse_up(int button, int x, int y, t_context *ctx)
{
	if (x || y)
	{
	}
	if (button == 2)
		ctx->right_mouse_dn = 0;
	if (button == 1)
		ctx->left_mouse_dn = 0;
	return (0);
}
