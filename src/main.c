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

int	main(int argc, char **argv)
{
	t_tet		tetris[MAX_TETRIS + 1];
	//uint16_t	*map;
	int			fd;
	int			ret;

	if (argc != 2)
		return (display_usage());
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (display_error());
	ret = parse(fd, tetris);
	close(fd);
	if (ret == XC_ERROR)
		return (display_error());
	ft_putendl("the parsing was successful"); //DEBUG
	return (0);
	#if 0
	map = grid_create();
	while (!solve(map, tetris, 4, 1))
		grid_expand();
	ft_putendl("this is the part where we print the map");//DEBUG
	// and here we would free the allocated map
	return (XC_EXIT);
	#endif
}
