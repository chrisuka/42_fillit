/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staskine <staskine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 13:24:02 by staskine          #+#    #+#             */
/*   Updated: 2022/04/13 14:28:03 by staskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/* this one just counts the  amount of different
characters and checks for
invalid ones. I added checking the newline
positions to this like how we discussed */

static int	input_check(char *str)
{
	int	i;
	int	h_tag;
	int	n_l;

	i = 0;
	h_tag = 0;
	n_l = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '#')
			h_tag++;
		else if (str[i] == '\n')
		{
			if (((i + 1) % 5) == 0 || i == 20)
				n_l++;
		}
		else if (str[i] != '.')
			return (XC_ERROR);
		i++;
	}
	if (h_tag == 4 && (n_l == 5 || n_l == 4))
		return (XC_EXIT);
	return (XC_ERROR);
}

/* this is for checking each connection.
It works with the logic that the three first 
hashtags need to have another one either next 
to them or under them for it to be a valid tetrimino*/

static int check_connections(char *str)
{
	int i;
	int	links;

	i = 0;
	links = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '#')
		{
			if (str[i + 1] == '#')
				links++;
			if (str[i + 5] == '#')
				links++;
		}
		i++;
	}
	if (links < 3)
		return (XC_ERROR);
	return (XC_EXIT);
}


/*This main is purely for testing purposes of 
these two functions :) */

/*
int main(void)
{
	int ret;
	char buf[22];
	int result;
	int fd;

	fd = open("test.txt", O_RDONLY);
	ret = read(fd, buf, 21);
	while (ret > 0)
	{
		buf[ret] = '\0';
		printf("\n%s\n", buf);
		result = input_check(buf);
		if (result == -1)
			printf("This is an invalid string\n");
		else
		{
			result = check_connections(buf);
			if (result == -1)
				printf("This is an invalid string\n");
			else
				printf("This is a valid string\n");
		}
		ret = read(fd, buf, 21);
	}
	close(fd);
	return (0);
}
*/