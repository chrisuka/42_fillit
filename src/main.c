/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <ikarjala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 17:19:50 by ikarjala          #+#    #+#             */
/*   Updated: 2022/04/09 18:35:42 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int	main(int argc, char **argv)
{
	int	fd;

	if (argc != 2)
		return (display_usage());
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (display_error());
	parse(fd);
	return (XC_EXIT);
}

// TODO:
//	decide on tetrimino data structure
//	write parser
//	write printer
//	plan main algorithm