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

/* it should be noted that atm this function will set the bits in reverse
** the top-left corner being represented by the rightmost bit. */
static	uint64_t	to_bitstr64(uint8_t *atoms, uint8_t n)
{
	uint64_t	bits;
	uint8_t		toggle_index;
	uint8_t		xoffset;
	uint8_t		x;

	bits = 0x0;
	xoffset = 5;
	while (n-- > 0)
	{
		x = atoms[n] % 5;
		xoffset = (uint8_t)ft_min(x, xoffset);
		toggle_index = (atoms[n] / 5) * 16 + x;
		bits |= (uint64_t)(1ULL << toggle_index);
	}
	xoffset = (atoms[0] % 5) - xoffset;
	bits >>= (toggle_index - xoffset);
	return (bits);
}

static void	get_bounds(uint8_t *atoms, uint8_t n,
	uint8_t *w_out, uint8_t *h_out)
{
	uint8_t		xmin;
	uint8_t		xmax;
	uint8_t		ymax;

	xmin = 4;
	xmax = 0;
	ymax = (atoms[n - 1] / 5);
	while (n-- > 0)
	{
		xmax = (uint8_t)ft_max(xmax, atoms[n] % 5);
		xmin = (uint8_t)ft_min(xmin, atoms[n] % 5);
	}
	*w_out = (xmax - xmin + 1);
	*h_out = (ymax - ((atoms[0] / 5)) + 1);
}

static void	get_block_indices(char *buf, uint8_t *o_indices)
{
	t_uint	a_i;
	t_uint	buf_i;

	a_i = 0;
	buf_i = -1U;
	while (buf[++buf_i])
	{
		if (buf[buf_i] == '#')
			o_indices[a_i++] = (uint8_t)buf_i;
	}
}

// Absolutely disgusting but works
static inline int	read_equ(int fd, void *buf, ssize_t *o_len)
{
	*o_len = read(fd, buf, BUFF_SIZE);
	return (*o_len != 0);
}

int	parse(int fd, t_tet *tetris, uint8_t *tet_count)
{
	char	buf[BUFF_SIZE + 1];
	uint8_t	atoms[4];
	ssize_t	r_len;
	uint8_t	tet_i;

	tet_i = (uint8_t)-1;
	while (read_equ(fd, buf, &r_len))
	{
		if (++tet_i >= MAX_TETRIS || r_len < BUFF_SIZE - 1)
			return (XC_ERROR);
		buf[r_len] = 0;
		get_block_indices(buf, atoms);
		if (!check_format(buf) || !check_connections(atoms, 4))
			return (XC_ERROR);
		tetris[tet_i] = (t_tet){
			to_bitstr64(atoms, 4), (char)('A' + tet_i), 0, 0};
/* 		if (!tet_allowed(tetris[tet_i]))
			return (XC_ERROR); */
		get_bounds(atoms, 4, &tetris[tet_i].w, &tetris[tet_i].h);
	}
	*tet_count = tet_i + 1;
	return (XC_EXIT);
}

#if 0
#include <stdio.h> //DEBUG============================================
int main(void)
{
	int			ret;
	char		buf[22];
	int			fd;
	uint8_t		atoms[4];
	u_int8_t	w, h;
	u_int64_t	bits;

	fd = open("eval_tests/invalid.txt", O_RDONLY);
	ret = read(fd, buf, 21);
	while (ret > 0)
	{
		buf[ret] = '\0';
		get_block_indices(buf, atoms);
		for (int i = 0; i < 4; i++)
			printf("%i ", atoms[i]);
		get_bounds(atoms, 4, &w, &h);
		printf("\n(%i, %i)", w, h);

		bits = to_bitstr64(atoms, 4);
		printf("\n%llu", bits);

		t_tet mytet = (t_tet){bits};
		//if (check_connections(idxs, 4);
		printf("\n%s", buf);
/* 		if (check_connections(atoms, 4) && tet_allowed(mytet))
			printf("\n%s", buf);
		else
			printf("\ninvalid"); */
		ret = read(fd, buf, 21);
	}
	printf("\n");
	close(fd);
	return (0);
}
#endif

