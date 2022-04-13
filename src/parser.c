/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <ikarjala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 19:01:35 by ikarjala          #+#    #+#             */
/*   Updated: 2022/04/13 18:21:04 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static int	tet_allowed(t_tet shape)
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

static int	check_connections(char *str)
{
	int i;
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
