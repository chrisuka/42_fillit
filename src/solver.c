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

/* NOTE: we can optimize the fitting further by precalculating
** the offset based on tet bounds and simply skipping some iterations
** therefore we will not need to check here if tet is inside grid
*/
static int	fit_piece(t_m4x16 chunk, t_tet piece, t_uint size)
{
	if (piece.x + piece.w > size
		|| piece.y + piece.h > size)
		return (FT_FALSE);
	return (piece.bits & chunk == 0);
}

// BAD IDEA! prefer higher memory usage over more processing per iteration!
//	TODO: mod tr_bitstr16 to return 64 with the correct line width instead
/* static uint64_t	tet_expand_rows(uint16_t b_in)
{
	uint64_t	b_out;
	uint8_t		i;

	b_out = (uint64_t)b_in;
	i = 0;
	while ((1 << i) & )
} */

int	solve(t_m4x16 *map, t_tet *tetris, t_uint size)
{
	uint64_t	bits;
	t_uint		chunks;
	t_uint		i;
	t_uint		x;
	t_uint		y;

	bits = tet_expand_rows(tetris->bits); // SEE LINE 27
	if (!bits)
		return (FT_TRUE);
	chunks = size / 4; // can be passed as parameter
	i = 0;
	while (!fit_piece(map[i], bits, size))
	{
		x = 0;
		y = 0;
		if (x++ < size)
			bits <<= 1;
		else
		{
			bits <<= tetris->w;
			y++;
			x = 0;
		}
		if (y >= size)
			return (FT_FALSE);
	}
	return (solve(map, &tetris[1], size));
}
