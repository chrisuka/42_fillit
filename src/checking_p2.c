/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_p2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staskine <staskine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 13:24:02 by staskine          #+#    #+#             */
/*   Updated: 2022/04/07 15:06:52 by staskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/* str - p should give the place of the new line character.
could be used to check if the length of the lines is correct.
The values should be 5, 10, 15, 20 */

static int	find_nl(char *str)
{
	int	findIndex;
	int i;
	char *p;

	findIndex = 0;
	i = 0;
	while (str)
	{
		p = ft_strchr(&str[i + 1], '\n');
		findIndex = str - p;
		if ((findIndex % 5) != 0)
			return (XC_ERROR);
		i = findIndex;
		findIndex = 0;
	}
	return (0);
}

/* this one just counts the  amount of different characters and checks for
invalid ones */

static int	edit_str(char *str)
{
	int	i;
	int	counter;
	int	counter_2;

	i = 0;
	counter = 0;
	counter_2 = 0;
	while (str)
	{
		if (str[i] == '#')
			counter++;
		if (str[i] == '\n')
			counter_2++;
		if (str[i] != '.' && str[i] != '#' && str[i] == '\n')
			return (XC_ERROR);
	}
	if (counter == 4 && (counter_2 == 4 || counter_2 == 5))
		return (0);
	return (XC_ERROR);
}

static int check_connections(char *str)
{
	int i;

	i = 0;
	while (str)
	{
		
	}
}

int	check_input(char *str)
{
	int check;

	check = edit_str(str);
	if (check != 0)
		return (XC_ERROR);
	check = find_nl(str);
	if (check != 0)
		return (XC_ERROR);
}