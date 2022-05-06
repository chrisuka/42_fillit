/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <ikarjala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 18:26:23 by ikarjala          #+#    #+#             */
/*   Updated: 2022/05/06 15:08:53 by ikarjala         ###   ########.fr       */
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

int	print_grid(uint16_t *map, uint8_t size, t_tet *tetris)
{
	char	*buf;
	uint8_t	sqr;
	uint8_t	i;
	uint8_t	x;
	uint8_t	y;

	sqr = size * size;
	buf = (char *)malloc(sizeof(char) * sqr + 1);
	if (!buf)
		return (XC_ERROR);
	i = -1;
	y = -1;
	while (++y < size)
	{
		x = -1;
		while (++x < size)
		{
			buf[++i] = ".#"[((map[y] & (1 << x)) != 0)];
			// TODO: needs to print correct tetrimino letter
		}
	}
	buf[sqr] = '\n';
	write(FD_OUT, buf, sqr);
	ft_memdel((void **)&buf);
	tetris = NULL;
	return (XC_EXIT);
}
