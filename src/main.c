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
#include <stdio.h> //DEBUG=======================================================

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
		printf("realloc at virtual size %u\n", size);//DEBUG
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
	if (parse (open(argv[1], O_RDONLY), tetris, &tet_c) == XC_ERROR)
		return (display_error());
	//DEBUG BEGIN =====================================================================
	#if 0
	while (tet_c-- > 0)
	{
		printf("tetris[%i]:\n0x%016llXULL\n", tet_c, tetris[tet_c].bits);
		print_grid(4, &tetris[tet_c]);
		ft_bzero(&tetris[tet_c], sizeof(t_tet));
	}
	return (0);
	#endif
	//DEBUG END =====================================================================
	tetris[tet_c].bits = 0ULL;
	grid_size = (uint8_t)ft_sqrt(tet_c * 4);
	create_grid(&map, grid_size);
	printf("attempting with map %ux%u\n", grid_size, grid_size); //DEBUG
	while (!solve(map, tetris, grid_size))
	{
		create_grid(&map, ++grid_size);
		printf("expand map to %ux%u\n", grid_size, grid_size); //DEBUG
	}
	printf("final result:\n"); //DEBUG
	print_grid(grid_size, tetris);
	del_array(&map, grid_size);
	return (XC_EXIT);
}
