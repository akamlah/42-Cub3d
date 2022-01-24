/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamlah <akamlah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 12:20:44 by akamlah           #+#    #+#             */
/*   Updated: 2021/06/25 13:25:50 by akamlah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*mapi;
	unsigned int	i;

	if (!s)
		return (0);
	mapi = ft_strdup(s);
	if (!mapi)
		return (0);
	i = 0;
	while (mapi[i] != '\0')
	{
		mapi[i] = f(i, s[i]);
		i++;
	}
	return (mapi);
}
