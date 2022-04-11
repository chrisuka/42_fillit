/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staskine <staskine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 14:01:04 by staskine          #+#    #+#             */
/*   Updated: 2022/04/11 14:42:55 by staskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int	ft_sqrt(int number)
{
	int	variable;

	variable = 0;
	while ((variable * variable) < number)
		variable++;
	return (variable);
}
