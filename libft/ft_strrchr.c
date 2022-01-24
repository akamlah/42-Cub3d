/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamlah <akamlah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 16:29:37 by akamlah           #+#    #+#             */
/*   Updated: 2021/06/25 13:25:25 by akamlah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*cptr;

	cptr = 0;
	while (*s != '\0')
	{
		if (*s == c)
			cptr = (char *)s;
		s ++;
	}
	if (*s == c)
		return ((char *)s);
	return (cptr);
}
