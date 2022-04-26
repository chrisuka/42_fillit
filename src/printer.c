/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <ikarjala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 18:26:23 by ikarjala          #+#    #+#             */
/*   Updated: 2022/04/25 16:47:28 by ikarjala         ###   ########.fr       */
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
