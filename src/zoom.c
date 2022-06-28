/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 12:57:16 by jsaarine          #+#    #+#             */
/*   Updated: 2022/06/28 16:55:41 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

void	zoom_to_mouse(t_context *ctx, double in_out)
{
	double	mouse_screen_x_fraction;
	double	mouse_screen_y_fraction;

	mouse_screen_x_fraction = (double)ctx->mouse_x / WIN_W;
	mouse_screen_y_fraction = (double)ctx->mouse_y / WIN_H;
	if (in_out < 1.0)
	{
		ctx->scale *= in_out;
		ctx->world_w *= in_out;
		ctx->world_h *= in_out;
		ctx->SOffsetX += -0.276 * ctx->scale
			+ mouse_screen_x_fraction * ctx->world_w * 0.1315;
		ctx->SOffsetY += -0.052 * ctx->scale
			+ mouse_screen_y_fraction * ctx->world_h * 0.1311;
	}
	else
	{
		ctx->scale *= in_out;
		ctx->world_w *= in_out;
		ctx->world_h *= in_out;
		ctx->SOffsetX -= -0.22 * ctx->scale
			+ mouse_screen_x_fraction * ctx->world_w * 0.105;
		ctx->SOffsetY -= -0.053 * ctx->scale
			+ mouse_screen_y_fraction * ctx->world_h * 0.1315;
	}
}
