/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 17:06:17 by jsaarine          #+#    #+#             */
/*   Updated: 2022/07/14 18:58:56 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double	ft_fabs(double n)
{
	if (n < 0)
		return (-n);
	return (n);
}

void	help_text(t_context *ctx)
{
	char	*hints[7];
	int		i;

	hints[0] = "Move:           W, A, S, D or Mouse2";
	hints[1] = "Zoom:           R, F";
	hints[2] = "Iterations:     T, G";
	hints[3] = "Lock mouse:     P";
	hints[4] = "Cycle fractals: B";
	hints[5] = "Toggle help     H";
	hints[6] = "Exit:           Esc";
	i = 0;
	while (i < 7)
	{
		mlx_string_put(ctx->mlx, ctx->win, 20, 20 + i * 13, 0xFFFFFF, hints[i]);
		i++;
	}
}

int	fractol_close(t_context *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
	return (0);
}

int	ft_strcmp(const char *a, const char *b)
{
	while (*a && *b && (*a == *b))
	{
		a++;
		b++;
	}
	return (((unsigned char)*a) - ((unsigned char)*b));
}
