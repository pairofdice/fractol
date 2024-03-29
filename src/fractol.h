/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:15:52 by jsaarine          #+#    #+#             */
/*   Updated: 2022/07/14 18:58:29 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "mlx.h"
# include <math.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# define USAGE "usage: ./fractol <fractal_name>\nAvailable fractals: \
mandelbrot, mandelmouse, burningship, julia, mandel_tri, julia_quad\n"

enum {
	NUM_THREADS = 13,
	NUM_TASKS = 29,
	NUM_FRACTALS = 6,
	WIN_W = 999,
	WIN_H = 999,
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17,
	Y_OFFSET = 0,
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
	KEY_N = 45,
	KEY_L = 4,
	KEY_LA = 123,
	KEY_DA = 125,
	KEY_RA = 124,
	KEY_UA = 126
};

typedef struct s_complex
{
	long double	x;
	long double	y;
}	t_complex;

typedef struct s_ci
{
	t_complex	z;
	int			i;
}	t_ci;

typedef struct s_colors
{
	double	a;
	double	b;
}	t_colors;

typedef struct s_fr_dat
{
	t_complex	point;
	t_complex	z;
	t_complex	z_minus_point;
	double		zmp_distance;
	int			n;
	int			i;
	double		distance;
}	t_fr_dat;

typedef struct s_point
{
	double	x;
	double	y;
	double	z;
}	t_point;

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
	int				mouse_x;
	int				mouse_y;
	int				right_mouse_dn;
	int				left_mouse_dn;
	double			zoom_xos;
	double			s_offset_x;
	double			s_offset_y;
	double			scale;
	double			world_w;
	double			world_h;
	int				frame_n;
	int				max_iter;
	int				pause;
	pthread_mutex_t	tasks_done_mutex;
	pthread_mutex_t	tasks_taken_mutex;
	pthread_mutex_t	frame_start_mutex;
	pthread_mutex_t	frame_end_mutex;
	pthread_cond_t	frame_start_cv;
	pthread_cond_t	frame_end_cv;
	size_t			tasks_done;
	size_t			tasks_taken;
	pthread_t		threadpool[NUM_THREADS];
	size_t			choose_fractal;
	int				help_text;
}	t_context;

// complex.c
t_complex	c_add(t_complex a, t_complex b);
t_complex	c_sub(t_complex a, t_complex b);
double		c_abs(t_complex a);
t_complex	c_mult(t_complex a, t_complex b);
t_complex	c_pow(t_complex a, size_t pow);
// fractals.c
t_colors	mandelbrot(t_complex sxy, t_complex c, t_context *ctx);
t_colors	julia(t_complex sxy, t_complex c, t_context *ctx);
t_colors	julia_mess(t_complex sxy, t_complex c, t_context *ctx);
t_colors	burning_ship(t_complex sxy, t_complex c, t_context *ctx);
// handle_keys.c
int			on_keypress(int key_nb, t_context *ctx);
// init.c
void		init_context(t_context *ctx);
double		x_offset_selector(t_context *ctx);
// mouse_events.c
int			on_mouse_down(int button, int x, int y, t_context *ctx);
int			on_mouse_move(int x, int y, t_context *ctx);
int			on_mouse_up(int button, int x, int y, t_context *ctx);
// multithread.c
void		taskhandler(void *ctx);
// pixel_put_color.c
void		img_pixel_put(t_frame_buffer *fb, int x, int y, int color);
int			rgb_to_int(t_point c);
// screenloop.c
void		screenloop(t_context *ctx, int task);
// utils.c
double		ft_fabs(double n);
void		help_text(t_context *ctx);
int			fractol_close(t_context *vars);
int			ft_strcmp(const char *a, const char *b);
// zoom.c
void		zoom_to_mouse(t_context *ctx, double in_out);

#endif
