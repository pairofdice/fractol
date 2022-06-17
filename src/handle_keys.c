/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 18:48:43 by jsaarine          #+#    #+#             */
/*   Updated: 2022/06/18 00:04:06 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	on_keys_b(int key_nb, t_context *ctx)
{
 	if (key_nb == KEY_MB_W || key_nb == KEY_W)
		ctx->SOffsetY += 0.1 * ctx->scale;
	if (key_nb == KEY_MB_A || key_nb == KEY_A)
		ctx->SOffsetX -= 0.1 * ctx->scale;
	if (key_nb == KEY_MB_S || key_nb == KEY_S)
		ctx->SOffsetY -= 0.1 * ctx->scale;
	if (key_nb == KEY_MB_D || key_nb == KEY_D)
		ctx->SOffsetX += 0.1 * ctx->scale;
	if (key_nb == KEY_MB_B || key_nb == KEY_B)
	{
		ctx->choose_fractal++;
		ctx->choose_fractal %= NUM_FRACTALS;
		ctx->SOffsetX = 0;
		ctx->SOffsetY = 0;
		ctx->scale = 1;
	}

/*
	if (key_nb == KEY_MB_C || key_nb == KEY_C)
	{
		ctx->t.color_map++;
		ctx->t.color_map %= NUM_COLORS;
	}*/
	if (key_nb == KEY_MB_P || key_nb == KEY_P)
	{
		if (ctx->pause == 0)
			ctx->pause = 1;
		else
			ctx->pause = 0;
	}
/*
	if (key_nb == KEY_MB_Z || key_nb == KEY_Z)
		reset(ctx);
 */
	return (0);
}

int	on_keys_a(int key_nb, t_context *ctx)
{
	if (key_nb == KEY_MB_ESC || key_nb == KEY_ESC)
		fdf_close(ctx);
	if (key_nb == KEY_MB_R || key_nb == KEY_R)
		//zoom_to_mouse(ctx, 0.9);
		ctx->scale *= 0.9;
	if (key_nb == KEY_MB_F || key_nb == KEY_F)
		//zoom_to_mouse(ctx, 1.1);
		ctx->scale *= 1.1;
	if (key_nb == KEY_MB_T || key_nb == KEY_T)
		ctx->max_iter += 1;
	if (key_nb == KEY_MB_G || key_nb == KEY_G)
		ctx->max_iter -= 1;
	/*
	if (key_nb == KEY_MB_Q || key_nb == KEY_Q)
		ctx->t.rot -= 128.0;
	if (key_nb == KEY_MB_E || key_nb == KEY_E)
		ctx->t.rot += 128.0;
	if (key_nb == KEY_MB_N || key_nb == KEY_N)
		ctx->draw_bg *= -1;
	 */
	return (0);
}
