/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <ikarjala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 19:01:35 by ikarjala          #+#    #+#             */
/*   Updated: 2022/04/21 12:46:05by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static int	tet_allowed(t_tet shape)
{
	t_uint			index;
	const uint64_t	v_tetris[19] = {
		I_PIECE, IH_PIECE, O_PIECE,
		L_PIECE, LCW_PIECE, LCCW_PIECE, LUD_PIECE,
		J_PIECE, JCW_PIECE, JCCW_PIECE, JUD_PIECE,
		T_PIECE, TCW_PIECE, TCCW_PIECE, TUD_PIECE,
		S_PIECE, SCW_PIECE, SCCW_PIECE, Z_PIECE
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
static t_tet	to_bitstr64(const char *buf)
{
	t_tet	ret;
	t_uint	i;
	t_bool	is_b;

	ret = (t_tet){0x0};
	while (*buf != '#' && *buf)
		buf++;
	i = 0;
	while (*buf)
	{
		is_b = (*buf == '#');
		ret.bits |= (uint64_t)(is_b << i);
		i += (*buf != '\n');
		buf++;
	}
	return (ret);
}

static int	check_connections(char *str)
{
	int	i;
	int	links;

	i = 0;
	links = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '#')
		{
			if (str[i + 1] == '#')
				links++;
			if (str[i + 5] == '#')
				links++;
		}
		i++;
	}
	if (links < 3)
		return (FT_FALSE);
	return (FT_TRUE);
}

static int	check_format(char *str)
{
	int	i;
	int	h_tag;
	int	n_l;

	i = 0;
	h_tag = 0;
	n_l = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '#')
			h_tag++;
		else if (str[i] == '\n')
		{
			if (((i + 1) % 5) == 0 || i == 20)
				n_l++;
		}
		else if (str[i] != '.')
			return (FT_FALSE);
		i++;
	}
	if (h_tag == 4 && (n_l == 5 || n_l == 4))
		return (FT_TRUE);
	return (FT_FALSE);
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
		if (r_len == 0)
			break ;
		if (tet_c > MAX_TETRIS || r_len < BUFF_SIZE - 1)
			return (XC_ERROR);
		buf[r_len] = 0;
		if (!check_format(buf) || !check_connections(buf))
			return (XC_ERROR);
		tetris[tet_c] = to_bitstr64(buf);
		if (!tet_allowed(tetris[tet_c]))
			return (XC_ERROR);
	}
	return (XC_EXIT);
}
