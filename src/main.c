/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <ikarjala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:57:41 by ikarjala          #+#    #+#             */
/*   Updated: 2022/08/23 12:06:06 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static void	del_array(uint16_t **map)
{
	free(*map);
	*map = NULL;
}

static int	create_grid(u_int16_t **map, u_int16_t size)
{
	if (*map)
	{
		if (size % MAP_PADDING != 0)
			return (XC_EXIT);
		free(*map);
	}
	size += MAP_PADDING;
	*map = (uint16_t *)malloc(sizeof(uint16_t) * size);
	if (!*map)
		return (XC_ERROR);
	ft_bzero(*map, sizeof(uint16_t) * size);
	return (XC_EXIT);
}

static inline int	parse_tetris(const char *path, t_tet *tetris,
		uint8_t *tet_cp)
{
	int	fd;
	int	ret;

	fd = open(path, O_RDONLY);
	ret = parse(fd, tetris, tet_cp);
	close(fd);
	return (ret);
}

/*	parse tetriminos from input file
 *	calculate grid starting size
 *	call recursive solver
 *	convert bit map to string and print output
*/
int	main(int argc, char **argv)
{
	t_tet		tetris[MAX_TETRIS + 1];
	uint16_t	*map;
	uint8_t		grid_size;
	uint8_t		tet_c;

	if (argc != 2)
		return (display_usage());
	ft_bzero(tetris, sizeof(tetris));
	if (parse_tetris (argv[1], tetris, &tet_c) == XC_ERROR || !tet_c)
		return (display_error());
	tetris[tet_c].bits = 0ULL;
	grid_size = (uint8_t)ft_sqrt(tet_c * 4);
	map = NULL;
	create_grid(&map, grid_size);
	while (!solve(map, tetris, grid_size))
		create_grid(&map, ++grid_size);
	print_grid(grid_size, tetris);
	del_array(&map);
	return (XC_EXIT);
}
