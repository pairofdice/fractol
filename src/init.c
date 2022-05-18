/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:14:51 by jsaarine          #+#    #+#             */
/*   Updated: 2022/05/18 18:42:43 by jsaarine         ###   ########.fr       */
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
	ctx->frame_n = 0;
	ctx->SOffsetX = 0;
	ctx->SOffsetY = 0;
	ctx->world_w = 2.5;

	ctx->world_h = 2;
	ctx->scale = 1;
	ctx->left_mouse_dn = 0;
	ctx->right_mouse_dn = 0;
	ctx->max_iter = 200;
}
