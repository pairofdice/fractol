/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:25:47 by jsaarine          #+#    #+#             */
/*   Updated: 2022/07/13 17:51:20 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_complex	c_add(t_complex a, t_complex b)
{
	t_complex	result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	return (result);
}

t_complex	c_sub(t_complex a, t_complex b)
{
	t_complex	result;

	result.x = a.x - b.x;
	result.y = a.y - b.y;
	return (result);
}

double	c_abs(t_complex a)
{
	return (sqrt(a.x * a.x + a.y * a.y));
}

t_complex	c_mult(t_complex a, t_complex b)
{
	t_complex	result;

	result.x = a.x * b.x - a.y * b.y;
	result.y = a.x * b.y + a.y * b.x;
	return (result);
}

t_complex	c_pow(t_complex a, size_t pow)
{
	t_complex	result;

	while (--pow)
		result = c_mult(a, a);
	return (result);
}
