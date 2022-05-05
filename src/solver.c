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

int	solve(uint16_t *map, t_tet *tetris, uint8_t size)
{
	t_m4x16		*m_chunk;
	uint64_t	bits;
	t_uint		x;
	t_uint		y;

	if (!tetris->bits)
		return (FT_TRUE);
	y = -1U;
	while (++y < size)
	{
		m_chunk = (t_m4x16 *)&map[y];
		x = -1U;
		while (++x < size)
		{
			bits = (tetris->bits << x);
			if ((*m_chunk & bits) == 0)
			{
				*m_chunk ^= bits;
				if (solve(map, &tetris[1], size))
					return (FT_TRUE);
				*m_chunk ^= bits;
			}
		}
	}
	return (FT_FALSE);
}
