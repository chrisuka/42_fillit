/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <ikarjala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 18:19:57 by ikarjala          #+#    #+#             */
/*   Updated: 2022/05/05 16:48:27 by ikarjala         ###   ########.fr       */
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
# define I_PIECE	65537ULL
# define IH_PIECE	15ULL
# define O_PIECE	196611ULL

# define L_PIECE	65539ULL
# define LCW_PIECE	65543ULL
# define LCCW_PIECE	458756ULL
# define LUD_PIECE	131075ULL

# define J_PIECE	131075ULL
# define JCW_PIECE	458753ULL
# define JCCW_PIECE	262151ULL
# define JUD_PIECE	65539ULL

# define T_PIECE	131079ULL
# define TCW_PIECE	196609ULL
# define TCCW_PIECE	196610ULL
# define TUD_PIECE	458754ULL

# define S_PIECE	196614ULL
# define SCW_PIECE	196611ULL
# define Z_PIECE	393219ULL
# define ZCW_PIECE	196611ULL

/* PRINTER */
int	display_error(void);
int	display_usage(void);

/* PARSER */
int	parse(int fd, t_tet *tetris);

/* SOLVER */
int	solve(uint16_t *map, t_tet *tetris, uint8_t size);

/* MATH */
int	ft_min(int a, int b);
int	ft_max(int a, int b);

#endif
