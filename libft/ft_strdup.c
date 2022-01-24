/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamlah <akamlah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 11:48:57 by akamlah           #+#    #+#             */
/*   Updated: 2021/09/21 16:22:11 by akamlah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

char	*ft_strdup(const char *s1)
{
	char	*memptr;
	size_t	len_s1;

	len_s1 = ft_strlen(s1);
	memptr = (char *)malloc(sizeof(char) * (len_s1 + 1));
	if (!memptr)
		return (0);
	memptr = (char *)ft_memcpy(memptr, s1, (len_s1 + 1));
	return (memptr);
}
