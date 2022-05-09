/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <ikarjala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 18:26:23 by ikarjala          #+#    #+#             */
/*   Updated: 2022/05/09 12:49:52 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int	display_error(void)
{
	ft_putendl_fd("error", FD_OUT);
	return (XC_ERROR);
}

int	display_usage(void)
{
	const char	*msg = "usage: fillit <tetrimino_file>";

	ft_putendl_fd(msg, FD_OUT);
	return (XC_EXIT);
}

int	print_grid(uint16_t *map, uint16_t size, t_tet *tetris)
{
	char		*buf;
	uint16_t	sqr;
	t_uint		i;
	t_uint		x;
	t_uint		y;

	sqr = size * size + size;
	buf = (char *)malloc(sizeof(char) * sqr);
	if (!buf)
		return (XC_ERROR);
	i = -1U;
	y = -1U;
	while (++y < size)
	{
		x = -1U;
		while (++x < size)
		{
			buf[++i] = ".#"[((map[y] & (1 << x)) != 0)];
			// TODO: needs to print correct tetrimino letter
		}
		buf[++i] = '\n';
	}
	write(FD_OUT, buf, sqr);
	ft_memdel((void **)&buf);
	tetris = NULL;//DEBUG
	return (XC_EXIT);
}
