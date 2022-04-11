/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <ikarjala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 19:01:35 by ikarjala          #+#    #+#             */
/*   Updated: 2022/04/09 21:41:40 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static int	tet_isvalid(t_tet shape)
{
	t_uint			index;
	const t_int64b	v_tetris[19] = {
		// we can simply put macros here, as defined in the header
	};

	index = -1U;
	while (++index < 19)
	{
		if (shape.code == v_tetris[index])
			return (FT_TRUE);
	}
	return (FT_FALSE);
}

int	parse(int fd, t_tet *tetris)
{
	char		buf[BUFF_SIZE + 1];
	ssize_t		rbytes;
	t_uint		tetc;
	t_uint		blocks;
	t_uint		i;

	tetc = 0;
	rbytes = 1;
	while (rbytes > 0)
	{
		rbytes = read(fd, buf, BUFF_SIZE);
		if (rbytes < BUFF_SIZE - 1)
			return (XC_ERROR);
		buf[rbytes] = 0;
		blocks = 0;
		i = 0;
		tetris[tetc].code = 0;
		while (i < rbytes)
		{
			if (buf[i] == '#')
				tetris[tetc].code = (1 << i) | tetris[tetc].code;
		}
		if (blocks != 4 || !tet_isvalid(tetris[tetc]))
			return (XC_ERROR);
		tetc++;
	}
	return (XC_EXIT);
}
