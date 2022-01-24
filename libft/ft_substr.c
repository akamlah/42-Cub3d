/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamlah <akamlah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 15:53:33 by akamlah           #+#    #+#             */
/*   Updated: 2021/08/29 11:59:55 by akamlah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*substr;
	size_t	len_s;

	if (!s)
		return (0);
	len_s = ft_strlen(s);
	substr = (char *)malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (0);
	i = 0;
	while (len--)
	{
		if (s[i] != '\0' && start <= len_s)
			substr[i] = s[i + start];
		else
			substr[i] = '\0';
		i++;
	}
	substr[i] = '\0';
	return (substr);
}
