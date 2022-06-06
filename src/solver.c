/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <ikarjala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 18:20:29 by ikarjala          #+#    #+#             */
/*   Updated: 2022/06/06 18:23:01 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static inline t_point	offset_size(t_tet *shape, uint16_t size)
{
	return ((t_point){
		(uint8_t)(size - shape->bounds.x),
		(uint8_t)(size - shape->bounds.y)});
}

int	solve(uint16_t *map, t_tet *tetris, uint16_t grid_size)
{
	t_m4x16		*m_chunk;
	uint64_t	bits;
	t_point		p;
	t_point		size;

	if (!tetris->bits)
		return (FT_TRUE);
	size = offset_size(tetris, grid_size);
	p = (t_point){0 - 1, 0 - 1};
	while (++p.y <= (int8_t)size.y)
	{
		m_chunk = (t_m4x16 *)&map[p.y];
		p.x = 0 - 1;
		while (++p.x <= (int8_t)size.x)
		{
			bits = (tetris->bits << p.x);
			if ((*m_chunk & bits) == 0)
			{
				*m_chunk ^= bits;
				if (solve(map, tetris + 1, grid_size))
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
