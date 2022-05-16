/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <ikarjala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 20:33:57 by ikarjala          #+#    #+#             */
/*   Updated: 2022/04/21 21:17:53by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <stdio.h> //DEBUG=======================================================

// TODO: move this function to math.c
void	pos2d_translate(t_point *atoms, t_point pos, uint8_t n)
{
	while (n-- > 0)
	{
		*atoms = (t_point){atoms->x + pos.x, atoms->y + pos.y};
		atoms++;
	}
}

static inline t_point	offset_size(t_tet *shape, uint16_t size)
{
	return ((t_point){
		(uint8_t)(size - shape->bounds.x),
		(uint8_t)(size - shape->bounds.y)});
}
// WARNING! CAN GO NEGATIVE AND OVERFLOW TO 255 !

int	solve(uint16_t *map, t_tet *tetris, uint16_t grid_size)
{
	t_m4x16		*m_chunk;
	uint64_t	bits;
	t_point		p;
	t_point		size;

	if (!tetris->bits)
		return (FT_TRUE);
	p = (t_point){(uint8_t)-1, (uint8_t)-1};
	size = offset_size(tetris, grid_size);
	while (++p.y <= (int8_t)size.y)
	{
		m_chunk = (t_m4x16 *)&map[p.y];
		p.x = (uint8_t)-1;
		while (++p.x <= (int8_t)size.x)
		{
			bits = (tetris->bits << p.x);
			if ((*m_chunk & bits) == 0)
			{
				*m_chunk ^= bits;
				if (solve(map, &tetris[1], grid_size))
				{
					pos2d_translate(tetris->atoms, p, 4);
					return (FT_TRUE);
				}
				*m_chunk ^= bits;
			}
		}
	}
	return (FT_FALSE);
}
