/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <ikarjala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 16:00:28 by ikarjala          #+#    #+#             */
/*   Updated: 2022/05/13 20:56:01 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	uint64_t	*dword_p;
	uint64_t	dword;
	uint8_t		uchr;
	uint8_t		i;

	uchr = (unsigned char)c;
	if (len > sizeof(dword))
	{
		dword = (uint64_t)uchr;
		i = sizeof(char) * __CHAR_BIT__;
		while (i < sizeof(dword) * __CHAR_BIT__)
		{
			dword |= (dword << i);
			i <<= 1;
		}
		dword_p = &b[len];
		while (len >= sizeof(dword))
		{
			len -= sizeof(dword);
			*(--dword_p) = dword;
		}
	}
	while (len-- > 0)
		((unsigned char *)b)[len] = uchr;
	return (b);
}
