/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:25:47 by jsaarine          #+#    #+#             */
/*   Updated: 2022/05/13 17:34:05 by jsaarine         ###   ########.fr       */
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
