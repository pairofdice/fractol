/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:15:52 by jsaarine          #+#    #+#             */
/*   Updated: 2022/05/02 16:36:41 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

void	init_context(t_context *ctx);

enum {
	WIN_W = 1536,
	WIN_H = 1024
};

typedef struct s_frame_buffer
{
	void	*img;
	char	*data;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		height;

}	t_frame_buffer;

typedef struct s_context
{
	void			*mlx;
	void			*win;
	t_frame_buffer	fb;
	int				w;
	int				h;
	int				mouse_x;
	int				mouse_y;
	int				right_mouse_dn;
	int				left_mouse_dn;
}	t_context;

#endif
