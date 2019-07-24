/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 16:32:39 by ebatchas          #+#    #+#             */
/*   Updated: 2019/07/23 13:46:37 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/editor.h"

int		ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

int		ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int		ft_limit(int value, int min, int max)
{
	if (value > max)
		value = max;
	else if (value < min)
		value = min;
	return (value);
}

/*
**	this function returns 1 if the value given is in the range, else 0
*/

int	ft_is_inrange(int value, int min, int max)
{
	if (value < min || value > max)
		return (0);
	return (1);
}

/*
**	this function is made to correct the negative modulus result
**		while mapping textures
*/

int	ft_modulus(int n, int m)
{
	int result;

	result = n % m;
	if (result < 0)
		return (m + result);
	return (result);
}
