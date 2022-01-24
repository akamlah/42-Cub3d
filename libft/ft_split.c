/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamlah <akamlah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 16:19:18 by akamlah           #+#    #+#             */
/*   Updated: 2021/09/21 16:20:24 by akamlah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

static size_t	ft_substrcount(char *s, char c)
{
	size_t	i;

	i = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s != 0)
			i++;
		while (*s != c && *s)
			s++;
	}
	return (i);
}

static size_t	ft_substrlen(char *s, char c)
{
	size_t	substrlen;

	substrlen = 0;
	while (*s == c && *s)
		s++;
	while (s[substrlen] != c && s[substrlen] != 0)
		substrlen++;
	return (substrlen);
}

static char	**ft_build_splitted(char **splitted, char *s, char c)
{
	size_t	i;
	size_t	save;
	size_t	j;

	i = 0;
	save = ft_substrcount(s, c);
	while (i < save)
	{
		splitted[i] = (char *)malloc(sizeof(char *) * (ft_substrlen(s, c) + 1));
		while (*s == c && *s)
			s++;
		j = 0;
		while (*s != c && *s)
		{
			splitted[i][j] = *s;
			s++;
			j++;
		}
		splitted[i][j] = '\0';
		i++;
	}
	splitted[i] = 0;
	return (splitted);
}

char	**ft_split(char const *str, char c)
{
	char	**splitted;
	char	*s;

	if (!str)
		return (0);
	s = (char *)str;
	if (!*s)
	{
		splitted = (char **)malloc(sizeof(char *) * 1);
		*splitted = 0;
		return (splitted);
	}
	splitted = (char **)malloc(sizeof(char *) * (ft_substrcount(s, c) + 1));
	if (!splitted)
		return (0);
	splitted = ft_build_splitted(splitted, s, c);
	return (splitted);
}
