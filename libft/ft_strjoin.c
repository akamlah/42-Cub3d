/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamlah <akamlah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 16:38:04 by akamlah           #+#    #+#             */
/*   Updated: 2021/08/29 12:15:42 by akamlah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	char	*jstr;
	size_t	len_s1;
	size_t	len_s2;

	if (!s1)
		return (0);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	jstr = (char *)malloc(sizeof(int) * (len_s1 + len_s2 + 1));
	if (!jstr)
		return (0);
	i = 0;
	while (s1[i] != '\0')
	{
		jstr[i] = s1[i];
		i++;
	}
	while (s2[i - len_s1] != '\0')
	{
		jstr[i] = s2[i - len_s1];
		i++;
	}
	jstr[i] = '\0';
	return (jstr);
}
