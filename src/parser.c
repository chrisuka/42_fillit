/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <ikarjala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 19:01:35 by ikarjala          #+#    #+#             */
/*   Updated: 2022/04/13 18:01:47 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static t_bool	tet_allowed(t_tet shape)
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

/* it should be noted that atm this function will set the bits in
** reverse order the top-left corner being represented by the rightmost bit.
*/
static t_tet	to_bitstr64(const char *buf, ssize_t r_len)
{
	t_tet	ret;
	t_uint	i;

	ret = (t_tet){0x0};
	i = -1U;
	while (++i < r_len)
	{
		if (buf[i] == '#')
			ret.bits = (1 << i) | ret.bits;
	}
	return (ret);
}

int	parse(int fd, t_tet *tetris)
{
	char	buf[BUFF_SIZE + 1];
	ssize_t	r_len;
	t_uint	tet_c;

	tet_c = 0;
	r_len = 1;
	while (r_len > 0)
	{
		tet_c++;
		r_len = read(fd, buf, BUFF_SIZE);
		if (r_len < BUFF_SIZE - 1 || tet_c > 26)
			return (XC_ERROR);
		buf[r_len] = 0;
		if (!input_check(buf) || !check_connections(buf))
			return (XC_ERROR);
		tetris[tet_c] = to_bitstr64(buf, r_len);
		if (!tet_allowed(tetris[tet_c]))
			return (XC_ERROR);
	}
	return (XC_EXIT);
}
