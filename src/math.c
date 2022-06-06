/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <ikarjala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 18:19:29 by ikarjala          #+#    #+#             */
/*   Updated: 2022/06/06 18:19:30 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int	ft_sqrt(int number)
{
	int	root;

	root = 2;
	while ((root * root) < number)
		root++;
	return (root);
}

int	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

void	pos2d_translate(t_point *atoms, t_point pos, uint8_t n)
{
	while (n-- > 0)
	{
		atoms->x += pos.x;
		atoms->y += pos.y;
		atoms++;
	}
}
