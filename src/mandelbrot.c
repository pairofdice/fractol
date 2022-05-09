/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 17:51:44 by jsaarine          #+#    #+#             */
/*   Updated: 2022/05/09 18:18:51 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	mandelbrot(t_complex c)
{
	t_complex	z;
	int	n;

	n = 0;
	z.x = 0;
	z.y	= 0;


	while ((z.x * z.x + z.y * z.y) < 4 && n < MAX_ITER)
	{
		z = cmplx_add(cmplx_mult(z, z), c);
		n++;
	}
	return (n);
}