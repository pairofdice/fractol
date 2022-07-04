/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 15:29:50 by jsaarine          #+#    #+#             */
/*   Updated: 2022/07/04 20:34:07 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
t_ci julia(t_complex c, t_complex s_xy)

{
	t_ci result;
	c_mult(s_xy, s_xy);
	c_mult(s_xy, s_xy);
	result.z = c_add(c_mult(s_xy, s_xy), c);
	result.i = s_xy.x * s_xy.x + s_xy.y * s_xy.y;
	return (result);
}

t_ci	mandelbrot(t_complex s_xy, t_complex c)
{
	t_ci	result;
	//t_complex	c;

	//int			i;
		//result.z = c_add(c_mult(sxy, sxy), c);
		//result.i = z.x * z.x + z.y * z.y;
	result.z = c_add(c_mult(s_xy, s_xy), c);
	result.i = result.z.x * result.z.x + result.z.y * result.z.y;

	return (result);
} 
t_ci	my_brot(t_complex s_xy, t_complex c)
{
	t_ci	result;
	//t_complex	c;

	//int			i;
		//result.z = c_add(c_mult(sxy, sxy), c);
		//result.i = z.x * z.x + z.y * z.y;
	result.z = c_add(c_mult(s_xy, s_xy), c);
	result.i = result.z.x * result.z.x + result.z.y * result.z.y;

	return (result);
} 
t_ci	burning_ship(t_complex s_xy, t_complex c)
{
	t_ci	result;

	s_xy.x = ft_fabs(s_xy.x);
	s_xy.y = ft_fabs(s_xy.y);
	result.z = c_add(c_mult(s_xy, s_xy), c);
	result.i =result.z.x *result.z.x + result.z.y * result.z.y;

	return (result);
} 

t_colors	fractal_base(t_complex s_xy, t_complex c, t_context *ctx)
{
	//t_complex	z;
	//t_complex	c;
	t_complex	zMinusPoint;
	t_complex	point;
	t_ci ci;
	int	n;
	int i;
	double distance;
	double zMinusPointDistance;
	t_colors colors;

	//z.x = 0;
	//z.y	= 0;
/* 	c.x = 0.355;
	c.y	= 0.355; */


	i = 0;
	n = 0;
	distance = 1e20;

	// koita laittaa siihen sun juliaan tää kaava
	// ((((z^8 / c) + z^11) + c) * z) * c
	// tai tää ((z^9 + z) + (z^2 * c)^2) / z
	// tai mandelbrotiin tää  z^3 + c

	while (i < 64 && n < ctx->max_iter)
	{
		
		// c_mult(sxy, sxy);
		// c_mult(sxy, sxy);
		// sxy = c_add(c_mult(sxy, sxy), c);
		// i = sxy.x * sxy.x + sxy.y * sxy.y;

		// ci = ajulia( c, sxy);
		//ci = ctx->fn_ptrs[ctx->choose_fractal](sxy, c);
		ci = mandelbrot(s_xy, c);
		s_xy = ci.z;
		i = ci.i;

		

		zMinusPoint = s_xy;
		point.y =  0;
		point.x = 0 ;
		 zMinusPoint = c_sub(zMinusPoint, point);
		zMinusPointDistance = c_abs(zMinusPoint);// zMinusPoint.magnitude();
		if (zMinusPointDistance < distance)
			distance = zMinusPointDistance;
		n++;
	}
	colors.a = n;
	colors.b = distance;
	return (colors);
}




