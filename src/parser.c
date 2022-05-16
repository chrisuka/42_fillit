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
static	uint64_t	to_bitstr64(t_point *atoms, uint8_t n)
{
	uint64_t	bits;
	uint8_t		toggle_index;
	uint8_t		xoffset;

	bits = 0x0;
	xoffset = 5;
	while (n-- > 0)
	{
		xoffset = (uint8_t)ft_min(atoms[n].x, xoffset);
		toggle_index = atoms[n].y * 16 + atoms[n].x;
		bits |= (uint64_t)(1ULL << toggle_index);
	}
	xoffset = atoms[0].x - xoffset;
	bits >>= (toggle_index - xoffset);
	return (bits);
}

static t_point	get_bounds(t_point *atoms, uint8_t n)
{
	t_point		bounds;
	t_point		max;
	uint8_t		xmin;

	xmin = 4;
	max.x = 0;
	max.y = atoms[n - 1].y;
	while (n-- > 0)
	{
		max.x = (uint8_t)ft_max(max.x, atoms[n].x);
		xmin = (uint8_t)ft_min(xmin, atoms[n].x);
	}
	bounds.x = (max.x - xmin + 1);
	bounds.y = (max.y - atoms[0].y + 1);
	return (bounds);
}

static void	get_block_indices(char *buf, t_point *o_indices)
{
	t_uint	a_i;
	t_uint	buf_i;

	a_i = 0;
	buf_i = -1U;
	while (buf[++buf_i])
	{
		if (buf[buf_i] == '#')
			o_indices[a_i++] = (t_point){buf_i % 5, buf_i / 5};
	}
}

// Absolutely disgusting but works
static inline int	read_equ(int fd, void *buf, ssize_t *o_len)
{
	*o_len = read(fd, buf, BUFF_SIZE);
	return (*o_len != 0);
}

// TODO:
//	CHANGE BLOCK_INDICES TO USE XY TUPLES INSTEAD

int	parse(int fd, t_tet *tetris, uint8_t *tet_count)
{
	char	buf[BUFF_SIZE + 1];
	t_point	atoms[4];
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
			to_bitstr64(atoms, 4), get_bounds(atoms, 4), {{0}}};
		ft_memmove(tetris[tet_i].atoms, atoms, sizeof(atoms));
		if (!tet_allowed(tetris[tet_i]))
			return (XC_ERROR);
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

