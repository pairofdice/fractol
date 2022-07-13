/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_put_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 12:20:23 by jsaarine          #+#    #+#             */
/*   Updated: 2022/07/13 15:19:15 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	img_pixel_put(t_frame_buffer *fb, int x, int y, int color)
{
	char	*dst;

	dst = fb->data + (y * fb->line_length + x * (fb->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	rgb_to_int(t_point c)
{
	return ((int)c.x << 16 | (int)c.y << 8 | (int)c.z);
}
