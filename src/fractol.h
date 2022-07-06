/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:15:52 by jsaarine          #+#    #+#             */
/*   Updated: 2022/07/05 16:03:41 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "mlx.h"
//# include "../minilibx/mlx.h"
# include <math.h>
# include <stdlib.h>
# include <pthread.h>


enum {
	NUM_THREADS = 13,
	NUM_TASKS = 29,
	NUM_FRACTALS = 5,
	WIN_W = 999,
	WIN_H = 999,
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 33,
	Y_OFFSET = 32102,
	KEY_MB_ESC = 65307,
	KEY_MB_W = 119,
	KEY_MB_A = 97,
	KEY_MB_S = 115,
	KEY_MB_D = 100,
	KEY_MB_Q = 113,
	KEY_MB_E = 101,
	KEY_MB_R = 114,
	KEY_MB_F = 102,
	KEY_MB_T = 116,
	KEY_MB_G = 103,
	KEY_MB_P = 112,
	KEY_MB_Z = 122,
	KEY_MB_B = 98,
	KEY_MB_C = 99,
	KEY_MB_N = 110,
	KEY_ESC = 53,
	KEY_Q = 12,
	KEY_E = 14,
	KEY_R = 15,
	KEY_F = 3,
	KEY_T = 17,
	KEY_G = 5,
	KEY_D = 2,
	KEY_A = 0,
	KEY_S = 1,
	KEY_W = 13,
	KEY_B = 11,
	KEY_P = 35,
	KEY_Z = 6,
	KEY_C = 8,
	KEY_N = 45

};

typedef struct s_complex
{
	long double x;
	long double y;
}	t_complex;

typedef struct s_ci
{
	t_complex	z;
	int			i;
}	t_ci;

typedef struct s_colors
{
	double a;
	double b;
}	t_colors;

 typedef struct s_point
{
	double	x;
	double	y;
	double	z;
	double	c;
} t_point;

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
	double			SOffsetX;
	double			SOffsetY;
	double			scale;
	double			world_w;
	double			world_h;
	int				frame_n;
	int				n;
	int				max_iter;
	int				pause;
	t_complex		screen_xy;
	pthread_mutex_t	tasks_taken_mutex;
	pthread_mutex_t	tasks_mutex;
	pthread_mutex_t	tasks_done_mutex;
	pthread_mutex_t	frame_start_mutex;
	pthread_mutex_t	frame_end_mutex;
	pthread_cond_t	frame_start_cv;
	pthread_cond_t	frame_end_cv;
	pthread_cond_t	tasks_done_cv;
	size_t			tasks_done;
	int				task;
	size_t			tasks_taken;
	size_t			tasks_doing;
	pthread_t		threadpool[NUM_THREADS];
	clock_t			prev;
	clock_t			curr;
	t_ci		(*fn_ptrs[NUM_FRACTALS])(t_complex sxy, t_complex c);
	size_t			choose_fractal;
}	t_context;

void	init_context(t_context *ctx);

void	img_pixel_put(t_frame_buffer *fb, int x, int y, int color);
void	checked_pixel_put(t_frame_buffer *fb, int x, int y, int color);

t_complex	c_add(t_complex a, t_complex b);
t_complex	c_sub(t_complex a, t_complex b);
double		c_abs(t_complex a);
t_complex	c_mult(t_complex a, t_complex b);

int			rgb_to_int(t_point c);
void	fractaldraw(t_context *ctx, int task);

// handle_it
int	on_keypress(int key_nb, t_context *ctx);
int	fdf_close(t_context *vars);
int	on_mouse_down(int button, int x, int y, t_context *ctx);
int	on_mouse_move(int x, int y, t_context *ctx);
int	on_mouse_up(int button, int x, int y, t_context *ctx);

int	on_keys_a(int key_nb, t_context *ctx);
int	on_keys_b(int key_nb, t_context *ctx);

void		zoom_to_mouse(t_context *ctx, double in_out);
double		ft_fabs(double n);
void		taskhandler(void *ctx);
t_colors	fractal_base(t_complex sxy, t_complex c, t_context *ctx);

t_ci	mandelbrot(t_complex sxy, t_complex c);
t_ci	julia(t_complex sxy, t_complex c);
t_ci	julia_inv(t_complex sxy, t_complex c);
t_ci	my_brot(t_complex sxy, t_complex c);
t_ci	burning_ship(t_complex sxy, t_complex c);


#endif
