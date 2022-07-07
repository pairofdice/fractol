/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 18:48:43 by jsaarine          #+#    #+#             */
/*   Updated: 2022/07/07 12:58:47 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	on_keys_b(int key_nb, t_context *ctx)
{
	if (key_nb == KEY_MB_W || key_nb == KEY_W)
		ctx->s_offset_y += 0.1 * ctx->scale;
	if (key_nb == KEY_MB_A || key_nb == KEY_A)
		ctx->s_offset_x -= 0.1 * ctx->scale;
	if (key_nb == KEY_MB_S || key_nb == KEY_S)
		ctx->s_offset_y -= 0.1 * ctx->scale;
	if (key_nb == KEY_MB_D || key_nb == KEY_D)
		ctx->s_offset_x += 0.1 * ctx->scale;
	if (key_nb == KEY_MB_B || key_nb == KEY_B)
	{
		ctx->choose_fractal++;
		ctx->choose_fractal %= NUM_FRACTALS;
		ctx->s_offset_x = 0;
		ctx->s_offset_y = 0;
		ctx->scale = 1;
	}
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
		zoom_to_mouse(ctx, 0.9);
	if (key_nb == KEY_MB_F || key_nb == KEY_F)
		zoom_to_mouse(ctx, 1.1);
	if (key_nb == KEY_MB_T || key_nb == KEY_T)
		ctx->max_iter += 1;
	if (key_nb == KEY_MB_G || key_nb == KEY_G)
		ctx->max_iter -= 1;
	return (0);
}
