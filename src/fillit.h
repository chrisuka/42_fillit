/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <ikarjala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 18:19:57 by ikarjala          #+#    #+#             */
/*   Updated: 2022/04/29 19:46:24 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include <fcntl.h>
# include <stdint.h>
# include "libft.h"

# define FD_IN	0
# define FD_OUT	1
# define FD_ERR	2

# define XC_ERROR	-1
# define XC_EXIT	0

# define MAX_TETRIS	26
# define BUFF_SIZE	21

typedef uint64_t	t_m4x16;
typedef struct s_tetrimino
{
	uint64_t	bits;
	char		legend;
	uint8_t		w;
	uint8_t		h;
}	t_tet;

/* TETRIMINO CODES */
# define I_PIECE	0b0000000000000001000000000000000100000000000000010000000000000001U
# define IH_PIECE	0b0000000000001111
# define O_PIECE	0b0000000000110000000000000011

# define L_PIECE	0b0000001100010001
# define LCW_PIECE	0b0000000000010111
# define LCCW_PIECE	0b0000000000011101
# define LUD_PIECE	0b0000001000100011

# define J_PIECE	0b0000000110010001
# define JCW_PIECE	0b0000000001110001
# define JCCW_PIECE	0b0000000001000111
# define JUD_PIECE	0b0000000100010011

# define T_PIECE	0b0000000000100111
# define TCW_PIECE	0b0000000100011001
# define TCCW_PIECE	0b0000000100110001
# define TUD_PIECE	0b0000000000111001

# define S_PIECE	0b0000000000011011
# define SCW_PIECE	0b0000001000110001
# define Z_PIECE	0b0000000001100011
# define ZCW_PIECE	0b0000000010011001

/* PRINTER */
int	display_error(void);
int	display_usage(void);

/* PARSER */
int	parse(int fd, t_tet *tetris);

/* SOLVER */
int	solve(t_m4x16 *map, t_tet *tetris, t_uint size);

/* MATH */
int	ft_min(int a, int b);
int	ft_max(int a, int b);

#endif
