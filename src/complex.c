/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:25:47 by jsaarine          #+#    #+#             */
/*   Updated: 2022/05/09 18:17:08 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"


t_complex	cmplx_add(t_complex a, t_complex b)
{
	t_complex	result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	return (result);
}

t_complex	cmplx_sub(t_complex a, t_complex b)
{
	t_complex	result;

	result.x = a.x - b.x;
	result.y = a.y - b.y;
	return (result);
}

t_complex	cmplx_abs(t_complex a)
{
	t_complex	result;
	return (result);
}

t_complex	cmplx_mult(t_complex a, t_complex b)
{
	t_complex	result;

	result.x = a.x * b.x - a.y * b.y;
	result.y = a.x * b.y + a.y * b.x;
	return (result);
}