/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 12:57:16 by jsaarine          #+#    #+#             */
/*   Updated: 2022/07/14 18:06:46 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	zoom_to_mouse(t_context *ctx, double zoom_dir)
{
	double	mouse_screen_x_fraction;
	double	mouse_screen_y_fraction;

	mouse_screen_x_fraction = (double)ctx->mouse_x / WIN_W;
	mouse_screen_y_fraction = (double)ctx->mouse_y / WIN_H;
	if (zoom_dir < 1.0)
	{
		ctx->scale *= zoom_dir;
		ctx->world_w *= zoom_dir;
		ctx->world_h *= zoom_dir;
		ctx->s_offset_x += -0.276 * ctx->scale
			+ mouse_screen_x_fraction * ctx->world_w * 0.1315;
		ctx->s_offset_y += -0.17 * ctx->scale
			+ mouse_screen_y_fraction * ctx->world_h * 0.1311;
	}
	else
	{
		ctx->scale *= zoom_dir;
		ctx->world_w *= zoom_dir;
		ctx->world_h *= zoom_dir;
		ctx->s_offset_x -= -0.22 * ctx->scale
			+ mouse_screen_x_fraction * ctx->world_w * 0.105;
		ctx->s_offset_y -= -0.053 * ctx->scale
			+ mouse_screen_y_fraction * ctx->world_h * 0.1315;
	}
}
