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

int	solve(t_m4x16 *map, t_tet *tetris)
{
	uint64_t	bits;
	t_uint		i;

	bits = tetris->bits;
	if (!bits)
		return (FT_TRUE);
	i = -1U;
	while (map[++i] & bits != 0)
		bits <<= 1;
	return (solve(map, &tetris[i]));
}
