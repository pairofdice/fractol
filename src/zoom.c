/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 12:57:16 by jsaarine          #+#    #+#             */
/*   Updated: 2022/06/10 13:49:41 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	zoom_to_mouse(t_context *ctx, double in_out)
{
	double	mouse_screen_x_fraction;
	double	mouse_screen_y_fraction;

	mouse_screen_x_fraction = (double)ctx->mouse_x / WIN_W;
	mouse_screen_y_fraction = (double)ctx->mouse_y / WIN_H;
	
	ctx->scale *= in_out;
	ctx->world_w *= in_out;
	ctx->world_h *= in_out;
	ctx->SOffsetX += -0.276 * ctx->scale + mouse_screen_x_fraction * ctx->world_w * 0.133; //276
	ctx->SOffsetY += -0.166 * ctx->scale + mouse_screen_y_fraction * ctx->world_h * 0.133;
	//ctx->SOffsetY += mouse_screen_y_fraction * ctx->world_h **0.1 ;

	printf("w: %f h: %f x: %f, y %f\n", ctx->world_w, ctx->world_h, mouse_screen_x_fraction, mouse_screen_y_fraction);
}