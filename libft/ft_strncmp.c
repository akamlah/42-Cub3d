/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamlah <akamlah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 18:05:33 by akamlah           #+#    #+#             */
/*   Updated: 2021/06/25 13:22:20 by akamlah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	c1;
	unsigned char	c2;
	size_t			i;

	i = 0;
	c1 = '\0';
	c2 = '\0';
	while (i < n && c1 == c2)
	{
		c1 = s1[i];
		c2 = s2[i];
		if (c1 == '\0')
			return (c1 - c2);
		i++;
	}
	return (c1 - c2);
}
