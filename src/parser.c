/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <ikarjala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 19:01:35 by ikarjala          #+#    #+#             */
/*   Updated: 2022/04/12 20:14:28 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static int	tet_isvalid(t_tet shape)
{
	t_uint			index;
	const uint64_t	v_tetris[19] = {
		// we can simply put macros here, as defined in the header
	};

	index = -1U;
	while (++index < 19)
	{
		if (shape.bits == v_tetris[index])
			return (FT_TRUE);
	}
	return (FT_FALSE);
}

int	parse(int fd, t_tet *tetris)
{
	char	buf[BUFF_SIZE + 1];
	ssize_t	r_len;
	t_uint	tet_c;
	t_uint	i;

	tet_c = 0;
	r_len = 1;
	while (r_len > 0)
	{
		r_len = read(fd, buf, BUFF_SIZE);
		if (r_len < BUFF_SIZE - 1)
			return (XC_ERROR);
		buf[r_len] = 0;
		tetris[tet_c].bits = 0;
		i = -1U;
		while (++i < r_len)
		{
			if (buf[i] == '#')
				tetris[tet_c].bits = (1 << i) | tetris[tet_c].bits;
		}
		if (!tet_isvalid(tetris[tet_c]))
			return (XC_ERROR);
		tet_c++;
	}
	return (XC_EXIT);
}
