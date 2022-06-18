/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_it.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 10:59:05 by jsaarine          #+#    #+#             */
/*   Updated: 2022/06/18 16:40:08 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"





int	on_keypress(int key_nb, t_context *ctx)
{
	//mlx_put_image_to_window(ctx->mlx, ctx->win, ctx->fb.img, 0, 0);

	on_keys_a(key_nb, ctx);
	on_keys_b(key_nb, ctx);

	//mlx_put_image_to_window(ctx->mlx, ctx->win, ctx->fb.img, 0, 0);

	return (0);
}

int	fdf_close(t_context *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
	return (0);
}

int	on_mouse_down(int button, int x, int y, t_context *ctx)
{
	printf("%d\n",  button);
	if (x >= 0 && x < WIN_W && y - Y_OFFSET >= 0 && y - Y_OFFSET < WIN_H)
	{
		if (button == 2)
			ctx->right_mouse_dn = 1;
		if (button == 1)
			ctx->left_mouse_dn = 1;
	}
	return (0);
}

int	on_mouse_move(int x, int y, t_context *ctx)
{
	double	dx;
	double	dy;
	printf("y is %d \n", y);

	dx = ctx->mouse_x - x;
	dy = ctx->mouse_y + Y_OFFSET - y;
	if (ctx->right_mouse_dn == 1)
	{
		// printf("%f %f\n", dx, dy);
		ctx->SOffsetX += dx  / 260.0 * ctx->scale;
		ctx->SOffsetY += dy  / 260.0 * ctx->scale;
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
