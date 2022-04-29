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

#include <stdio.h> //DEBUG===============================================================

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

/* it should be noted that atm this function will set the bits in reverse
** the top-left corner being represented by the rightmost bit. */
static	uint64_t	tr_bitstr64(uint8_t *idxs, uint8_t n)
{
	uint64_t	bits;
	uint8_t		toggle_index;
	uint8_t		xoffset;
	uint8_t		x;

	bits = 0x0;
	xoffset = idxs[0] % 5;
	while (n-- > 0)
	{
		x = idxs[n] % 5;
		printf("%u-%u ", xoffset, (x < xoffset) * x); //DEBUG====================
		xoffset -= ((x < xoffset) * x);//FIXME: should only subtract up to once per row!
		toggle_index = (idxs[n] / 5) * 16 + x;
		bits |= (uint64_t)(1 << toggle_index);
	}
	printf("\n");//DEBUG====================================
	bits >>= (idxs[0] - xoffset);
	return (bits);
}

//		DEPRECATED		//
#if 0
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
		ret.bits |= (uint64_t)(is_b << i);
		i += (*buf != '\n');
		buf++;
	}
	return (ret);
}
#endif

// NEW CONTENDER (NOT FUNCTIONAL ATM)
#if 0
static int	check_connections(uint8_t *blocks, uint8_t n)
{
	uint8_t	gap;
	uint8_t	links;

	links = 0;
	while (n-- > 1)
	{
		gap = blocks[n] - blocks[n - 1];
		links += (gap == 1 || gap == 5);
	}
	return (links >= 3);
}
#endif

//		DEPRECATED (?)		//
#if 1
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
#endif

static void	get_bounds(uint8_t *idxs, uint8_t n,
	uint8_t *w_out, uint8_t *h_out)
{
	uint8_t		xmin;
	uint8_t		xmax;
	uint8_t		ymax;

	xmin = 4;
	xmax = 0;
	ymax = (idxs[n - 1] / 5);
	while (n-- > 0)
	{
		xmax = (uint8_t)ft_max(xmax, idxs[n] % 5);
		xmin = (uint8_t)ft_min(xmin, idxs[n] % 5);
	}
	*w_out = (xmax - xmin + 1);
	*h_out = (ymax - ((idxs[0] / 5)) + 1);
}

static void	get_block_idxs(char *buf, uint8_t *idxsout)
{
	uint8_t	a_i;
	uint8_t	buf_i;

	a_i = 0;
	buf_i = (uint8_t)-1U;
	while (buf[++buf_i])
	{
		if (buf[buf_i] == '#')
			idxsout[a_i++] = buf_i;
	}
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

#if 0
int	parse(int fd, t_tet *tetris)
{
	char	buf[BUFF_SIZE + 1];
	uint8_t	tb_ixs[4];
	ssize_t	r_len;
	t_uint	tet_i;

	tet_i = 0;
	r_len = 1;
	// TODO: cleanup
	while (r_len > 0)
	{
		r_len = read(fd, buf, BUFF_SIZE);
		if (r_len == 0)
			break ;
		if (tet_i >= MAX_TETRIS || r_len < BUFF_SIZE - 1)
			return (XC_ERROR);
		buf[r_len] = 0;
		get_block_idxs(buf, tb_ixs);
		if (!check_format(buf) || !check_connections(tb_ixs, 4))
			return (XC_ERROR);
		tetris[tet_i] = (t_tet){tr_bitstr64(tb_ixs, 4),
			('A' + tet_i), (uint16_t)get_bounds(tb_ixs, 4)};
		if (!tet_allowed(tetris[tet_i]))
			return (XC_ERROR);
		tet_i++;
	}
	return (XC_EXIT);
}
#endif






int main(void)
{
	int ret;
	char buf[22];
	int fd;
	uint8_t	idxs[4];
	u_int8_t	w, h;
	u_int64_t	bits;

	fd = open("eval_tests/t_shapes.txt", O_RDONLY);
	ret = read(fd, buf, 21);
	while (ret > 0)
	{
		buf[ret] = '\0';
		get_block_idxs(buf, idxs);
		for (int i = 0; i < 4; i++)
			printf("%i ", idxs[i]);
		get_bounds(idxs, 4, &w, &h);
		printf("\n(%i, %i)\n", w, h);

		bits = tr_bitstr64(idxs, 4);
		printf("%X", bits);

		t_tet mytet = (t_tet){bits};
		//if (check_connections(idxs, 4);
		if (check_connections(buf))
			printf("\n%s", buf);
		ret = read(fd, buf, 21);
	}
	printf("\n");
	close(fd);
	return (0);
}
