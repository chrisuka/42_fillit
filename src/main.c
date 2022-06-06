/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <ikarjala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 17:19:50 by ikarjala          #+#    #+#             */
/*   Updated: 2022/05/05 15:55:06by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static void	del_array(uint16_t **map, uint16_t size)
{
	ft_bzero((void *)*map, size + (size % MAP_PADDING));
	free(*map);
	*map = NULL;
}

static int	create_grid(u_int16_t **map, u_int16_t size)
{
	if (*map)
	{
/* 		if (size % MAP_PADDING != 0)
			return (XC_EXIT); */
		free(*map);
	}
	*map = (uint16_t *)malloc(sizeof(u_int16_t) * size);
	if (!*map)
		return (XC_ERROR);
	ft_bzero(*map, size);
	return (XC_EXIT);
}

int	main(int argc, char **argv)
{
	t_tet		tetris[MAX_TETRIS + 1];
	uint16_t	*map;
	uint8_t		grid_size;
	uint8_t		tet_c;

	if (argc != 2)
		return (display_usage());
	ft_bzero(tetris, sizeof(tetris));
	if (parse (open(argv[1], O_RDONLY), tetris, &tet_c) == XC_ERROR || !tet_c)
		return (display_error());
	tetris[tet_c].bits = 0ULL;
	grid_size = (uint8_t)ft_sqrt(tet_c * 4);
	create_grid(&map, grid_size);
	while (!solve(map, tetris, grid_size))
	{
		create_grid(&map, ++grid_size);
	}
	print_grid(grid_size, tetris);
	del_array(&map, grid_size);
	return (XC_EXIT);
}
