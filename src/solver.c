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

static inline void	update_atoms(t_tet *shape, t_point pos)
{
	uint8_t	atom_i;
	t_point	*tpos;

	atom_i = 4;
	while (atom_i-- > 0)
	{
		tpos = &shape->atoms[atom_i];
		*tpos = (t_point){tpos->x + pos.x, tpos->y + pos.y};
	}
}

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
	p = (t_point){(uint8_t)-1, (uint8_t)-1};
	size = offset_size(tetris, grid_size);
	while (++p.y <= size.y)
	{
		m_chunk = (t_m4x16 *)&map[p.y];
		p.x = (uint8_t)-1;
		while (++p.x <= size.x)
		{
			bits = (tetris->bits << p.x);
			if ((*m_chunk & bits) == 0)
			{
				*m_chunk ^= bits;
/*				printf("insert (%u,%u)\n", x, y); //DEBUG
				print_grid(map, size, tetris); //DEBUG */
				if (solve(map, &tetris[1], grid_size))
				{
					update_atoms(tetris, p);
					return (FT_TRUE);
				}
				*m_chunk ^= bits;
			}
		}
	}
	return (FT_FALSE);
}

// TODO:
//	PRECALCULATE OFFSETS	----	[CONTENDER AVAILABLE]

//	MAKE SURE M_CHUNK DOESN'T POINT TO GARBAGE MEMORY
//		AKA. HAVE SOME SORT OF BOTTOM OFFSET

//	CONSIDER ALLOCATING EXTRA SPACE FOR MAP TO REDUCE REALLOCING
