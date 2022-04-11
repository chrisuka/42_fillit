/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <ikarjala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 18:19:57 by ikarjala          #+#    #+#             */
/*   Updated: 2022/04/09 21:41:07 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include <fcntl.h>
# include "libft.h"

# define FD_IN	0
# define FD_OUT	1
# define FD_ERR	2

# define XC_ERROR	-1
# define XC_EXIT	0

# define BUFF_SIZE	21

typedef unsigned long long	t_int64b;
typedef struct s_tetrimino
{
	t_int64b	code;
}	t_tet;

/* PRINTER */
int		display_error(void);
int		display_usage(void);

/* PARSER */
int		parse(int fd, t_tet *tetris);

#endif
